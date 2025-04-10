#include "bof.h"
#include "instruction.h"
#include "machine_types.h"
#include "regname.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// Define constants for registers
#define GP 0
#define SP 1
#define FP 2
#define RA 7

// Define the number of general-purpose registers
#define NUM_REGISTERS 8

// Define the size of memory (32K words)
#define MEMORY_SIZE_IN_WORDS 32768

// Define the memory union
union mem_u {
    word_type words[MEMORY_SIZE_IN_WORDS];
    uword_type uwords[MEMORY_SIZE_IN_WORDS];
    bin_instr_t instrs[MEMORY_SIZE_IN_WORDS];
} memory;

// Define VM state
word_type registers[NUM_REGISTERS]; // $gp, $sp, $fp, $r3, $r4, $r5, $r6, $ra
word_type PC;                        // Program Counter
word_type HI, LO;                    // Special registers

// Tracing flag
bool tracing = true;

// System call codes
#define EXIT_SC 1            // Exit system call code
#define PRINT_STR_SC 3       // Print string system call code
#define START_TRACING_SC 2046  // Start tracing system call code
#define STOP_TRACING_SC 2047   // Stop tracing system call code

// Function Prototypes
void load_bof(const char *filename, BOFHeader *header);
void print_program(const BOFHeader *header);
void execute_program(const BOFHeader *header);
void execute_instruction(bin_instr_t instr);
void handle_system_call(bin_instr_t instr);
void print_vm_state(address_type addr, bin_instr_t instr);
bool check_invariants(const BOFHeader *header);

// Main function
int main(int argc, char *argv[]) {
    if (argc < 2) {
        bail_with_error("Usage: %s [-p] <filename.bof>", argv[0]);
    }

    int arg_index = 1;
    bool print_flag = false;

    // Check for -p flag
    if (strcmp(argv[arg_index], "-p") == 0) {
        print_flag = true;
        arg_index++;
        if (argc < 3) {
            bail_with_error("Usage: %s [-p] <filename.bof>", argv[0]);
        }
    }

    const char *filename = argv[arg_index];

    BOFHeader header;

    // Load BOF file
    load_bof(filename, &header);

    // Initialize registers based on header
    registers[GP] = header.data_start_address;
    registers[SP] = header.stack_bottom_addr;
    registers[FP] = header.stack_bottom_addr;
    PC = header.text_start_address;
    HI = 0;
    LO = 0;

    // Check VM invariants
    if (!check_invariants(&header)) {
        bail_with_error("VM invariants violated after initialization.");
    }

    if (print_flag) { // Handle -p flag
        print_program(&header);
        exit(EXIT_SUCCESS);
    }
    else {// Execute the program
        execute_program(&header);
    }
    return 0;
}

// Function to load BOF file into memory
void load_bof(const char *filename, BOFHeader *header) {
    BOFFILE bof = bof_read_open(filename);

    // Read BOF header
    *header = bof_read_header(bof);

    // Load instructions into memory
    for (word_type addr = header->text_start_address; addr < (header->text_start_address + header->text_length); addr++) {
        memory.instrs[addr] = instruction_read(bof);
    }

    // Load data section into memory
    for (word_type addr = header->data_start_address; addr < (header->data_start_address + header->data_length); addr++) {
        memory.words[addr] = bof_read_word(bof);
    }

    bof_close(bof);
}

