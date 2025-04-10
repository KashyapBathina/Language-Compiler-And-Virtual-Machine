// $Id: code_utils.h,v 1.4 2024/11/10 22:06:54 leavens Exp $
// Some convenience functions that may help with code generation
#ifndef _CODE_UTILS_H
#define _CODE_UTILS_H
#include "code_seq.h"

// Requires: t != SP && s != SP
// Return a code sequence that copies the value from register s
// into register t, using the top of the stack as a temporary.
// Modifies: t (and temporarily, SP)
extern code_seq code_utils_copy_regs(reg_num_type t, reg_num_type s);

// Return a code sequence that loads the static link
// (which is SAVEDSTATIC_LINK_OFFSET from the address contained in register b,
// and place it in register rt.
// Modifies only register rt.
extern code_seq code_utils_load_static_link_into_reg(reg_num_type t,
						     reg_num_type b);

// Requires: reg != FP && reg != RA
// Modifies only: register reg
// Return a code sequence that will put the address that corresponds to the
// frame pointer for the given number of scopes outward in register reg
extern code_seq code_utils_compute_fp(reg_num_type reg, unsigned int levelsOut);

// Requires: words >= 0
// Allocate the given number of words on the runtime stack
// Modifies when executed: SP register
// At the end of exeuction, SP holds the address of the last allocated word.
// (So, if the call allocates only one word, then SP addresses that word.)
extern code_seq code_utils_allocate_stack_space(immediate_type words);

// Requires: words >= 0
// Deallocate the given number of words from the runtime stack
// Modifies when executed: SP register
extern code_seq code_utils_deallocate_stack_space(immediate_type words);

// Set up the runtime stack for a procedure,
// where the static link is found in register $r3.
// Modifies when executed, the SP register, the FP register,
// and memory from SP to SP - MINIMAL_STACK_ALLOC_IN_WORDS
// (inclusive)
extern code_seq code_utils_save_registers_for_AR();

// Restore the callee's registers from the places they are saved on the stack.
// This restores the SP, FP, and RA registers only.
// (It is assumed that the stack already holds the static link address)
// Modifies when executed, the SP register, the FP register, the RA register.
// restoring their saved contents from memory
// (as saved by code_utils_save_registers_for_AR)
extern code_seq code_utils_restore_registers_from_AR();

// Set up the program's stack as if it were in a call (from the OS)
extern code_seq code_utils_set_up_program();

// Tear down the program's stack and exit (with exit code 0).
extern code_seq code_utils_tear_down_program();

#endif
