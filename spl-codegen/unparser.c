/* $Id: unparser.c,v 1.11 2024/10/23 13:38:20 leavens Exp $ */
#include <stdio.h>
#include <assert.h>
#include "unparser.h"
#include "utilities.h"

// Amount of spaces to indent per nesting level
#define SPACES_PER_LEVEL 2

// Print SPACES_PER_LEVEL * level spaces to out
static void indent(FILE *out, int level)
{
    int num = SPACES_PER_LEVEL * level;
    for (int i = 0; i < num; i++) {
	fprintf(out, " ");
    }
}

// Print (to out) a semicolon, but only if addSemiToEnd is true,
// and then print a newline.
static void newlineAndOptionalSemi(FILE *out, bool addSemiToEnd)
{
    fprintf(out, "%s\n", (addSemiToEnd ? ";" : ""));
}

// Unparse the given program AST and then print a period and an newline
void unparseProgram(FILE *out, block_t prog)
{
    unparseBlock(out, prog, 0, false);
    fprintf(out, ".\n");
}

// Unparse the given block, indented by the given level, to out
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseBlock(FILE *out, block_t blk, int level,
			 bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "begin\n");
    unparseConstDecls(out, blk.const_decls, level+1);
    unparseVarDecls(out, blk.var_decls, level+1);
    unparseProcDecls(out, blk.proc_decls, level+1);
    unparseStmts(out, blk.stmts, level+1);
    indent(out, level);
    fprintf(out, "end");
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the list of const-decls given by the AST cds to out
// with the given nesting level
// (note that if cds == NULL, then nothing is printed)
void unparseConstDecls(FILE *out, const_decls_t cds, int level)
{
    // debug_print("unparseConstDecls entry ...\n");
    assert(cds.type_tag == const_decls_ast);
    const_decl_t *cd_listp = cds.start;
    while (cd_listp != NULL) {
	unparseConstDecl(out, *cd_listp, level);
	cd_listp = cd_listp->next;
    }
}

// Unparse a single const-def given by the AST cd to out,
// indented for the given nesting level
void unparseConstDecl(FILE *out, const_decl_t cd, int level)
{
    // debug_print("unparseConstDecl entry ...\n");
    indent(out, level);
    fprintf(out, "const ");
    unparseConstDefList(out, cd.const_def_list, level);
}

// Unparse the list of const-defs given by the AST cdl to out
// with the given nesting level, followed by a semicolon and a newline.
void unparseConstDefList(FILE *out, const_def_list_t cdl, int level)
{
    // debug_print("unparseConstDefList entry ...\n");
    assert(cdl.type_tag == const_def_list_ast);
    bool printed_already = false;
    const_def_t *cdp = cdl.start;
    while (cdp != NULL) {
	if (printed_already) {
	    fprintf(out, ", ");
	}
	unparseConstDef(out, *cdp, level);
	printed_already = true;
	cdp = cdp->next;
    }
    fprintf(out, ";\n");
}

// Unparse the const-def given by the AST cdf to out
// with the given nesting level
extern void unparseConstDef(FILE *out, const_def_t cdf, int level)
{
    fprintf(out, "%s = %d", cdf.ident.name, cdf.number.value);
}

// Unparse the list of vart-decls given by the AST vds to out
// with the given nesting level
// (note that if vds.var_decls == NULL, then nothing is printed)
void unparseVarDecls(FILE *out, var_decls_t vds, int level)
{
    // debug_print("Entering unparseVarDecls ...\n");
    assert(vds.type_tag == var_decls_ast);
    var_decl_t *vdp = vds.var_decls;
    while (vdp != NULL) {
	unparseVarDecl(out, *vdp, level);
	vdp = vdp->next;
    }
}

// Unparse a single var-decl given by the AST vd to out,
// indented for the given nesting level
void unparseVarDecl(FILE *out, var_decl_t vd, int level)
{
    // debug_print("Entering unparseVarDecl ...\n");
    indent(out, level);
    fprintf(out, "var");
    unparseIdentList(out, vd.ident_list);
    fprintf(out, ";\n");
}

// Unparse the identifiers in idents to out, with a space before each,
// and a comma as a separator
void unparseIdentList(FILE *out, ident_list_t ident_list)
{
    // debug_print("Entering unparseIdentList ...\n");
    ident_t *ip = ident_list.start;
    bool already_printed =false;
    while (ip != NULL) {
	// debug_print("in unparseIdents ip is %x\n", ip);
	// debug_print("in unparseIdents ip->name is %s\n", ip->name);
	if (already_printed) {
	    fprintf(out, ", %s", ip->name);
	} else {
	    fprintf(out, " %s", ip->name);
	}
	already_printed = true;
	ip = ip->next;
    }
}