// Function to print the program in assembly form
void print_program(const BOFHeader *header) {
    printf("Address Instruction\n");
    // Print instructions
    for (word_type addr = header->text_start_address; addr < (header->text_start_address + header->text_length); addr++) {
        bin_instr_t instr = memory.instrs[addr];
        const char *asm_form = instruction_assembly_form(addr, instr);
        printf("%6u: %s\n", addr, asm_form);
    }
    

    // Print data
    int chars_in_line = 0;
    for (word_type addr = header->data_start_address; addr <= (header->data_start_address + header->data_length); addr++) {
        // handling zeroes and otherwise
        if (memory.words[addr] == 0) {            
            chars_in_line += printf("%8d: %d\t", addr, memory.words[addr]);
            
                
            if (addr!= (header->data_start_address + header->data_length) && memory.words[addr+1] == 0) {
                while (memory.words[addr]==0 && addr!=header->data_start_address + header->data_length) {
                    addr++;
                }
                if (addr!=header->data_start_address + header->data_length) chars_in_line += printf("...\t");
            }
        }
        else {
            chars_in_line += printf("%8d: %d\t", addr, memory.words[addr]);
        }
        
        
        //int temp_count = snprintf(NULL, 0, "%d: %d", addr, memory.words[addr]);
        if (chars_in_line /*+ temp_count */ > 59) {
            printf("\n");
            chars_in_line = 0;
        }
    }
    printf("...");
    printf("\n");
}


// Function to execute the program
void execute_program(const BOFHeader *header) {
    
    // Ensure the loop runs until the last instruction in the text section
    while (PC < header->text_start_address + header->text_length) {
        bin_instr_t instr = memory.instrs[PC];
        address_type current_addr = PC;

        // If the instruction is EXIT, print and stop the loop
        const char *asm_form = instruction_assembly_form(current_addr, instr);
        if (strcmp(asm_form, "EXIT 0") == 0) {
            // Print the final state before exiting
            if (tracing) print_vm_state(current_addr, instr);
            break;  // Exit loop after processing the EXIT instruction
        }
        
        
        // Handle tracing if enabled
        if (tracing) {
            print_vm_state(current_addr, instr);
        }
        PC++;
        // Execute the instruction
        execute_instruction(instr);
        

        // Increment PC after processing the instruction
    }
}



