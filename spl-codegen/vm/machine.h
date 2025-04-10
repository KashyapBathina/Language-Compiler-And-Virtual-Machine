/* $Id: machine.h,v 1.16 2024/11/10 13:22:31 leavens Exp $ */
#ifndef _MACHINE_H
#define _MACHINE_H
#include <assert.h>
#include "machine_types.h"
#include "bof.h"
#include "instruction.h"

// a size for the memory (2^16 = 32K words)
#define MEMORY_SIZE_IN_WORDS 32768

// Requires: bf is open for reading in binary
// Load the binary object file bf, and get ready to run it
extern void machine_load(BOFFILE bf);

// Requires: a program has been loaded into the computer's memory
// print a heading and the program in the VM's memory to out
extern void machine_print_loaded_program(FILE *out);

// Run the VM on the already loaded program,
// producing any trace output called for by the program
// if trace_execution is true
extern void machine_run(bool trace_execution);

// Load the given binary object file and run it
extern void machine_load_and_run(BOFFILE bf, bool trace_execution);

// If tracing then print bi, execute bi (always),
// then if tracing print out the machine's state.
// All tracing output goes to the FILE out
extern void machine_trace_execute_instr(FILE *out, address_type addr,
					bin_instr_t bi);

// Execute the given instruction, which is found at address addr,
// in the machine's current state
extern void machine_execute_instr(address_type addr, bin_instr_t bi);

// Print instr, execute instr, then print out the machine's state (to out)
extern void machine_trace_execute(FILE *out, bin_instr_t instr);

// Requires: out != NULL and out can be written on
// print the state of the machine (registers, globals, and
// the memory between GPR[$sp] and GPR[$fp], inclusive) to out
extern void machine_print_state(FILE *out);

// Invariant test for the VM (for debugging purposes)
// This exits with an assertion error if the invariant does not pass
extern void machine_okay();

#endif