// Unparse the list of proc-decls given by the AST pds to out
// with the given nesting level
// (note that if pds.proc_decls is NULL, then nothing is printed)
void unparseProcDecls(FILE *out, proc_decls_t pds, int level)
{
    // debug_print("unparseProcDecls entry ...\n");
    assert(pds.type_tag == proc_decls_ast);
    proc_decl_t *pdp = pds.proc_decls;
    while (pdp != NULL) {
	unparseProcDecl(out, *pdp, level);
	pdp = pdp ->next;
    }
}

// Unparse the given proc-decl given by the AST pd to out
// with the given nesting level followed by a semicolon
void unparseProcDecl(FILE *out, proc_decl_t pd, int level)
{
    // debug_print("unparseProcDecl entry ...\n");
    indent(out, level);
    fprintf(out, "proc %s\n", pd.name);
    unparseBlock(out, *(pd.block), level, true);
}


// Unparse the stmts given by stmt to out
// with indentation level given by level.
// (The statements always occur before an end, so a semicolon is never added.)
void unparseStmts(FILE *out, stmts_t stmts, int level)
{
    // indent(out, level);
    // fprintf(out, "%% stmts at level %d\n", level);
    if (stmts.stmts_kind != empty_stmts_e) {
	stmt_list_t sl = stmts.stmt_list;
	unparseStmtList(out, sl, level, false);
    }
}

// Unparse the stmts given by stmt to out
// with indentation level given by level,
// and add a semicolon at the end if addSemiToEnd is true.
void unparseStmtList(FILE *out, stmt_list_t stmt_list, int level,
		     bool addSemiToEnd)
{
    // indent(out, level);
    // fprintf(out, "%% stmtList at level %d\n", level);    
    stmt_t *s = stmt_list.start;
    while (s != NULL) {
	unparseStmt(out, *s, level, addSemiToEnd || (s->next != NULL));
	s = s->next;
    }
}

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToENd is true.
void unparseStmt(FILE *out, stmt_t stmt, int level, bool addSemiToEnd)
{
    // debug_print("In unparseStmt stmt.type_tag is %d\n", stmt.type_tag);
    assert(stmt.type_tag == stmt_ast);
    switch (stmt.stmt_kind) {
    case assign_stmt:
	assert(stmt.data.assign_stmt.type_tag == assign_stmt_ast);
	unparseAssignStmt(out, stmt.data.assign_stmt, level, addSemiToEnd);
	break;
    case call_stmt:
	unparseCallStmt(out, stmt.data.call_stmt, level, addSemiToEnd);
	break;
    case if_stmt:
	unparseIfStmt(out, stmt.data.if_stmt, level, addSemiToEnd);
	break;
    case while_stmt:
	unparseWhileStmt(out, stmt.data.while_stmt, level, addSemiToEnd);
	break;
    case read_stmt:
	unparseReadStmt(out, stmt.data.read_stmt, level, addSemiToEnd);
	break;
    case print_stmt:
	unparsePrintStmt(out, stmt.data.print_stmt, level, addSemiToEnd);
	break;
    case block_stmt:
	unparseBlockStmt(out, stmt.data.block_stmt, level, addSemiToEnd);
	break;
    default:
	bail_with_error("Unknown stmt_kind (%d) in unparseStmt!",
			stmt.stmt_kind);
	break;
    }
}

// Unparse the assignment statment given by stmt to out
// with indentation level given by level,
// and add a semicolon at the end if addSemiToEnd is true.
void unparseAssignStmt(FILE *out, assign_stmt_t stmt, int level,
			      bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "%s := ", stmt.name);
    if (stmt.expr == NULL) {
	bail_with_error("Found null expression in assignment statment!");
    }
    unparseExpr(out, *(stmt.expr));
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the call statment given by stmt to out
// with indentation level given by level,
// and add a semicolon at the end if addSemiToEnd is true.
void unparseCallStmt(FILE *out, call_stmt_t stmt, int level,
			    bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "call %s", stmt.name);
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the sequential statment given by stmt to out
// with indentation level given by level (indenting the body one more level)
// and add a semicolon at the end if addSemiToEnd is true.
void unparseBlockStmt(FILE *out, block_stmt_t stmt, int level,
		      bool addSemiToEnd)
{
    unparseBlock(out, *(stmt.block), level, addSemiToEnd);
}