// Function to execute a single instruction
void execute_instruction(bin_instr_t instr) {
    instr_type it = instruction_type(instr);

    switch (it) {
        case comp_instr_type:
            switch (instr.comp.func) {
                case ADD_F:
                    //add
                    //word_type offset = machine_types_formOffset(instr.immed.offset);
                    //printf("%d", offset);
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.words[registers[SP]] + (memory.words[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]);
                    break;
                case SUB_F:
                    // sub
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.words[registers[SP]] - (memory.words[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]);
                    break;
                case CPW_F:
                    // Copy word
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.words[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)];
                    break;
                case AND_F:
                    // AND
                    memory.uwords[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.uwords[registers[SP]] & (memory.uwords[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]);
                    break;
                case BOR_F:
                    // OR
                    memory.uwords[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.uwords[registers[SP]] | (memory.uwords[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]);
                    break;
                case NOR_F:
                    // NOR
                    memory.uwords[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = ~(memory.uwords[registers[SP]] | (memory.uwords[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]));
                    break;
                case XOR_F:
                    // XOR
                    memory.uwords[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.uwords[registers[SP]] ^ (memory.uwords[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]);
                    break;
                case LWR_F:
                    // Load the word from the calculated memory location into the register
                    registers[instr.comp.rt] = memory.words[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)];
                    break;
                case SWR_F:
                    // Store the word at the calculated memory location
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = registers[instr.comp.rs];
                    break;
                case SCA_F:
                    // store computed address
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os);
                    break;
                case LWI_F:
                    // load word indirect
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = memory.words[memory.words[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)]];
                    break;
                case NEG_F:
                    // neg
                    memory.words[registers[instr.comp.rt] + machine_types_formOffset(instr.comp.ot)] = -memory.words[registers[instr.comp.rs] + machine_types_formOffset(instr.comp.os)];
                    break;
            }
        break;
            
            
            
        case other_comp_instr_type:
            switch (instr.othc.func) {
                case LIT_F:
                    // load
                    memory.words[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)] = machine_types_sgnExt(instr.othc.arg);
                    break;
                case ARI_F:
                    // add register immeditae 
                    registers[instr.othc.reg] += machine_types_sgnExt(instr.othc.arg);
                    break;
                case SRI_F:
                    // sub register immeditae 
                    registers[instr.othc.reg] -= machine_types_sgnExt(instr.othc.arg);
                    break;
                case MUL_F:
                    // multiply
                    unsigned long long product = (unsigned long long) (memory.words[registers[SP]]) * (unsigned long long) ( (unsigned long long)memory.words[registers[instr.othc.reg] + (unsigned long long) machine_types_formOffset(instr.othc.offset)]);
                    HI = (word_type)(product >> 32); 
                    LO = (word_type)(product & 0xFFFFFFFF);
                    break;
                case DIV_F:
                    // divide
                    HI = memory.words[registers[SP]] % (memory.words[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)]);
                    LO = memory.words[registers[SP]] / (memory.words[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)]);
                    break;
                case CFHI_F:
                    // copy from HI
                    memory.words[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)] = HI;
                    break;
                case CFLO_F:
                    // copy from LO
                    memory.words[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)] = LO;
                    break;
                case SLL_F:
                    // shift left
                    memory.uwords[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)] = memory.uwords[registers[SP]] << instr.othc.arg;
                    break;
                case SRL_F:
                    // shift right
                    memory.uwords[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)] = memory.uwords[registers[SP]] >> instr.othc.arg;
                    break;
                case JMP_F:
                    // jump
                    PC = memory.uwords[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)];
                    break;
                case CSI_F:
                    // call subroutine indirect
                    registers[RA] = PC;
                    PC = memory.words[registers[instr.othc.reg] + machine_types_formOffset(instr.othc.offset)];
                    break;
                case JREL_F:
                    // jump relative to address
                    PC = ((PC-1) + machine_types_formOffset(instr.othc.offset));
                    break;
            }
        break;
            
            
            
        case syscall_instr_type:
            switch (instr.syscall.code) {
                case exit_sc:
                    // exit 
                    exit(machine_types_sgnExt(instr.syscall.offset));
                    break;
                case print_str_sc:
                    // print str
                    memory.words[registers[SP]] = printf("%s", (char*)&memory.words[registers[instr.syscall.reg] + machine_types_formOffset(instr.syscall.offset)]);
                    break;
                case print_char_sc:
                    // print char
                    memory.words[registers[SP]] = fputc((char)memory.words[registers[instr.syscall.reg] + machine_types_formOffset(instr.syscall.offset)], stdout);
                    break;
                case print_int_sc:
                    // print int;
                    memory.words[registers[SP]] = printf("%d", memory.words[registers[instr.syscall.reg] + machine_types_formOffset(instr.syscall.offset)]);
                    break;
                case read_char_sc:
                    // read char
                    memory.words[registers[instr.syscall.reg] + machine_types_formOffset(instr.syscall.offset)] = getc(stdin);
                    break;
                case start_tracing_sc:
                    // VM trace
                    tracing = true;
                    break;
                case stop_tracing_sc:
                    // dont VM trace
                    tracing = false;
                    break;
            }
        break;



        case immed_instr_type:
            switch (instr.immed.op) {
                case ADDI_O:
                    // add immediate
                    memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)] += machine_types_zeroExt(instr.immed.immed);
                    break;
                case ANDI_O:
                    // and immediate
                    memory.uwords[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)] &= machine_types_zeroExt(instr.immed.immed);
                    break;
                case BORI_O:
                    // or immediate
                    memory.uwords[registers[instr.uimmed.reg] + machine_types_formOffset(instr.uimmed.offset)] |= machine_types_zeroExt(instr.uimmed.uimmed);
                    break;
                case NORI_O:
                    // nor immediate
                    memory.uwords[registers[instr.uimmed.reg] + machine_types_formOffset(instr.uimmed.offset)] = ~(memory.uwords[registers[instr.uimmed.reg] + machine_types_formOffset(instr.uimmed.offset)]) | machine_types_zeroExt(instr.uimmed.uimmed);
                    break;
                case XORI_O:
                    // xor immediate
                    memory.uwords[registers[instr.uimmed.reg] + machine_types_formOffset(instr.uimmed.offset)] = (memory.uwords[registers[instr.uimmed.reg] + machine_types_formOffset(instr.uimmed.offset)]) ^ machine_types_zeroExt(instr.uimmed.uimmed);
                    break;
                case BEQ_O:
                    // branch equal
                    if (memory.words[registers[SP]] == memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)]) {
                        PC = (PC-1) + machine_types_formOffset(instr.immed.immed);
                    }
                    break;
                case BGEZ_O:
                    // branch >=0 
                    if (memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)] >= 0) {
                        PC = (PC-1) + machine_types_formOffset(instr.immed.immed);
                    }
                    break;
                case BGTZ_O:
                    // branch >0 
                    if (memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)] > 0) {
                        PC = (PC-1) + machine_types_formOffset(instr.immed.immed);
                    }
                    break;
                case BLEZ_O:
                    // branch <= 0 
                    if (memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)] <= 0) {
                        PC = (PC-1) + machine_types_formOffset(instr.immed.immed);
                    }
                    break;
                case BLTZ_O:
                    // branch < 0 
                    if (memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)] < 0) {
                        PC = (PC-1) + machine_types_formOffset(instr.immed.immed);
                    }
                    break;
                case BNE_O:
                    // branch != 
                    if (memory.words[registers[SP]] != memory.words[registers[instr.immed.reg] + machine_types_formOffset(instr.immed.offset)]) {
                        PC = (PC-1) + machine_types_formOffset(instr.immed.immed);
                    }
                    break;
            }
        break;
            
            
            
        case jump_instr_type:
            switch (instr.jump.op) {
                case JMPA_O:
                    // jump to address
                    PC = machine_types_formAddress(PC-1, instr.jump.addr);
                    break;
                case CALL_O:
                    // call subroutine
                    registers[RA] = PC;
                    PC = machine_types_formAddress(PC-1, instr.jump.addr);
                    break;
                case RTN_O:
                    // return from subroutine
                    PC = registers[RA];
                    break;
            }
        break;

        default:
            break;
    }
}


