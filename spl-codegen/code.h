/* $Id: code.h,v 1.23 2024/11/10 21:09:43 leavens Exp $ */
#ifndef _CODE_H
#define _CODE_H
#include <stdbool.h>
#include "machine_types.h"
#include "instruction.h"

// SSM assembly language instructions (that can be in linked lists)
typedef struct code_s {
    struct code_s *next;
    bin_instr_t instr;
} code;

// Code creation functions below

// --- computational format instructions from table 3 of the SSM Manual ---

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_nop();

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_add(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_sub(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_cpw(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_cpr(reg_num_type t, reg_num_type s);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_and(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_bor(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_nor(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_xor(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_lwr(reg_num_type t, reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_swr(reg_num_type t, offset_type ot, reg_num_type s);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_sca(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_lwi(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_neg(reg_num_type t, offset_type ot,
		      reg_num_type s, offset_type os);

// --- other computational format instructions from table 4 ---

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_lit(reg_num_type t, offset_type o,
		      immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_ari(reg_num_type r, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_sri(reg_num_type r, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_mul(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_div(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_cfhi(reg_num_type t, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_cflo(reg_num_type t, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_sll(reg_num_type t, offset_type o, shift_type h);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_srl(reg_num_type t, offset_type o, shift_type h);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_jmp(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_csi(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_jrel(offset_type o);

// --- immediate format instructions from table 5 of the SSM Manual ---

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_addi(reg_num_type r, offset_type o, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_andi(reg_num_type r, offset_type o, uimmed_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_bori(reg_num_type r, offset_type o, uimmed_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_nori(reg_num_type r, offset_type o, uimmed_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_beq(reg_num_type r, offset_type o, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_bgez(reg_num_type r, offset_type o, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_bgtz(reg_num_type r, offset_type o, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_blez(reg_num_type r, offset_type o, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_bltz(reg_num_type r, offset_type o, immediate_type i);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_bne(reg_num_type r, offset_type o, immediate_type i);

// --- jump format instructions from table 6 of the SSM Manual ---

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_jmpa(address_type a);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_call(address_type a);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_rtn();

// --- system calls from table 7 of the SSM Manual ---

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_exit(offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_pstr(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_pint(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_pch(reg_num_type s, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_rch(reg_num_type t, offset_type o);

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_stra();

// Create and return a fresh instruction
// with the named mnemonic and parameters
extern code *code_notr();

#endif