// Unparse the if-statment given by stmt to out
// with indentation level given by level (and each body indented one more),
// and add a semicolon at the end if addSemiToEnd is true.
void unparseIfStmt(FILE *out, if_stmt_t stmt, int level, bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "if ");
    unparseCondition(out, stmt.condition);
    fprintf(out, "\n");
    indent(out, level);
    fprintf(out, "then\n");
    unparseStmts(out, *(stmt.then_stmts), level+1);
    if (stmt.else_stmts != NULL) {
	indent(out, level);
	fprintf(out, "else\n");
	unparseStmts(out, *(stmt.else_stmts), level+1);
    }
    indent(out, level);
    fprintf(out, "end");
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the while-statment given by stmt to out
// with indentation level given by level (and the body indented one more),
// and add a semicolon at the end if addSemiToEnd is true.
void unparseWhileStmt(FILE *out, while_stmt_t stmt, int level,
		      bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "while ");
    unparseCondition(out, stmt.condition);
    fprintf(out, "\n");
    indent(out, level);
    fprintf(out, "do\n");
    unparseStmts(out, *(stmt.body), level+1);
    indent(out, level);
    fprintf(out, "end");
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the read statment given by stmt to out
// and add a semicolon at the end if addSemiToEnd is true.
void unparseReadStmt(FILE *out, read_stmt_t stmt, int level, bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "read %s", stmt.name);
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the write statment given by stmt to out
// and add a semicolon at the end if addSemiToEnd is true.
void unparsePrintStmt(FILE *out, print_stmt_t stmt, int level,
		      bool addSemiToEnd)
{
    indent(out, level);
    fprintf(out, "print ");
    unparseExpr(out, stmt.expr);
    newlineAndOptionalSemi(out, addSemiToEnd);
}

// Unparse the condition given by cond to out
void unparseCondition(FILE *out, condition_t cond)
{
    switch (cond.cond_kind) {
    case ck_db:
	unparseDbCond(out, cond.data.db_cond);
	break;
    case ck_rel:
	unparseRelOpCond(out, cond.data.rel_op_cond);
	break;
    default:
	bail_with_error("Unexpected condition_kind_e (%d) in unparseCondition!",
			cond.cond_kind);
	break;
    }
}

// Unparse the odd condition given by cond to out
void unparseDbCond(FILE *out, db_condition_t dbcond)
{
    fprintf(out, "divisible ");
    unparseExpr(out, dbcond.dividend);
    fprintf(out, " by ");
    unparseExpr(out, dbcond.divisor);
}

// Unparse the binary relation condition given by cond to out
void unparseRelOpCond(FILE *out, rel_op_condition_t cond)
{
    unparseExpr(out, cond.expr1);
    fprintf(out, " ");
    unparseToken(out, cond.rel_op);
    fprintf(out, " ");
    unparseExpr(out, cond.expr2);
}

// Unparse the given token, t, to out
void unparseToken(FILE *out, token_t t)
{
    fprintf(out, "%s", t.text);
}

// Unparse the expression given by the AST exp to out
// adding parentheses to indicate the nesting relationships
void unparseExpr(FILE *out, expr_t exp)
{
    switch (exp.expr_kind) {
    case expr_bin:
	unparseBinOpExpr(out, exp.data.binary);
	break;
    case expr_negated:
	unparseNegatedExpr(out, exp.data.negated);
	break;
    case expr_ident:
	unparseIdent(out, exp.data.ident);
	break;
    case expr_number:
	unparseNumber(out, exp.data.number);
	break;
    default:
	bail_with_error("Unexpected expr_kind_e (%d) in unparseExpr!",
			exp.expr_kind);
	break;
    }
}

// Unparse the expression given by the AST exp to out
// adding parentheses (whether needed or not)
void unparseBinOpExpr(FILE *out, binary_op_expr_t exp)
{
    fprintf(out, "(");
    unparseExpr(out, *(exp.expr1));
    fprintf(out, " ");
    unparseToken(out, exp.arith_op);
    fprintf(out, " ");
    unparseExpr(out, *(exp.expr2));
    fprintf(out, ")");
}

// Unparse the expression given by the AST exp to out
// adding parentheses (whether needed or not)
void unparseNegatedExpr(FILE *out, negated_expr_t exp)
{
    fprintf(out, "-(");
    unparseExpr(out, *(exp.expr));
    fprintf(out, ")");
}

// Unparse the given identifier reference (i.e., identifier use), id, to out
void unparseIdent(FILE *out, ident_t id)
{
    fprintf(out, "%s", id.name);
}

// Unparse the given number AST, num, to out in decimal format
void unparseNumber(FILE *out, number_t num)
{
    fprintf(out, "%d", num.value);
}
