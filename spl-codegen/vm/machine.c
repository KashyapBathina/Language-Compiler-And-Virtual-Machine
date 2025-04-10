/* $Id: machine.c,v 1.49 2024/11/10 22:47:50 leavens Exp leavens $ */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "machine_types.h"
#include "machine.h"
#include "regname.h"
#include "utilities.h"

#define MAX_PRINT_WIDTH 59

// the VM's memory, in signed and unsigned word and binary instruction views.
static union mem_u {
    word_type words[MEMORY_SIZE_IN_WORDS];
    uword_type uwords[MEMORY_SIZE_IN_WORDS];
    bin_instr_t instrs[MEMORY_SIZE_IN_WORDS];
} memory;

// general purpose registers
static word_type GPR[NUM_REGISTERS];
// hi and lo registers used in multiplication and division.
// A view as a (signed) long int (result, 64 bits)
// and as an array (hilo) of 2 32-bit ints.
static union longAs2words_u {
    long result;
    word_type hilo[2]; 
} hilo_regs;

// LO is index 0, HI is index 1, for an x86 architecture
// (because the x86 is little-endian)
#define LO 0
#define HI 1

// the program counter
static address_type PC;

// should the machine be printing tracing output?
static bool tracing;

// initial_stack_bottom is used for tracing
static address_type initial_stack_bottom;

// words of instructions (based on the header)
static unsigned short instruction_words;
// words of global data (based on the header)
static unsigned short global_data_words;


// should the machine be running? (default true)
static bool running;

// set up the state of the machine
static void initialize()
{
    tracing = true;   // default for tracing
    instruction_words = 0;
    global_data_words = 0;
    running = true;

    // zero the registers
    for (int j = 0; j < NUM_REGISTERS; j++) {
	GPR[j] = 0;
    }
    hilo_regs.result = 0;
    // zero out the memory
    for (int i = 0; i < MEMORY_SIZE_IN_WORDS; i++) {
	memory.words[i] = 0;
    }
}

// Requires: bf is a binary object file that is open for reading
// Load count instructions from bf into the memory starting at address 0.
// If any errors are encountered, exit with an error message.
static void load_instructions(BOFFILE bf, int count)
{
    for (int wa = 0; wa < count; wa++) {
	memory.instrs[wa] = instruction_read(bf);
    }
}

// Requires: bf is a binary object file that is open for reading
// Load count words from bf into the memory
// starting at word address global_base.
// If any errors are encountered, exit with an error message.
static void load_data(BOFFILE bf, int count, unsigned int global_base)
{
    for (int wo = 0; wo < count; wo++) {
	memory.words[global_base+wo] = bof_read_word(bf);
    }
}

// Requires: bf is open for reading in binary
// Load the binary object file bf, and get ready to run it
void machine_load(BOFFILE bf)
{
    initialize();

    // read and check the header
    BOFHeader bh = bof_read_header(bf);
    if (bh.text_length >= bh.data_start_address) {
	bail_with_error("%s (%u) %s (%u)!",
			"Text, i.e., program length", bh.text_length,
			"is not less than the start address of the global data",
			bh.data_start_address);
    }
    if (bh.data_start_address + bh.data_length >= bh.stack_bottom_addr) {
	bail_with_error("%s (%u) + %s (%u) %s (%u)!",
			"Global data start address", bh.data_start_address,
			"global data length", bh.data_length,
			"is not less than the stack bottom address",
			bh.stack_bottom_addr);
    }
    if (bh.stack_bottom_addr >= MEMORY_SIZE_IN_WORDS) {
	bail_with_error("%s (%u) %s (%u)!",
			"stack_bottom_addr", bh.stack_bottom_addr,
			"is not less than the memory size",
			MEMORY_SIZE_IN_WORDS);
    }

    // load the program
    instruction_words = bh.text_length;
    load_instructions(bf, instruction_words);

    global_data_words = bh.data_length;
    
    load_data(bf, global_data_words, bh.data_start_address);

    // initialize the registers
    PC = bh.text_start_address;

    GPR[GP] = bh.data_start_address;
    GPR[SP] = bh.stack_bottom_addr;
    GPR[FP] = bh.stack_bottom_addr;
    initial_stack_bottom = bh.stack_bottom_addr;
}

