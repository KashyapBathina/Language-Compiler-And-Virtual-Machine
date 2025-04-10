// $Id: code_utils.c,v 1.12 2024/11/18 22:03:45 leavens Exp leavens $
#include <assert.h>
#include "regname.h"
#include "code.h"
#include "code_seq.h"
#include "code_utils.h"

#define MINIMAL_STACK_ALLOC_IN_WORDS 4
#define SAVED_SP_OFFSET (-1)
#define SAVED_FP_OFFSET (-2)
#define SAVED_STATIC_LINK_OFFSET (-3)
#define SAVED_RA_OFFSET (-4)

// Requires: t != SP && s != SP, if the VM has no CPR instruction
// Return a code sequence that copies the value from register s
// into register t.
// If the VM has no CPR instruction, then this uses
// the top of the stack as a temporary and so modifies SP.
code_seq code_utils_copy_regs(reg_num_type t, reg_num_type s)
{
    code_seq ret = code_seq_singleton(code_cpr(t, s));
    // If the SSM didn't have the cpr instruction
    // one could use the top of the stack as a temporary, as follows
    /*
    code_seq ret = code_utils_allocate_stack_space(1);
    code_seq_add_to_end(&ret, code_swr(SP, 0, s));
    code_seq_add_to_end(&ret, code_lwr(t, SP, 0));
    code_seq_concat(&ret, code_utils_deallocate_stack_space(1));
    */
    return ret;
}

// Return a code sequence that loads the static link
// (which is SAVEDSTATIC_LINK_OFFSET from the address contained in register b,
// and place it in register rt.
// Modifies only register rt.
code_seq code_utils_load_static_link_into_reg(reg_num_type t,
					      reg_num_type b)
{
    code_seq ret = code_seq_singleton(code_lwr(t, b, SAVED_STATIC_LINK_OFFSET));
    return ret;
}

// Requires: reg != FP && reg != RA
// Modifies only: register reg
// Return a code sequence that will put the address that corresponds to the
// frame pointer for the given number of scopes outward in register reg
code_seq code_utils_compute_fp(reg_num_type reg, unsigned int levelsOut)
{
    // start in the current AR (so levelsOut == 0 addresses locals properly)
    assert(reg != FP && reg != RA);
    code_seq ret
	= code_utils_copy_regs(reg, FP);
    while (levelsOut > 0) {
	code_seq_concat(&ret,
			code_utils_load_static_link_into_reg(reg, reg));
	levelsOut--;
    }
    return ret;
}

// Requires: words >= 0
// Allocate the given number of words on the runtime stack
// Modifies when executed: SP register
// At the end of exeuction, SP holds the address of the last allocated word.
// (So, if the call allocates only one word, then SP addresses that word.)
code_seq code_utils_allocate_stack_space(immediate_type words)
{
    assert(words >= 0);
    code_seq ret = code_seq_singleton(code_sri(SP, words));
    return ret;
}

// Requires: words >= 0
// Deallocate the given number of words from the runtime stack
// Modifies when executed: SP register
code_seq code_utils_deallocate_stack_space(immediate_type words)
{
    assert(words >= 0);
    code_seq ret = code_seq_singleton(code_ari(SP, words));
    return ret;
}

// Requires: $r3 holds the static link (from the current AR)
// Set up the runtime stack for a procedure,
// where the static link is found in register $r3.
// Modifies when executed, the SP register, the FP register, $r3,
// and memory from SP to SP - MINIMAL_STACK_ALLOC_IN_WORDS
// (inclusive)
code_seq code_utils_save_registers_for_AR()
{
    // assume that SP is pointing to the lowest local storage already allocated
    code_seq ret;
    // save SP onto the top of the stack
    ret = code_seq_singleton(code_swr(SP, SAVED_SP_OFFSET, SP));
    // save FP (dynamic link) onto top of the stack
    code_seq_add_to_end(&ret, code_swr(SP, SAVED_FP_OFFSET, FP));
    // save the static link from $r3 onto top of stack
    code_seq_add_to_end(&ret, code_swr(SP, SAVED_STATIC_LINK_OFFSET, 3));
    // save the RA register on the stack
    code_seq_add_to_end(&ret, code_swr(SP, SAVED_RA_OFFSET, RA));
    // save SP into the FP register so FP points to the base of the AR
    // can't use code_utils_copy_regs for this because SP is involved
    code_seq_add_to_end(&ret, code_cpr(FP, SP));
    /* the following can be used if there is no cpr instruction:
    code_seq_add_to_end(&ret, SAVED_RA_OFFSET-1, SP));
    code_seq_add_to_end(&ret, code_lwr(FP, SP, SAVED_RA_OFFSET-1));
    */

    // allocate the space on the stack for the saved registers
    code_seq_concat(&ret,
		    code_utils_allocate_stack_space(MINIMAL_STACK_ALLOC_IN_WORDS));

    return ret;
}

// Restore the callee's registers from the places they are saved on the stack.
// This restores the SP, FP, and RA registers only.
// (It is assumed that the stack already holds the static link address)
// Modifies when executed, the SP register, the FP register, the RA register
// and the $r3 register, restoring the saved contents of SP, FP, and RA
// from memory (as saved by code_utils_save_registers_for_AR).
code_seq code_utils_restore_registers_from_AR()
{
    code_seq ret = code_seq_empty();
    // restore the RA register
    code_seq_add_to_end(&ret,
			code_lwr(RA, FP, SAVED_RA_OFFSET));
    // save the SP register in $r3 temporarily, to not violate VM's invariant
    code_seq_add_to_end(&ret, code_lwr(3, FP, SAVED_SP_OFFSET));
    // restore the FP (dynamic link) register
    code_seq_add_to_end(&ret, code_lwr(FP, FP, SAVED_FP_OFFSET));
    // deallocate the space for variables and constants by restoring old SP
    code_seq_add_to_end(&ret, code_cpr(SP, 3));
    return ret;
}

// Set up the program's stack as if it were in a call (from the OS)
code_seq code_utils_set_up_program()
{
    code_seq ret;
    // set up the saved registers
    ret = code_utils_copy_regs(3, FP);  // save FP into $r3
    code_seq_concat(&ret, code_utils_save_registers_for_AR());
    return ret;
}

// Tear down the program's stack and exit (with exit code 0).
code_seq code_utils_tear_down_program()
{
    code_seq ret;
    // restore the saved registers to their initial state
    ret = code_utils_restore_registers_from_AR();
    code_seq_add_to_end(&ret, code_exit(0));
    return ret;
}
