/* $Id: scope_check.c,v 1.22 2024/11/16 20:34:50 leavens Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scope_check.h"
#include "id_attrs.h"
#include "file_location.h"
#include "ast.h"
#include "utilities.h"
#include "symtab.h"
#include "scope_check.h"

// Requires: prog != NULL.
// The pointer passed to this function should point to the AST
// used by the compiler to generate code, so that the changes
// made (to the id_use fields) are communicated to the code generator.
// Build the symbol table for the given program AST
// and Check the given program AST for duplicate declarations
// or uses of identifiers that were not declared.
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_program(block_t *prog)
{
    scope_check_block(prog);
}

// build the symbol table and check the declarations in blk
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_block(block_t *blk)
{
    symtab_enter_scope();
    scope_check_constDecls(blk->const_decls);
    scope_check_varDecls(blk->var_decls);
    scope_check_procDecls(&(blk->proc_decls));
    scope_check_stmts(&(blk->stmts));
    symtab_leave_scope();
}

// build the symbol table and check the declarations in cds
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_constDecls(const_decls_t cds)
{
    const_decl_t *dcl = cds.start;
    while (dcl != NULL) {
	scope_check_constDecl(*(dcl));
	dcl = dcl->next;
    }
}

// build the symbol table and check the const declaration cd
// and add its const-defs to the current scope's symbol table
// or produce an error if these names have already been declared
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_constDecl(const_decl_t cd)
{
    scope_check_const_def_list(cd.const_def_list);
}

// build the symbol table and check the const definitions cdfs
// and add the declared names to the current scope's symbol table
// or produce an error if these names have already been declared
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_const_def_list(const_def_list_t cdl)
{
    const_def_t *cdf = cdl.start;
    while (cdf != NULL) {
	scope_check_constDef(*(cdf));
	cdf = cdf->next;
    }
}

// Put the given name, which is to be declared with kind k,
// and has its declaration at the given file location (floc),
// into the current scope's symbol table at the offset scope_size().
// Modifies the given AST to have appropriate id_use pointers.
static void add_ident_to_scope(const char *name, id_kind k, file_location floc)
{
    id_use *idu = symtab_lookup(name);
    if (idu != NULL && idu->levelsOutward == 0) {
	bail_with_prog_error(floc,
			     "%s \"%s\" is already declared as a %s",
			     id_attrs_id_kind_string(k),
			     name,
			     id_attrs_id_kind_string(
						id_use_get_attrs(idu)->kind));
    } else {
	symtab_insert(name,
		      id_attrs_create(floc, k, symtab_scope_loc_count()));
    }
}

// build the symbol table and check the const definition cdf
// and add the declared name to the current scope's symbol table
// or produce an error if this name has already been declared
void scope_check_constDef(const_def_t cdf)
{
    add_ident_to_scope(cdf.ident.name, constant_idk, *(cdf.file_loc));
}

// build the symbol table and check the declarations in vds
void scope_check_varDecls(var_decls_t vds)
{
    var_decl_t *vdp = vds.var_decls;
    while (vdp != NULL) {
	scope_check_varDecl(*vdp);
	vdp = vdp->next;
    }
}

// check the var declaration vd
// and add the declared names to the current scope's symbol table
// or produce an error if the names have already been declared
void scope_check_varDecl(var_decl_t vd)
{
    scope_check_varIdentList(vd.ident_list);
}

// check the identifiers from a var declaration, as given in ids
// and add the declared names to the current scope's symbol table
// or produce an error if the names have already been declared
void scope_check_varIdentList(ident_list_t idl)
{
    ident_t *idp = idl.start;
    while (idp != NULL) {
	add_ident_to_scope(idp->name, variable_idk, *(idp->file_loc));
	idp = idp->next;
    }
}

// build the symbol table and check the declarations in pds
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_procDecls(proc_decls_t *pds)
{
    proc_decl_t *pdp = pds->proc_decls;
    while (pdp != NULL) {
	scope_check_procDecl(pdp);
	pdp = pdp->next;
    }
}

// check the procedure declaration pd
// and add it to the current scope's symbol table
// or produce an error if its name has already been declared
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_procDecl(proc_decl_t *pd)
{
    // add name to scope first, so that the procedure can be recursive
    add_ident_to_scope(pd->name, procedure_idk, *(pd->file_loc));
    scope_check_block(pd->block);
}

// check all the statement in stmts to make sure that
// all idenfifiers referenced in them have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_stmts(stmts_t *stmts)
{
    if (stmts->stmts_kind != empty_stmts_e) {
	scope_check_stmtList(&(stmts->stmt_list));
    }
}

// check all the statement in stmt_list to make sure that
// all idenfifiers referenced in them have been declared
// (if not, then produce an error)
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_stmtList(stmt_list_t *stmt_list)
{
    stmt_t *s = stmt_list->start;
    while (s != NULL) {
	scope_check_stmt(s);
	s = s->next;
    }
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_stmt(stmt_t *stmt)
{
    switch (stmt->stmt_kind) {
    case assign_stmt:
	scope_check_assignStmt(&(stmt->data.assign_stmt));
	break;
    case call_stmt:
	scope_check_callStmt(&(stmt->data.call_stmt));
	break;
    case if_stmt:
	scope_check_ifStmt(&(stmt->data.if_stmt));
	break;
    case while_stmt:
	scope_check_whileStmt(&(stmt->data.while_stmt));
	break;
    case read_stmt:
	scope_check_readStmt(&(stmt->data.read_stmt));
	break;
    case print_stmt:
	scope_check_printStmt(&(stmt->data.print_stmt));
        print_stmt_t ps = stmt->data.print_stmt;
	if (ps.expr.expr_kind == expr_ident) {
	    assert(ps.expr.data.ident.idu != NULL);
	}
	break;
    case block_stmt:
	scope_check_blockStmt(&(stmt->data.block_stmt));
	break;
    default:
	bail_with_error("Unknown stmt_kind (%d) in scope_check_stmt!",
			stmt->stmt_kind);
	break;
    }
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_assignStmt(assign_stmt_t *stmt)
{
    stmt->idu = scope_check_ident_declared(*(stmt->file_loc), stmt->name);
    id_attrs attrs = *id_use_get_attrs(stmt->idu);
    if (attrs.kind != variable_idk) {
	bail_with_prog_error(attrs.file_loc,
			     "Must be a variable on the left-hand side of an assignment statement, not the %s \"%s\"",
			     id_attrs_id_kind_string(attrs.kind),
			     stmt->name);
    }
    scope_check_expr(stmt->expr);
}

// check the statement to make sure that
// the procedure being called has been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_callStmt(call_stmt_t *stmt)
{
    stmt->idu = scope_check_ident_declared(*(stmt->file_loc), stmt->name);
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_blockStmt(block_stmt_t *stmt)
{
    scope_check_block(stmt->block);
}


// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_ifStmt(if_stmt_t *stmt)
{
    scope_check_condition(&(stmt->condition));
    scope_check_stmts(stmt->then_stmts);
    if (stmt->else_stmts != NULL) {
	scope_check_stmts(stmt->else_stmts);
    }
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_whileStmt(while_stmt_t *stmt)
{
    scope_check_condition(&(stmt->condition));
    scope_check_stmts(stmt->body);
}

// Check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_readStmt(read_stmt_t *stmt)
{
    stmt->idu = scope_check_ident_declared(*(stmt->file_loc), stmt->name);
    id_attrs attrs = *id_use_get_attrs(stmt->idu);
    if (attrs.kind != variable_idk) {
	bail_with_prog_error(attrs.file_loc,
			     "The name (%s) in a read statement must be a variable, not a %s",
			     stmt->name,
			     id_attrs_id_kind_string(attrs.kind));
    }
}

// check the statement to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_printStmt(print_stmt_t *stmt)
{
    scope_check_expr(&(stmt->expr));
    if (stmt->expr.expr_kind == expr_ident) {
	assert(stmt->expr.data.ident.idu != NULL);
    }
}

// check the condition to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_condition(condition_t *cond)
{
    switch (cond->cond_kind){
    case ck_db:
	scope_check_db_condition(&(cond->data.db_cond));
	break;
    case ck_rel:
	scope_check_rel_op_condition(&(cond->data.rel_op_cond));
	break;
    default:
	bail_with_error("Unexpected type_tag (%d) in scope_check_cond!",
			cond->cond_kind);
	break;
    }
}

// check the condition to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_db_condition(db_condition_t *cond)
{
    scope_check_expr(&(cond->dividend));
    scope_check_expr(&(cond->divisor));
}

// check the condition to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_rel_op_condition(rel_op_condition_t *cond)
{
    scope_check_expr(&(cond->expr1));
    scope_check_expr(&(cond->expr2));
}

// check the expresion to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error).
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_expr(expr_t *exp)
{
    switch (exp->expr_kind) {
    case expr_ident:
	scope_check_ident(&(exp->data.ident));
	assert(exp->data.ident.idu != NULL);
	break;
    case expr_negated:
	scope_check_expr(exp->data.negated.expr);
	break;
    case expr_bin:
	scope_check_binary_op_expr(&(exp->data.binary));
	break;
    case expr_number:
	// no identifiers are possible in this case, so just return
	break;
    default:
	bail_with_error("Unexpected expr_kind_e (%d) in scope_check_expr!",
			exp->expr_kind);
	break;
    }
}

// check that the given name has been declared,
// if not, then produce an error using the file_location (floc) given.
// Modifies the given AST to have appropriate id_use pointers.
void scope_check_ident(ident_t *id)
{
    file_location floc = *(id->file_loc);
    const char *name = id->name;
    id_use *idu = scope_check_ident_declared(floc, name);
    if (idu == NULL) {
	bail_with_prog_error(floc,
			     "identifier \"%s\" has not been declared!",
			     name);
    }
    id->idu = idu;
}

// check the expression (exp) to make sure that
// all idenfifiers referenced in it have been declared
// (if not, then produce an error)
void scope_check_binary_op_expr(binary_op_expr_t *exp)
{
    scope_check_expr(exp->expr1);
    scope_check_expr(exp->expr2);
}

// Check that the given name has been declared,
// if so, then return an id_use
// (containing the attributes) for that name,
// otherwise, produce an error
// using the file_location (floc) given.
id_use *scope_check_ident_declared(
         file_location floc,
         const char *name)
{
    id_use *ret = symtab_lookup(name);
    if (ret == NULL) {
	bail_with_prog_error(floc,
				"identifier \"%s\" is not declared!",
				name);
    }
    id_attrs *ret_attrs = id_use_get_attrs(ret);
    assert(ret_attrs != NULL);
    return ret;
}