// Requires: fmt == 'x' or fmt == 'd'
// print the memory location at word address wa to out
// with a format determined by fmt and no newline,
// returns the number of characters written
static int print_loc(FILE *out, address_type wa, char fmt)
{
    int count;
    if (fmt == 'x') {
	count = fprintf(out, "%8d: 0x%x\t", wa,
			memory.words[wa]);
    } else { // fmt == 'd'
	count = fprintf(out, "%8d: %d\t", wa,
			memory.words[wa]);
    }
    return count;
}

// print the word address given and the instruction's assembly form
static void print_instruction(FILE *out, address_type wa, bin_instr_t bi)
{
    fprintf(out, "%6d: %s\n", wa, instruction_assembly_form(wa, bi));
}

// Print the word memory in hex or decimal based on the fmt argument
// between the word addresses start (inclusive) and end (inclusive) to out,
// without a newline and eliding all repeated zeros in the range
// Returns true if printed a newline at the end, false otherwise
static bool print_memory_nonzero(FILE *out, int start, int end, char fmt)
{
    bool printed_trailing_newline = false;
    bool previously_zero = false; // was previous word printed a 0?
    bool printed_dots = false;   // have we already printed dots?
    int lc = 0;   // count of chars on a line
    for (int wa = start; wa <= end; wa++) {
	if (lc > MAX_PRINT_WIDTH) {
	    newline(out);
	    printed_trailing_newline = true;
	    lc = 0;
	}
	if (memory.words[wa] != 0) {
	    lc += print_loc(out, wa, fmt);
	    printed_trailing_newline = false;
	    previously_zero = false;
	    printed_dots = false;
	} else {
	    // memory.words[wa] == 0
	    if (!previously_zero) {
		// print the first zero
		lc += print_loc(out, wa, fmt);
		previously_zero = true;
		printed_dots = false;
	    } else {
		// previously printed a zero
		if (!printed_dots) {
		    // not already printed the dots, so print them now
		    lc += fprintf(out, "%s", "        ...     ");
		    printed_dots = true;
		}
	    }
	    printed_trailing_newline = false;
	}
    }
    return printed_trailing_newline;
}

// print the nonzero memory locations between the word addresses
// start and end (both inclusive) on out, in decimal notation
// a trailing newline was printed if the result is true
static bool print_memory_words_d(FILE *out, int start, int end)
{
    return print_memory_nonzero(out, start, end, 'd');
}

// Print the global area, eliding repeated zeros,
// starting at GPR[GP]
static void print_global_data(FILE *out)
{
    int global_wa = GPR[GP];
    bool printed_nl;
    printed_nl = print_memory_words_d(out, global_wa, GPR[SP]-1);
    if (!printed_nl) {
	newline(out);
    }
}

// Requires: a program has been loaded into the computer's memory
// print a heading and the program and any global data
// that were previously loaded into the VM's memory to out
void machine_print_loaded_program(FILE *out)
{
    // heading
    instruction_print_table_heading(out);
    // instructions
    for (int wa = 0; wa < instruction_words; wa++) {
	print_instruction(out, wa, memory.instrs[wa]);
    }

    print_global_data(out);
}

// Run the VM on the already loaded program,
// producing any trace output called for by the program
void machine_run(bool trace_execution)
{
    tracing = trace_execution;
    if (tracing) {
	machine_print_state(stdout);
    }
    // execute the program
    while (running) {
	machine_okay(); // check the invariant
	machine_trace_execute_instr(stdout, PC, memory.instrs[PC]);
    }
}

// Load the given binary object file and run it
void machine_load_and_run(BOFFILE bf, bool trace_execution)
{
    machine_load(bf);
    machine_run(trace_execution);
}

// Requires: addr == PC.
// If tracing then print the given word address and the assembly form of bi,
// then execute bi (always),
// then if tracing print out the machine's state.
// All tracing output goes to the FILE out
void machine_trace_execute_instr(FILE *out, address_type addr,
				 bin_instr_t bi)
{
    assert(addr == PC);
    if (tracing) {
	fprintf(out, "\n==> ");
	print_instruction(out, PC, bi);
    }
    machine_execute_instr(addr, bi);
    if (tracing) {
	machine_print_state(out);
    }
}

