/* $Id: ast.h,v 1.12 2024/10/06 01:07:29 leavens Exp $ */
#ifndef _AST_H
#define _AST_H
#include <stdbool.h>
#include "machine_types.h"
#include "file_location.h"

// types of ASTs (type tags)
typedef enum {
    block_ast, const_decls_ast, const_decl_ast,
    const_def_list_ast, const_def_ast, 
    var_decls_ast, var_decl_ast, ident_list_ast,
    proc_decls_ast, proc_decl_ast,
    stmts_ast, empty_ast, stmt_list_ast, stmt_ast,
    assign_stmt_ast, call_stmt_ast, if_stmt_ast, while_stmt_ast,
    read_stmt_ast, print_stmt_ast, block_stmt_ast,
    condition_ast, db_condition_ast, rel_op_condition_ast,
    expr_ast, binary_op_expr_ast, negated_expr_ast, ident_ast, number_ast,
    token_ast
} AST_type;

// The following types for structs named N_t
// are returned by the parser.
// The struct N_t is the type of information kept in the AST
// that is related to the nonterminal N in the abstract syntax.

// The generic struct type (generic_t) has the fields that
// should be in all alternatives for ASTs.
typedef struct {
    file_location *file_loc;
    AST_type type_tag; // says what field of the union is active
    void *next; // for lists
} generic_t;

// empty ::=
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
} empty_t;

// identifiers
typedef struct ident_s {
    file_location *file_loc;
    AST_type type_tag;
    struct ident_s *next; // for lists this is a part of
    const char *name;
} ident_t;

// (possibly signed) numbers
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const char *text;
    word_type value;
} number_t;

// tokens as ASTs
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const char *text;
    int code;
} token_t;

// kinds of expressions
typedef enum { expr_bin, expr_negated, expr_ident, expr_number } expr_kind_e;

// forward declaration for the expr type
struct expr_s;

// expr ::= expr arithOp expr
// arithOp ::= + | - | * | /
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    struct expr_s *expr1;
    token_t arith_op;
    struct expr_s *expr2;
} binary_op_expr_t;

// expr ::= - expr
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    struct expr_s *expr;
} negated_expr_t;
    
// expr ::= expr arithOp expr | ident | number
typedef struct expr_s {
    file_location *file_loc;
    AST_type type_tag;
    expr_kind_e expr_kind;
    union {
	binary_op_expr_t binary;
	negated_expr_t negated;
	ident_t ident;
	number_t number;
    } data;
} expr_t;

// kinds of conditions
typedef enum { ck_db, ck_rel } condition_kind_e;

typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    expr_t dividend;
    expr_t divisor;
} db_condition_t;

typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    expr_t expr1;
    token_t rel_op;
    expr_t expr2;
} rel_op_condition_t;

// condition ::= divisible expr expr | expr relOp expr
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    condition_kind_e cond_kind;
    union cond_u {
	db_condition_t db_cond;
	rel_op_condition_t rel_op_cond;
    } data;
} condition_t;

// kinds of statements
typedef enum { assign_stmt, call_stmt, if_stmt, while_stmt,
	       read_stmt, print_stmt, block_stmt } stmt_kind_e;

// forward declaration of statement type
struct stmt_s;

// stmt-list ::= stmt | stmt-list stmt
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    struct stmt_s *start;
} stmt_list_t;

typedef enum { empty_stmts_e, stmt_list_e } stmts_kind_e;

// stmts ::= { stmts }
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    stmts_kind_e stmts_kind;
    stmt_list_t stmt_list; // when stmts_kind != empty_stmts_e
} stmts_t;

// stmt ::= ident := expr
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const char *name;
    struct expr_s *expr;
} assign_stmt_t;

// stmt ::= call ident
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const char *name;
} call_stmt_t;

// forward declaration for block type
struct block_s;

// block-stmt ::= block
typedef struct block_stmt_s {
    file_location *file_loc;
    AST_type type_tag;
    struct block_s *block;
} block_stmt_t;

// if-stmt ::= if condition stmts stmts | if condition stmts
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    condition_t condition;
    stmts_t *then_stmts;
    stmts_t *else_stmts;
} if_stmt_t;

// stmt ::= while condition stmt
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    condition_t condition;
    stmts_t *body;
} while_stmt_t;

// stmt ::= read ident
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const char *name;
} read_stmt_t;

// stmt ::= print expr
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    expr_t expr;
} print_stmt_t;

