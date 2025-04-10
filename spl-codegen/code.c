/* $Id: code.c,v 1.29 2024/11/11 23:01:08 leavens Exp $ */
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "utilities.h"
#include "code.h"
#include "regname.h"

// Return a fresh code struct, with next pointer NULL
// containing the given instruction instr.
// If there is not enough space, bail with an error,
// so this will never return NULL.
static code *code_create(bin_instr_t instr)
{
    code *ret = (code *)malloc(sizeof(code));
    if (ret == NULL) {
	bail_with_error("Not enough space to allocate a code struct!");
    }
    ret->next = NULL;
    ret->instr = instr;
    return ret;
}

// --- computational format instructions as in the SSM Manual's table 3 ---

// return a freshly allocated computational-format instruction
static code *create_comp_instr(reg_num_type t, offset_type ot, reg_num_type s,
			       offset_type os, func0_code fc)
{
    comp_instr_t ci;
    ci.op = COMP_O;
    ci.rt = t;
    ci.ot = ot;
    ci.rs = s;
    ci.os = os;
    ci.func = fc;
    bin_instr_t bi;
    bi.comp = ci;
    return code_create(bi);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_nop()
{
    return create_comp_instr(0,0,0,0,NOP_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_add(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, ADD_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_sub(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, SUB_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_cpw(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, CPW_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_cpr(reg_num_type t, reg_num_type s)
{
    return create_comp_instr(t, 0, s, 0, CPR_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_and(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, AND_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_bor(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, BOR_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_nor(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, NOR_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_xor(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, XOR_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_lwr(reg_num_type t, reg_num_type s, offset_type os)
{
    return create_comp_instr(t, 0, s, os, LWR_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_swr(reg_num_type t, offset_type ot, reg_num_type s)
{
    return create_comp_instr(t, ot, s, 0, SWR_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_sca(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, SCA_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_lwi(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, LWI_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_neg(reg_num_type t, offset_type ot,
	       reg_num_type s, offset_type os)
{
    return create_comp_instr(t, ot, s, os, NEG_F);
}


// --- other computational format instructions, in SSM Manual's table 4 ---

// return a freshly allocated computational-format instruction
static code *create_other_comp_instr(reg_num_type t, offset_type o,
				     arg_type a, func1_code fc)
{
    other_comp_instr_t oci;
    oci.op = OTHC_O;
    oci.reg = t;
    oci.offset = o;
    oci.arg = a;
    oci.func = fc;
    bin_instr_t bi;
    bi.othc = oci;
    return code_create(bi);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_lit(reg_num_type t, offset_type ot, immediate_type i)
{
    return create_other_comp_instr(t, ot, i, LIT_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_ari(reg_num_type r, immediate_type i)
{
    return create_other_comp_instr(r, 0, i, ARI_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_sri(reg_num_type r, immediate_type i)
{
    return create_other_comp_instr(r, 0, i, SRI_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_mul(reg_num_type s, offset_type o)
{
    return create_other_comp_instr(s, o, 0, MUL_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_div(reg_num_type s, offset_type o)
{
    return create_other_comp_instr(s, o, 0, DIV_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_cfhi(reg_num_type t, offset_type o)
{
    return create_other_comp_instr(t, o, 0, CFHI_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_cflo(reg_num_type t, offset_type o)
{
    return create_other_comp_instr(t, o, 0, CFLO_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_sll(reg_num_type t, offset_type o, shift_type h)
{
    return create_other_comp_instr(t, o, h, SLL_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_srl(reg_num_type t, offset_type o, shift_type h)
{
    return create_other_comp_instr(t, o, h, SLL_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_jmp(reg_num_type s, offset_type o)
{
    return create_other_comp_instr(s, o, 0, JMP_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_csi(reg_num_type s, offset_type o)
{
    return create_other_comp_instr(s, o, 0, CSI_F);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_jrel(offset_type o)
{
    return create_other_comp_instr(0, 0, o, JREL_F);
}


// --- immediate format instructions, in SSM Manual's table 5 ---

// return a fresh immediate-type instruction
// (with a signed immediate operand)
static code *create_immed_instr(op_code op, reg_num_type r,
				offset_type o, immediate_type i)
{
    immed_instr_t ii;
    ii.op = op;
    ii.reg = r;
    ii.offset = o;
    ii.immed = i;  // this is sign extended by the VM, not here!
    bin_instr_t bi;
    bi.immed = ii;
    return code_create(bi);
}

// return a fresh immediate-type instruction
// (with an unsigned immediate operand)
static code *create_uimmed_instr(op_code op, reg_num_type r,
				 offset_type o, uimmed_type u)
{
    uimmed_instr_t ui;
    ui.op = op;
    ui.reg = r;
    ui.offset = o;
    ui.uimmed = u; 
    bin_instr_t bi;
    bi.uimmed = ui;
    return code_create(bi);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_addi(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(ADDI_O, r, o, i);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_andi(reg_num_type r, offset_type o, uimmed_type u)
{
    return create_uimmed_instr(ANDI_O, r, o, u);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_bori(reg_num_type r, offset_type o, uimmed_type u)
{
    return create_uimmed_instr(BORI_O, r, o, u);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_nori(reg_num_type r, offset_type o, uimmed_type u)
{
    return create_uimmed_instr(NORI_O, r, o, u);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_xori(reg_num_type r, offset_type o, uimmed_type u)
{
    return create_uimmed_instr(XORI_O, r, o, u);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_beq(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(BEQ_O, r, o, i);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_bgez(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(BGEZ_O, r, o, i);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_bgtz(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(BGTZ_O, r, o, i);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_blez(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(BLEZ_O, r, o, i);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_bltz(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(BLTZ_O, r, o, i);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_bne(reg_num_type r, offset_type o, immediate_type i)
{
    return create_immed_instr(BNE_O, r, o, i);
}

// --- jump format instructions, in SSM Manual's table 6 ---

// return a fresh jump-type instruction
static code *create_jump_instr(op_code op, address_type a)
{
    jump_instr_t ji;
    ji.op = op;
    ji.addr = a;
    bin_instr_t bi;
    bi.jump = ji;
    return code_create(bi);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_jmpa(address_type a)
{
    return create_jump_instr(JMPA_O, a);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_call(address_type a)
{
    code *ret = create_jump_instr(CALL_O, a);
    return ret;
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_rtn()
{
    code *ret = create_jump_instr(RTN_O, 0);
    return ret;
}

// --- system call instructions, in SSM Manual's table 7 ---

// return a fresh syscall-type instruction
static code *create_syscall_instr(syscall_type t, reg_num_type r, offset_type o)
{
    syscall_instr_t si;
    si.op = OTHC_O;
    si.reg = r;
    si.offset = o;
    si.code = t;
    si.func = SYS_F;
    bin_instr_t bi;
    bi.syscall = si;
    return code_create(bi);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_exit(offset_type o)
{
    return create_syscall_instr(exit_sc, 0, o);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_pstr(reg_num_type s, offset_type o)
{
    return create_syscall_instr(print_str_sc, s, o);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_pint(reg_num_type s, offset_type o)
{
    return create_syscall_instr(print_int_sc, s, o);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_pch(reg_num_type s, offset_type o)
{
    return create_syscall_instr(print_char_sc, s, o);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_rch(reg_num_type t, offset_type o)
{
    return create_syscall_instr(read_char_sc, t, o);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_stra()
{
    return create_syscall_instr(start_tracing_sc,0,0);
}

// Create and return a fresh instruction
// with the named mnemonic and parameters
code *code_notr()
{
    return create_syscall_instr(stop_tracing_sc,0,0);
}