// Requires: The instruction at memory.instrs[PC] is bi.
// Execute the given instruction, which is found at word address addr,
// in the machine's current state
void machine_execute_instr(address_type addr, bin_instr_t bi)
{
    // increment the PC (advance address by 1 word)
    PC = PC + 1;

    // execute the actual instruction
    instr_type it = instruction_type(bi);
    switch (it) {
    case comp_instr_type:
	{
	    comp_instr_t ci = bi.comp;
	    switch (ci.func) {
	    case NOP_F:
		// do nothing
		break;
	    case ADD_F:
		memory.words[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.words[GPR[SP]]
			  + memory.words[GPR[ci.rs] + machine_types_formOffset(ci.os)];
		break;
	    case SUB_F:
		memory.words[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.words[GPR[SP]]
		    - memory.words[GPR[ci.rs]
				   + machine_types_formOffset(ci.os)];
		break;
	    case CPW_F:
		memory.words[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.words[GPR[ci.rs]
				   + machine_types_formOffset(ci.os)];
		break;
	    case CPR_F:
		GPR[ci.rt] = GPR[ci.rs];
		break;
	    case AND_F:
		memory.uwords[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.uwords[GPR[SP]]
		    & memory.uwords[GPR[ci.rs]
				    + machine_types_formOffset(ci.os)];
		break;
	    case BOR_F:
		memory.uwords[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.uwords[GPR[SP]]
		    | memory.uwords[GPR[ci.rs]
				    + machine_types_formOffset(ci.os)];
		break;
	    case NOR_F:
		memory.uwords[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = ~(memory.uwords[GPR[SP]]
			| memory.uwords[GPR[ci.rs]
					+ machine_types_formOffset(ci.os)]);
		break;
	    case XOR_F:
		memory.uwords[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.uwords[GPR[SP]]
		    ^ memory.uwords[GPR[ci.rs]
				    + machine_types_formOffset(ci.os)];
		break;
	    case LWR_F:
		GPR[ci.rt]
		    = memory.words[GPR[ci.rs]
				   + machine_types_formOffset(ci.os)];
		break;
	    case SWR_F:
		memory.words[GPR[ci.rt]
			     + machine_types_formOffset(ci.ot)]
		    = GPR[ci.rs];
		break;
	    case SCA_F:
		memory.words[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = (GPR[ci.rs] + machine_types_formOffset(ci.os));
		break;
	    case LWI_F:
		memory.words[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = memory.words[memory.words
				   [GPR[ci.rs] + machine_types_formOffset(ci.os)]];
		    break;
	    case NEG_F:
		memory.words[GPR[ci.rt] + machine_types_formOffset(ci.ot)]
		    = - (memory.words[GPR[ci.rs]
				      + machine_types_formOffset(ci.os)]);
		break;
	    default:
		bail_with_error("Invalid function code (%d) in machine_execute's COMP_O computational instruction case!",
				ci.func);
		break;
	    }
	}
	break;
    case other_comp_instr_type:
	{
	    other_comp_instr_t oci = bi.othc;
	    switch (oci.func) {
	    case LIT_F:
		memory.words[GPR[oci.reg] + machine_types_sgnExt(oci.offset)]
			     = machine_types_sgnExt(oci.arg);
	        break;
	    case ARI_F:
		GPR[oci.reg] = GPR[oci.reg] + machine_types_sgnExt(oci.arg);
		break;
	    case SRI_F:
		GPR[oci.reg] = GPR[oci.reg] - machine_types_sgnExt(oci.arg);
		break;
	    case MUL_F:
		hilo_regs.result
		    = (long) memory.words[GPR[SP]]
		      * (long) memory.words[GPR[oci.reg]
				     + machine_types_formOffset(oci.offset)];
		break;
	    case DIV_F:
		int divisor = memory.words[GPR[oci.reg]
				     + machine_types_formOffset(oci.offset)];
		if (divisor == 0) {
		    bail_with_error("Error: Attempt to divide by zero!");
		}
		hilo_regs.hilo[HI] = memory.words[GPR[SP]] % divisor;
		hilo_regs.hilo[LO] = memory.words[GPR[SP]] / divisor;
		break;
	    case CFHI_F:
		memory.words[GPR[oci.reg]
				 + machine_types_formOffset(oci.offset)]
		    = hilo_regs.hilo[HI];
		break;
	    case CFLO_F:
		memory.words[GPR[oci.reg]
				 + machine_types_formOffset(oci.offset)]
		    = hilo_regs.hilo[LO];
		break;
	    case SLL_F:
		memory.uwords[GPR[oci.reg]
			     + machine_types_formOffset(oci.offset)]
		    = memory.uwords[GPR[SP]] << oci.arg;
		break;
	    case SRL_F:
		memory.uwords[GPR[oci.reg]
			     + machine_types_formOffset(oci.offset)]
		    = memory.uwords[GPR[SP]] >> oci.arg;
		break;
	    case JMP_F:
		PC = memory.uwords[GPR[oci.reg]
				   + machine_types_formOffset(oci.offset)];
		break;
	    case CSI_F:
		GPR[RA] = PC;
		PC = memory.words[GPR[oci.reg]
				  + machine_types_formOffset(oci.offset)];
		break;
	    case JREL_F:
		PC = (PC - 1) + machine_types_formOffset(oci.arg);
		break;
	    default:
		bail_with_error("Invalid function code (%d) in machine_execute's OTHC_O computational instruction case!",
				oci.func);
		break;
	    }
	}
	break;
    case syscall_instr_type:
	{
	    syscall_instr_t si = bi.syscall;
	    switch (si.code) {
	    case exit_sc:
		running = false;
		exit(machine_types_sgnExt(si.offset));
		break;
	    case print_str_sc:
		memory.words[GPR[SP]]
		    = printf("%s",
			     (char *) &(memory.words[GPR[si.reg]
						     + machine_types_formOffset(si.offset)]));
		break;
	    case print_int_sc:
		memory.words[GPR[SP]]
		    = printf("%d",
			     memory.words[GPR[si.reg]
					  + machine_types_formOffset(si.offset)]);
		break;
	    case print_char_sc:
		memory.words[GPR[SP]]
		    = fputc(memory.words[GPR[si.reg]
					     + machine_types_formOffset(si.offset)],
			    stdout);
		break;
	    case read_char_sc:
		memory.words[GPR[si.reg] + machine_types_formOffset(si.offset)]
		    = getc(stdin);
		break;
	    case start_tracing_sc:
		tracing = true;
		break;
	    case stop_tracing_sc:
		tracing = false;
		break;
	    default:
		bail_with_error("Invalid system call type (%d) in machine_execute's syscall instruction case!",
				instruction_syscall_number(bi));
		break;
	    }
	}
	break;
    case immed_instr_type:
	{
	    immed_instr_t ii = bi.immed;
	    uimmed_instr_t ui = bi.uimmed;
	    switch (ii.op) {
	    case ADDI_O:
		memory.words[GPR[ii.reg] + machine_types_formOffset(ii.offset)]
		    = memory.words[GPR[ii.reg] + machine_types_formOffset(ii.offset)]
		      + machine_types_sgnExt(ii.immed);
		break;
	    case ANDI_O:
		memory.uwords[GPR[ui.reg] + machine_types_formOffset(ui.offset)]
		    = memory.uwords[GPR[ui.reg]
				    + machine_types_formOffset(ui.offset)]
		      & machine_types_zeroExt(ui.uimmed);
		break;
	    case BORI_O:
		memory.uwords[GPR[ui.reg] + machine_types_formOffset(ui.offset)]
		    = memory.uwords[GPR[ui.reg]
				    + machine_types_formOffset(ui.offset)]
		      | machine_types_zeroExt(ui.uimmed);
		break;
	    case NORI_O:
		memory.uwords[GPR[ui.reg] + machine_types_formOffset(ui.offset)]
		    = ~(memory.uwords[GPR[ui.reg]
				      + machine_types_formOffset(ui.offset)]
			| machine_types_zeroExt(ui.uimmed));
		break;
	    case XORI_O:
		memory.uwords[GPR[ui.reg] + machine_types_formOffset(ui.offset)]
		    = memory.uwords[GPR[ui.reg]
				    + machine_types_formOffset(ui.offset)]
		      ^ machine_types_zeroExt(ui.uimmed);
		break;
	    case BEQ_O:
		if (memory.words[GPR[SP]]
		    == memory.words[GPR[ii.reg]
					+ machine_types_formOffset(ii.offset)]) {
		    PC = (PC - 1) + machine_types_formOffset(ii.immed);
		}
		break;
	    case BGEZ_O:
		if (memory.words[GPR[ii.reg]
				     + machine_types_formOffset(ii.offset)]
		    >= 0) {
		    PC = (PC - 1) + machine_types_formOffset(ii.immed);
		}
		break;
	    case BGTZ_O:
		if (memory.words[GPR[ii.reg]
				     + machine_types_formOffset(ii.offset)]
		    > 0) {
		    PC = (PC - 1) + machine_types_formOffset(ii.immed);
		}
		break;
	    case BLEZ_O:
		if (memory.words[GPR[ii.reg]
				     + machine_types_formOffset(ii.offset)]
		    <= 0) {
		    PC = (PC - 1) + machine_types_formOffset(ii.immed);
		}
		break;
	    case BLTZ_O:
		if (memory.words[GPR[ii.reg]
				     + machine_types_formOffset(ii.offset)]
		    < 0) {
		    PC = (PC - 1) + machine_types_formOffset(ii.immed);
		}
		break;
	    case BNE_O:
		if (memory.words[GPR[SP]]
		    != memory.words[GPR[ii.reg]
					+ machine_types_formOffset(ii.offset)]) {
		    PC = (PC - 1) + machine_types_formOffset(ii.immed);
		}
		break;
	    default:
		bail_with_error("Invalid opcode (%d) in machine_execute's immediate instruction case!",
				ii.op);	    
		break;
	    }
	}
	break;
    case jump_instr_type:
	{
	    jump_instr_t ji = bi.jump;
	    switch (ji.op) {
	    case JMPA_O:
		PC = machine_types_formAddress(PC-1, ji.addr);
		break;
	    case CALL_O:
		GPR[RA] = PC;
		PC = machine_types_formAddress(PC-1, ji.addr);
		break;
	    case RTN_O:
		PC = GPR[RA];
		break;
	    default:
		bail_with_error("Invalid opcode (%d) in machine_execute's jump instruction case!",
				ji.op);	    
		break;
	    }
	}
	break;
    default:
	bail_with_error("Invalid instruction type (%d) in machine_execute!",
			it);
	break;
    }
}

#define    REGFORMAT1 "GPR[%-3s]: %-5d"
#define    REGFORMAT2 "\tGPR[%-3s]: %-5d"

// Requires: out != NULL and is writable
// Print the current values in the registers to out
static void print_registers(FILE *out)
{
    // print the registers
    fprintf(out, "%8s: %u", "PC", PC);
    if (hilo_regs.result != 0L) {
	fprintf(out, "\t%8s: %d\t%8s: %d",
		"HI", hilo_regs.hilo[HI],
		"LO", hilo_regs.hilo[LO]);
    }
    newline(out);

    for (int j = 0; j < (NUM_REGISTERS); /* nothing */) {
	fprintf(out, REGFORMAT1, regname_get(j), GPR[j]);
	j++;
	for (int lc = 0; lc < 4 && j < (NUM_REGISTERS); lc++) {
	    fprintf(out, REGFORMAT2, regname_get(j), GPR[j]);
	    j++;
	}
	newline(out);
    }
}

// Print non-zero global data between the (word) addresses
// GPR[SP] and initial_stack_bottom inclusive
static void print_runtime_stack(FILE *out)
{
    // print the memory between sp and fp, inclusive
    bool printed_nl = print_memory_words_d(out, GPR[SP], initial_stack_bottom);
    if (!printed_nl) {
	newline(out);
    }
}

// Requires: out != NULL and out can be written on
// print the state of the machine (registers, globals, and
// the memory between GPR[$sp] and GPR[$fp], inclusive) to out
void machine_print_state(FILE *out)
{
    print_registers(out);
    print_global_data(out);
    print_runtime_stack(out);
}

// Invariant test for the VM (for debugging purposes)
// This exits with an assertion error if the invariant does not pass
void machine_okay()
{
    assert(0 <= GPR[GP]);
    assert(GPR[GP] < GPR[SP]);
    assert(GPR[SP] <= GPR[FP]);
    assert(GPR[FP] < MEMORY_SIZE_IN_WORDS);
}