// stmt ::= assign-stmt | call-stmt | if-stmt
//        | while-stmt | read-stmt | print-stmt | block-stmt
typedef struct stmt_s {
    file_location *file_loc;
    AST_type type_tag;
    struct stmt_s *next; // for lists this is a part of
    stmt_kind_e stmt_kind;
    union {
	assign_stmt_t assign_stmt;
	call_stmt_t call_stmt;
	if_stmt_t if_stmt;
	while_stmt_t while_stmt;
	read_stmt_t read_stmt;
	print_stmt_t print_stmt;
	block_stmt_t block_stmt;
    } data;
} stmt_t;

// procDecl ::= proc ident block
typedef struct proc_decl_s {
    file_location *file_loc;
    AST_type type_tag;
    struct proc_decl_s *next; // for lists
    const char *name;
    struct block_s *block;
} proc_decl_t;

// proc-decls ::= { proc-decl }
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    proc_decl_t *proc_decls;
} proc_decls_t;

// ident-list ::= ident | ident-list ident
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    ident_t *start;
} ident_list_t;

// var-decl ::= var ident-list
typedef struct var_decl_s {
    file_location *file_loc;
    AST_type type_tag;
    struct var_decl_s *next; // for lists this is a part of
    ident_list_t ident_list;
} var_decl_t;

// var-decls ::= { var-decl }
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    var_decl_t *var_decls;
} var_decls_t;

// const-def ::= ident number
typedef struct const_def_s {
    file_location *file_loc;
    AST_type type_tag;
    struct const_def_s *next; // for lists this is a part of
    ident_t ident;
    number_t number;
} const_def_t;

// const-def-list ::= { const-def }
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const_def_t *start;
} const_def_list_t;

// const-decl ::= const const-def-list
typedef struct const_decl_s {
    file_location *file_loc;
    AST_type type_tag;
    struct const_decl_s *next; // for lists this is a part of
    const_def_list_t const_def_list;
} const_decl_t;

// const-decls ::= { const-decl }
typedef struct {
    file_location *file_loc;
    AST_type type_tag;
    const_decl_t *start;
} const_decls_t;

// block ::= begin const-decls var-decls proc-decls stmts
typedef struct block_s {
    file_location *file_loc;
    AST_type type_tag;
    const_decls_t const_decls;
    var_decls_t var_decls;
    proc_decls_t proc_decls;
    stmts_t stmts;
} block_t;

// program ::= block

// The AST definition used by bison
typedef union AST_u {
    generic_t generic;
    block_t block;
    const_decls_t const_decls;
    const_decl_t const_decl;
    const_def_list_t const_def_list;
    const_def_t const_def;
    var_decls_t var_decls;
    var_decl_t var_decl;
    ident_list_t ident_list;
    proc_decls_t proc_decls;
    proc_decl_t proc_decl;
    stmts_t stmts;
    stmt_list_t stmt_list;
    stmt_t stmt;
    assign_stmt_t assign_stmt;
    call_stmt_t call_stmt;
    if_stmt_t if_stmt;
    while_stmt_t while_stmt;
    read_stmt_t read_stmt;
    print_stmt_t print_stmt;
    block_stmt_t block_stmt;
    condition_t condition;
    rel_op_condition_t rel_op_condition;
    db_condition_t db_condition;
    expr_t expr;
    binary_op_expr_t binary_op_expr;
    token_t token;
    number_t number;
    ident_t ident;
    empty_t empty;
} AST;

// Return the file location from an AST
extern file_location *ast_file_loc(AST t);

// Return the filename from the AST t
extern const char *ast_filename(AST t);

// Return the line number from the AST t
extern unsigned int ast_line(AST t);

// Return the type tag of the AST t
extern AST_type ast_type_tag(AST t);

// Return a pointer to a fresh copy of t
// that has been allocated on the heap
extern AST *ast_heap_copy(AST t);

// Return an AST for a block which contains the given ASTs.
extern block_t ast_block(token_t begin_tok, const_decls_t const_decls, var_decls_t var_decls, proc_decls_t proc_decls, stmts_t stmts);

// Return an AST for an empty const decls
extern const_decls_t ast_const_decls_empty(empty_t empty);

// Return an AST for the const decls
extern const_decls_t ast_const_decls(const_decls_t const_decls,
				     const_decl_t const_decl);

// Return an AST for a const_decl
extern const_decl_t ast_const_decl(const_def_list_t const_def_list);

// Return an AST for const_def_list
extern const_def_list_t ast_const_def_list_singleton(const_def_t const_def);

// Return an AST for adding to a const_def_list
extern const_def_list_t ast_const_def_list(const_def_list_t const_def_list,
					   const_def_t const_def);

// Return an AST for a const-def
extern const_def_t ast_const_def(ident_t ident, number_t number);

// Return an AST for varDecls that are empty
extern var_decls_t ast_var_decls_empty(empty_t empty);

