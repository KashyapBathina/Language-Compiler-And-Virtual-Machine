#ifndef SCOPE_CHECK_H
#define SCOPE_CHECK_H

#include "ast.h"
#include "file_location.h"
#include "id_use.h"

// Function to check the scope of the program
void scope_check_program(block_t prog);

// Function declarations for checking various parts of the program
void scope_check_const_decls(const_decls_t const_decls);
void scope_check_proc_decls(proc_decls_t proc_decls);
void scope_check_var_decls(var_decls_t var_decls);
void scope_check_idents(ident_list_t ids, id_kind kind);
void scope_check_declare_ident(ident_t id, id_kind kind);
id_use *scope_check_ident_declared(file_location floc, const char *name);
stmt_t scope_check_stmt(stmt_t stmt);
assign_stmt_t scope_check_assign_stmt(assign_stmt_t stmt);
call_stmt_t scope_check_call_stmt(call_stmt_t stmt);
if_stmt_t scope_check_if_stmt(if_stmt_t stmt);
while_stmt_t scope_check_while_stmt(while_stmt_t stmt);
read_stmt_t scope_check_read_stmt(read_stmt_t stmt);
print_stmt_t scope_check_print_stmt(print_stmt_t stmt);
block_stmt_t scope_check_block_stmt(block_stmt_t stmt);
stmts_t scope_check_stmts(stmts_t stmts);
condition_t scope_check_condition(condition_t cond);
expr_t scope_check_expr(expr_t exp);
binary_op_expr_t scope_check_binary_op_expr(binary_op_expr_t exp);
ident_t scope_check_ident_expr(ident_t id);

#endif // SCOPE_CHECK_H
