#ifndef GEN_CODE_H
#define GEN_CODE_H

#include "ast.h"
#include "code_seq.h"
#include "bof.h"

// Initialize the code generator
void gen_code_initialize(void);

// Generate the entire program
void gen_code_program(BOFFILE bf, block_t prog);

// Generate code for a block
code_seq gen_code_block(block_t block);

// Generate code for constant declarations
code_seq gen_code_const_decls(const_decls_t cds);

// Generate code for a single constant declaration
code_seq gen_code_const_decl(const_decl_t cd);

// Generate code for a list of constant definitions
code_seq gen_code_const_def_list(const_def_list_t cdl);

// Generate code for a single constant definition
code_seq gen_code_const_def(const_def_t cd);

// Generate code for variable declarations
code_seq gen_code_var_decls(var_decls_t vds);

// Generate code for a single variable declaration
code_seq gen_code_var_decl(var_decl_t vd);

// Generate code for identifiers in idents
code_seq gen_code_idents(ident_list_t idents);

// Generate code for statements
code_seq gen_code_stmts(stmts_t stmts);

// Generate code for a list of statements
code_seq gen_code_stmt_list(stmt_list_t stmt_list);

// Generate code for a single statement
code_seq gen_code_stmt(stmt_t stmt);

// Generate code for an assignment statement
code_seq gen_code_assign_stmt(assign_stmt_t stmt);

// Generate code for a call statement
code_seq gen_code_call_stmt(call_stmt_t stmt);

// Generate code for a block statement
code_seq gen_code_block_stmt(block_stmt_t stmt);

// Generate code for an if statement
code_seq gen_code_if_stmt(if_stmt_t stmt);

// Generate code for a while statement
code_seq gen_code_while_stmt(while_stmt_t stmt);

// Generate code for a read statement
code_seq gen_code_read_stmt(read_stmt_t stmt);

// Generate code for a print statement
code_seq gen_code_print_stmt(print_stmt_t stmt);

// Generate code for conditions
code_seq gen_code_condition(condition_t cond);

// Generate code for database conditions
code_seq gen_code_db_condition(db_condition_t cond);

// Generate code for relational operator conditions
code_seq gen_code_rel_op_condition(rel_op_condition_t cond);

// Generate code for expressions
code_seq gen_code_expr(expr_t expr);

// Generate code for binary operation expressions
code_seq gen_code_binary_op_expr(binary_op_expr_t expr);

// Generate code for negated expressions
code_seq gen_code_negated_expr(negated_expr_t expr);

// Generate code for identifiers
code_seq gen_code_ident(ident_t id);

// Generate code for number literals
code_seq gen_code_number(number_t number);

// Generate code for operators
code_seq gen_code_op(token_t op);

// Generate code for arithmetic operators
code_seq gen_code_arith_op(token_t op);

// Generate code for relational operators
code_seq gen_code_rel_op(token_t op);

#endif // GEN_CODE_H