// Return an AST varDecls that have some var_decls
extern var_decls_t ast_var_decls(var_decls_t var_decls, var_decl_t var_decl);

// Return an AST for a var_decl
extern var_decl_t ast_var_decl(ident_list_t ident_list);

// Return an AST made for one ident
extern ident_list_t ast_ident_list_singleton(ident_t ident);

// Return an AST made for ident lists
extern ident_list_t ast_ident_list(ident_list_t ident_list, ident_t ident);

// Return an AST for proc_decls
extern proc_decls_t ast_proc_decls_empty(empty_t empty);

// Return an AST for proc_decls
extern proc_decls_t ast_proc_decls(proc_decls_t proc_decls,
				   proc_decl_t proc_decl);

// Return an AST for a proc_decl
extern proc_decl_t ast_proc_decl(ident_t ident, block_t block);


// Return an AST for the list of statements 
extern stmts_t ast_stmts_empty(empty_t empty);

// Return an AST for empty found in the given file location
extern empty_t ast_empty(file_location *file_loc);

// Return an AST for the list of statements 
extern stmts_t ast_stmts(stmt_list_t stmt_list);

// Return an AST for a list of statements that has stmt as a member
extern stmt_list_t ast_stmt_list_singleton(stmt_t stmt);

// Return an AST for the list of statements 
extern stmt_list_t ast_stmt_list(stmt_list_t stmt_list, stmt_t stmt);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_assign(assign_stmt_t s);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_call(call_stmt_t s);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_block(block_stmt_t s);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_if(if_stmt_t s);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_while(while_stmt_t s);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_read(read_stmt_t s);

// Return an AST for the given statement as a more general stmt AST
extern stmt_t ast_stmt_print(print_stmt_t s);

// Return an AST for an assignment statement
extern assign_stmt_t ast_assign_stmt(ident_t ident, expr_t expr);

// Return an AST for a call statement
extern call_stmt_t ast_call_stmt(ident_t ident);

// Return an AST for an if-then-else statement
extern if_stmt_t ast_if_then_else_stmt(condition_t condition,
				       stmts_t then_stmts, stmts_t else_stmts);

// Return an AST for a (short) if-then statement
extern if_stmt_t ast_if_then_stmt(condition_t condition,
				  stmts_t then_stmts);

// Return an AST for a while statement
extern while_stmt_t ast_while_stmt(condition_t condition, stmts_t body);

// Return an AST for a read statement
extern read_stmt_t ast_read_stmt(ident_t ident); 

// Return an AST for a print statement
extern print_stmt_t ast_print_stmt(expr_t expr); 

// Return an AST for a block statement
extern block_stmt_t ast_block_stmt(block_t block);


// Return an AST for an odd condition
extern db_condition_t ast_db_condition(expr_t dividend, expr_t divisor);

// Return an AST for an initializer with the given value
extern rel_op_condition_t ast_rel_op_condition(expr_t expr1, token_t rel_op,
					       expr_t expr2);

// Return an AST for an odd condition
extern condition_t ast_condition_db(db_condition_t db_cond);

// Return an AST for a relational condition
extern condition_t ast_condition_rel_op(rel_op_condition_t rel_op_cond);


// Return an expression AST for a binary operation expresion
extern expr_t ast_expr_binary_op(binary_op_expr_t e1);

// Return an expression AST for an identifier
extern expr_t ast_expr_ident(ident_t e);

// Return an AST for an expression that's a number
extern expr_t ast_expr_number(number_t e);

// Return an AST for a binary op expression
extern binary_op_expr_t ast_binary_op_expr(expr_t expr1, token_t arith_op,
					   expr_t expr2);

// Return an expression AST for a signed expression
extern expr_t ast_expr_signed_expr(token_t sign, expr_t expr);

// The following are made by the lexer...

// Return an AST for the given token
extern token_t ast_token(file_location *file_loc, const char *text, int code);

// Return an AST for an identifier
// found in the file named fn, on line ln, with the given name.
extern ident_t ast_ident(file_location *file_loc, const char *name);

// Some operations on AST lists

// Requires: lst is a pointer to a non-circular 
//           linked list with next pointers
//           as in generic_t
// Return a pointer to the last element in lst.
// This only returns NULL if lst == NULL.
extern void *ast_last_list_elem(void *lst);

// Requires: lst is a pointer to a non-circular 
//           linked list with next pointers
//           as in generic_t
// Return the number of elements in the linked list lst
extern int ast_list_length(void *lst);

// Requires: lst is a pointer to a non-circular 
//           linked list with next pointers
//           as in generic_t
// Is lst empty?
extern bool ast_list_is_empty(void *lst);

#endif
