/* $Id: scope_check.h,v 1.9 2024/11/10 12:54:14 leavens Exp $ */
#ifndef _SCOPE_CHECK_H
#define _SCOPE_CHECK_H
#include "ast.h"

// Requires: prog != NULL.
// The pointer passed to this function should point to the AST
// used by the compiler to generate code, so that the changes
// made (to the id_use fields) are communicated to the code generator.
// Build the symbol table for the given program AST
// and Check the given program AST for duplicate declarations
// or uses of identifiers that were not declared.
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_program(block_t *prog);

// build the symbol table and check the declarations in blk
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_block(block_t *blk);

// build the symbol table and check the declarations in cds
extern void scope_check_constDecls(const_decls_t cds);

// build the symbol table and check the const declaration cd
// and add its const-defs to the current scope's symbol table
// or produce an error if these names have already been declared
extern void scope_check_constDecl(const_decl_t cd);

// build the symbol table and check the const definitions cdfs
// and add the declared names to the current scope's symbol table
// or produce an error if these names have already been declared
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_const_def_list(const_def_list_t cdl);

// build the symbol table and check the const definition cdf
// and add the declared name to the current scope's symbol table
// or produce an error if its name has already been declared
extern void scope_check_constDef(const_def_t cdf);

// build the symbol table and check the declarations in vds
extern void scope_check_varDecls(var_decls_t vds);

// check the var declaration vd
// and add the declared names to the current scope's symbol table
// or produce an error if the names have already been declared
extern void scope_check_varDecl(var_decl_t vd);

// check the identifiers from a var declaration, as given in ids
// and add the declared names to the current scope's symbol table
// or produce an error if the names have already been declared
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_varIdentList(ident_list_t ident_list);

// build the symbol table and check the declarations in pds
extern void scope_check_procDecls(proc_decls_t *pds);

// check the procedure declaration pd
// and add it to the current scope's symbol table
// or produce an error if its name has already been declared
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_procDecl(proc_decl_t *pd);

// check all the statement in stmts to make sure that
// all idenfifiers referenced in them have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_stmts(stmts_t *stmts);

// check all the statement in stmt_list to make sure that
// all idenfifiers referenced in them have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_stmtList(stmt_list_t *stmt_list);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_stmt(stmt_t *stmt);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_assignStmt(assign_stmt_t *stmt);

// check the statement to make sure that
// the procedure being called has been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_callStmt(call_stmt_t *stmt);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_blockStmt(block_stmt_t *block);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_ifStmt(if_stmt_t *stmt);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_whileStmt(while_stmt_t *stmt);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_readStmt(read_stmt_t *stmt);

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_printStmt(print_stmt_t *stmt);

// check the condition to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_condition(condition_t *cond);

// check the condition to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_db_condition(db_condition_t *cond);

// check the condition to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_rel_op_condition(rel_op_condition_t *cond);

// check the expresion to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_expr(expr_t *exp);

// check that the given name has been declared,
// if not, then produce an error using the file_location (floc) given.
// Modifies the AST to have appropriate id_use pointers.
extern void scope_check_ident(ident_t *id);

// check the expression (exp) to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
extern void scope_check_binary_op_expr(binary_op_expr_t *exp);

// Check that the given name has been declared,
// if so, then return an id_use
// (containing the attributes) for that name,
// otherwise, produce an error
// using the file_location (floc) given.
extern id_use *scope_check_ident_declared(
         file_location floc,
         const char *name);

#endif
