/* $Id: unparser.h,v 1.6 2024/10/23 14:55:24 leavens Exp $ */
#ifndef _UNPARSER_H
#define _UNPARSER_H
#include <stdio.h>
#include "ast.h"

// Unparse the given program AST and then print a period and an newline
extern void unparseProgram(FILE *out, block_t prog);

// Unparse the given block, indented by the given level, to out
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseBlock(FILE *out, block_t blk, int indentLevel,
			 bool addSemiToEnd);

// Unparse the list of const-decls given by the AST cds to out
// with the given nesting level
// (note that if cds is empty, then nothing is printed)
extern void unparseConstDecls(FILE *out, const_decls_t cds, int level);

// Unparse the const-decl given by the AST cd to out
// with the given nesting level
extern void unparseConstDecl(FILE *out, const_decl_t cd, int level);

// Unparse the list of const-defs given by the AST cdl to out
// with the given nesting level
extern void unparseConstDefList(FILE *out, const_def_list_t cdl, int level);

// Unparse the const-def given by the AST cdf to out
// with the given nesting level
extern void unparseConstDef(FILE *out, const_def_t cdf, int level);

// Unparse the list of var-decls given by the AST vds to out
// with the given nesting level
// (note that if vds.var_decls == NULL, then nothing is printed)
extern void unparseVarDecls(FILE *out, var_decls_t vds, int level);

// Unparse the var-decl given by the AST vd to out
// with the given nesting level
extern void unparseVarDecl(FILE *out, var_decl_t vd, int level);

// Unparse the identifiers in idents to out, with a space before each,
// and a comma as a separator
extern void unparseIdentList(FILE *out, ident_list_t ident_list);

// Unparse the list of proc-decls given by the AST pds to out
// with the given nesting level
// (note that if pds.proc_decls is NULL, then nothing is printed)
extern void unparseProcDecls(FILE *out, proc_decls_t pds, int level);

// Unparse the given proc-decl given by the AST pd to out
// with the given nesting level
extern void unparseProcDecl(FILE *out, proc_decl_t pd, int level);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseStmt(FILE *out, stmt_t stmt, int indentLevel,
			bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseAssignStmt(FILE *out, assign_stmt_t stmt, int level, bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseCallStmt(FILE *out, call_stmt_t stmt, int level, bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseBlockStmt(FILE *out, block_stmt_t stmt, int level, bool addSemiToEnd);

// Unparse the statements given by the AST stmts to out,
// indented for the given level.
// (The statements always occur before an end, so a semicolon is never added.)
extern void unparseStmts(FILE *out, stmts_t stmts, int level);

// Unparse the stmts given by stmt to out
// with indentation level given by level,
// and add a semicolon at the end if addSemiToEnd is true.
void unparseStmtList(FILE *out, stmt_list_t stmt_list, int level,
		     bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseIfStmt(FILE *out, if_stmt_t stmt, int level,
			  bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseWhileStmt(FILE *out, while_stmt_t stmt, int level,
			     bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparseReadStmt(FILE *out, read_stmt_t stmt, int level,
			    bool addSemiToEnd);

// Unparse the statement given by the AST stmt to out,
// indented for the given level,
// adding a semicolon to the end if addSemiToEnd is true.
extern void unparsePrintStmt(FILE *out, print_stmt_t stmt, int level, bool addSemiToEnd);

// Unparse the condition given by cond to out
extern void unparseCondition(FILE *out, condition_t cond);

extern void unparseDbCond(FILE *out, db_condition_t cond);

extern void unparseRelOpCond(FILE *out, rel_op_condition_t cond);

// Unparse the given token, t, to out
extern void unparseToken(FILE *out, token_t t);

// Unparse the expression given by the AST exp to out
// adding parentheses to indicate the nesting relationships
extern void unparseExpr(FILE *out, expr_t exp);

extern void unparseBinOpExpr(FILE *out, binary_op_expr_t exp);

// Unparse the given bin_arith_opo to out
extern void unparseArithOp(FILE *out, token_t arith_op);

// Unparse the expression given by the AST exp to out
// adding parentheses (whether needed or not)
extern void unparseNegatedExpr(FILE *out, negated_expr_t exp);

// Unparse the given identifer reference (use) to out
extern void unparseIdent(FILE *out, ident_t id);

// Unparse the given number to out in decimal format
extern void unparseNumber(FILE *out, number_t num);

#endif