// Function to print the VM's state for tracing
void print_vm_state(address_type addr, bin_instr_t instr) {
    printf("      PC: %u", PC);
    if (HI!=0 || LO!=0) {
        printf("         HI: %d           LO: %d", HI, LO);
    }
    printf("\n");
    int chars_in_line = 0;
    for (int i = 0; i < NUM_REGISTERS; i++) { // printing registers
        chars_in_line += printf("GPR[%s]: %d\t", regname_get(i), registers[i]);
        if (chars_in_line>59) {
            printf("\n");
            chars_in_line = 0;
        }
    }
    printf("\n");

        
        
    // Print data
    int consec_zeroes = 0;
    chars_in_line = 0;
    for (word_type addr = registers[GP]; addr <= registers[FP]; addr++) {
        if (addr == registers[SP]) {
            printf("\n");
            chars_in_line = printf("%8d: %d\t", registers[SP], memory.words[registers[SP]]);
            consec_zeroes = 0;
        }
        if (memory.words[addr] == 0) {   
            if (consec_zeroes == 0) {         
                if (addr!=registers[SP]) chars_in_line += printf("%8d: %d\t", addr, memory.words[addr]);
                consec_zeroes = 1;
            }
                
            else if (consec_zeroes==1) {
                chars_in_line += printf("        ...     ");
                consec_zeroes = 2;
            }
        }
        else {
            if (addr!=registers[SP]) chars_in_line += printf("%8d: %d\t", addr, memory.words[addr]);
            consec_zeroes=0;
        }
        
        
        if (chars_in_line > 59) {
            printf("\n");
            chars_in_line = 0;
        }
    }
    printf("\n");
    
    



    const char *asm_form = instruction_assembly_form(addr, instr);
    printf("\n");
    printf("==> %u: %s\n", addr, asm_form);
}


// Function to check VM invariants
bool check_invariants(const BOFHeader *header) {
    if (registers[GP] < 0 || registers[SP] > registers[FP] || PC >= MEMORY_SIZE_IN_WORDS) {
        return false;
    }
    return true;
}