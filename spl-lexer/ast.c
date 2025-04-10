/* $Id: ast.c,v 1.11 2024/10/06 01:07:29 leavens Exp $ */
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "utilities.h"
#include "ast.h"
#include "spl.tab.h"

// Return the file location from an AST
file_location *ast_file_loc(AST t) {
    return t.generic.file_loc;
}

// Return the filename from the AST t
const char *ast_filename(AST t) {
    return ast_file_loc(t)->filename;
}

// Return the line number from the AST t
unsigned int ast_line(AST t) {
    return ast_file_loc(t)->line;
}

// Return the type tag of the AST t
AST_type ast_type_tag(AST t) {
    return t.generic.type_tag;
}

// Return a pointer to a fresh copy of t
// that has been allocated on the heap
AST *ast_heap_copy(AST t) {
    AST *ret = (AST *)malloc(sizeof(AST));
    if (ret == NULL) {
	bail_with_error("Cannot allocate an AST heap copy!");
    }
    *ret = t;
    return ret;
}

// Return an AST for a block which contains the given ASTs.
block_t ast_block(token_t begin_tok, const_decls_t const_decls,
		  var_decls_t var_decls, proc_decls_t proc_decls,
		  stmts_t stmts)
{
    block_t ret;
    ret.file_loc = file_location_copy(begin_tok.file_loc);
    ret.type_tag = block_ast;
    ret.const_decls = const_decls;
    ret.var_decls = var_decls;
    ret.proc_decls = proc_decls;
    ret.stmts = stmts;
    return ret;
}

// Return an AST for an empty const decls
extern const_decls_t ast_const_decls_empty(empty_t empty)
{
    const_decls_t ret;
    ret.file_loc = empty.file_loc;
    ret.type_tag = const_decls_ast;
    ret.start = NULL;
    return ret;
}

// Return an AST for the const decls
const_decls_t ast_const_decls(const_decls_t const_decls,
			      const_decl_t const_decl)
{
    const_decls_t ret = const_decls;
    // make a copy of const_decl on the heap
    const_decl_t *p = (const_decl_t *) malloc(sizeof(const_decl_t));
    if (p == NULL) {
	bail_with_error("Cannot allocate space for %s!", "const_decl_t");
    }
    *p = const_decl;
    p->next = NULL;
    const_decl_t *last = ast_last_list_elem(ret.start);
    if (last == NULL) {
	ret.start = p;
    } else {
	last->next = p;
    }
    return ret;
}



// Return an AST for a const_decl
const_decl_t ast_const_decl(const_def_list_t const_def_list)
{
    const_decl_t ret;
    ret.file_loc = const_def_list.file_loc;
    ret.type_tag = const_decl_ast;
    ret.const_def_list = const_def_list;
    ret.next = NULL;
    return ret;
}

// Return an AST for const-def-list that is a singleton
extern const_def_list_t ast_const_def_list_singleton(const_def_t const_def)
{
    const_def_list_t ret;
    ret.file_loc = const_def.file_loc;
    ret.type_tag = const_def_list_ast;
    const_def_t *p = (const_def_t *) malloc(sizeof(const_def_t));
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "const_def_t"); 
    }		    
    *p = const_def;		
    p->next = NULL;    
    ret.start = p;							
    return ret;
}

// Return an AST for const_defs
extern const_def_list_t ast_const_def_list(const_def_list_t const_def_list,
				           const_def_t const_def)
{
    const_def_list_t ret = const_def_list;
    // make a copy of const_def on the heap
    const_def_t *p = (const_def_t *) malloc(sizeof(const_def_t));
    if (p == NULL) {
	bail_with_error("Cannot allocate space for %s!", "const_def_t");
    }
    *p = const_def;
    p->next = NULL;
    const_def_t *last = ast_last_list_elem(ret.start);
    if (last == NULL) {
	ret.start = p;
    } else {
	last->next = p;
    }
    return ret;
}

// Return an AST for a const-def
const_def_t ast_const_def(ident_t ident, number_t number)
{
    const_def_t ret;
    ret.file_loc = file_location_copy(ident.file_loc);
    assert((ret.file_loc)->filename != NULL);
    ret.type_tag = const_def_ast;
    ret.next = NULL;
    ret.ident = ident;
    ret.number = number;
    return ret;
}


// Return an AST for varDecls that are empty
var_decls_t ast_var_decls_empty(empty_t empty)
{
    var_decls_t ret;
    ret.file_loc = empty.file_loc;
    ret.type_tag = var_decls_ast;
    ret.var_decls = NULL;
    return ret;
}

// Return an AST varDecls that have some var_decls
var_decls_t ast_var_decls(var_decls_t var_decls, var_decl_t var_decl)
{
    var_decls_t ret = var_decls;
    // make a copy of var_decl on the heap
    var_decl_t *p = (var_decl_t *) malloc(sizeof(var_decl_t));
    if (p == NULL) {
	bail_with_error("Cannot allocate space for %s!", "var_decl_t");
    }
    *p = var_decl;
    p->next = NULL;
    var_decl_t *last = ast_last_list_elem(ret.var_decls);
    if (last == NULL) {
	ret.var_decls = p;
    } else {
	last->next = p;
    }
    return ret;
}

// Return an AST for a var_decl
var_decl_t ast_var_decl(ident_list_t ident_list)
{
    var_decl_t ret;
    ret.file_loc = ident_list.file_loc;
    ret.type_tag = var_decl_ast;
    ret.next = NULL;
    ret.ident_list = ident_list;
    return ret;
}

// Return an AST made for one ident
extern ident_list_t ast_ident_list_singleton(ident_t ident)
{
    ident_list_t ret;
    ret.file_loc = ident.file_loc;
    ret.type_tag = ident_list_ast;
    // make a copy of ident on the heap
    ident_t *p = (ident_t *) malloc(sizeof(ident_t));	
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "ident_t"); 
    }		    
    *p = ident;		
    p->next = NULL;    
    ret.start = p;						
    return ret;
}

// Return an AST made for idents
extern ident_list_t ast_ident_list(ident_list_t ident_list, ident_t ident)
{
    ident_list_t ret = ident_list;
    // make a copy of ident on the heap
    ident_t *p = (ident_t *) malloc(sizeof(ident_t));
    if (p == NULL) {
	bail_with_error("Cannot allocate space for %s!", "ident_t");
    }
    *p = ident;
    p->next = NULL;
    ident_t *last = ast_last_list_elem(ret.start);
    if (last == NULL) {
	ret.start = p;
    } else {
	last->next = p;
    }
    return ret;
}

// Return an AST for proc_decls
proc_decls_t ast_proc_decls_empty(empty_t empty)
{
    proc_decls_t ret;
    ret.file_loc = empty.file_loc;
    ret.type_tag = proc_decls_ast;
    ret.proc_decls = NULL;
    return ret;
}

// Return an AST for proc_decls
proc_decls_t ast_proc_decls(proc_decls_t proc_decls,
			    proc_decl_t proc_decl)
{
    proc_decls_t ret = proc_decls;
    // make a copy of proc_decl on the heap
    proc_decl_t *p = (proc_decl_t *) malloc(sizeof(proc_decl_t));	
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "proc_decl_t"); 
    }		    
    *p = proc_decl;		
    p->next = NULL;    
    proc_decl_t *last = ast_last_list_elem(ret.proc_decls);
    if (last == NULL) {
	ret.proc_decls = p;
    } else {
	last->next = p;
    }
    return ret;
}

// Return an AST for a proc_decl
proc_decl_t ast_proc_decl(ident_t ident, block_t block)
{
    proc_decl_t ret;
    ret.file_loc = file_location_copy(ident.file_loc);
    ret.type_tag = proc_decl_ast;
    ret.next = NULL;
    ret.name = ident.name;
    block_t *p = (block_t *) malloc(sizeof(block_t));
    if (p == NULL) {
	bail_with_error("Unable to allocate space for a %s!", "block_t");
    }
    *p = block;
    ret.block = p;
    return ret;
}

// Return an AST for a print statement
print_stmt_t ast_print_stmt(expr_t expr) {
    print_stmt_t ret;
    ret.file_loc = expr.file_loc;
    ret.type_tag = print_stmt_ast;
    ret.expr = expr;
    return ret;
}

// Return an AST for a read statement
read_stmt_t ast_read_stmt(ident_t ident) {
    read_stmt_t ret;
    ret.file_loc = file_location_copy(ident.file_loc);
    ret.type_tag = read_stmt_ast;
    ret.name = ident.name;
    return ret;
}

// Return an immediate data holding an address
while_stmt_t ast_while_stmt(condition_t condition, stmts_t body) {
    while_stmt_t ret;
    ret.file_loc = condition.file_loc;
    ret.type_tag = while_stmt_ast;
    ret.condition = condition;
    stmts_t *p = (stmts_t *) malloc(sizeof(stmts_t));
    if (p == NULL) {
	bail_with_error("Unable to allocate space for a %s!", "stmts_t"); 
    }
    *p = body;		
    ret.body = p;					
    return ret;
}

// Return an AST for an if-then-else statement
if_stmt_t ast_if_then_else_stmt(condition_t condition,
				stmts_t then_stmts, stmts_t else_stmts)
{
    if_stmt_t ret;
    ret.file_loc = condition.file_loc;
    ret.type_tag = if_stmt_ast;
    ret.condition = condition;
    // copy then_stmt to the heap
    stmts_t *p = (stmts_t *) malloc(sizeof(stmts_t));			
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "stmts_t"); 
    }									
    *p = then_stmts;	
    ret.then_stmts = p;						
    // copy else_stmts to the heap
    p = (stmts_t *) malloc(sizeof(stmts_t));	
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "stmts_t"); 
    }		    
    *p = else_stmts;		
    ret.else_stmts = p;						
    return ret;
}

// Return an AST for a (short) if-then statement
extern if_stmt_t ast_if_then_stmt(condition_t condition,
				  stmts_t then_stmts)
{
    if_stmt_t ret;
    ret.file_loc = condition.file_loc;
    ret.type_tag = if_stmt_ast;
    ret.condition = condition;
    // copy then_stmt to the heap
    stmts_t *p = (stmts_t *) malloc(sizeof(stmts_t));			
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "stmts_t"); 
    }									
    *p = then_stmts;	
    ret.then_stmts = p;						
    ret.else_stmts = NULL;						
    return ret;
}

// Return an AST for a begin statement
// containing the given list of statements
block_stmt_t ast_block_stmt(block_t block)
{
    block_stmt_t ret;
    ret.file_loc = block.file_loc;
    ret.type_tag = block_stmt_ast;
    // copy the block to the heap
    block_t *p = (block_t *) malloc(sizeof(block_t));			
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "block_t"); 
    }									
    *p = block;	
    ret.block = p;
    return ret;
}

// Return an AST for a call statment
 call_stmt_t ast_call_stmt(ident_t ident)
{
    call_stmt_t ret;
    ret.file_loc = file_location_copy(ident.file_loc);
    ret.type_tag = call_stmt_ast;
    ret.name = ident.name;
    return ret;
}

// Return an AST for an assignment statement
assign_stmt_t ast_assign_stmt(ident_t ident, expr_t expr)
{
    assign_stmt_t ret;
    ret.file_loc = file_location_copy(ident.file_loc);
    ret.type_tag = assign_stmt_ast;
    ret.name = ident.name;
    assert(ret.name != NULL);
    expr_t *p = (expr_t *) malloc(sizeof(expr_t));
    if (p == NULL) {
	bail_with_error("Unable to allocate space for a %s!", "expr_t");
    }
    *p = expr;
    ret.expr = p;
    assert(ret.expr != NULL);
    return ret;
}

// Return an AST for the list of statements 
stmts_t ast_stmts_empty(empty_t empty)
{
    stmts_t ret;
    ret.file_loc = file_location_copy(empty.file_loc);
    ret.type_tag = stmts_ast;
    ret.stmts_kind = empty_stmts_e;
    return ret;
}

// Return an AST for empty found in the given file location
empty_t ast_empty(file_location *file_loc)
{
    empty_t ret;
    ret.file_loc = file_loc;
    ret.type_tag = empty_ast;
    return ret;
}

// Return an AST for the list of statements 
stmts_t ast_stmts(stmt_list_t stmt_list)
{
    stmts_t ret;
    ret.file_loc = stmt_list.file_loc;
    ret.type_tag = stmts_ast;
    ret.stmts_kind = stmt_list_e;
    ret.stmt_list = stmt_list;
    return ret;
}


// Return an AST for the list of statements 
stmt_list_t ast_stmt_list_singleton(stmt_t stmt) {
    // debug_print("Entering ast_stmts_singleton\n");
    stmt_list_t ret;
    ret.file_loc = stmt.file_loc;
    ret.type_tag = stmt_list_ast;
    stmt.next = NULL;
    // copy stmt to the heap
    stmt_t *p = (stmt_t *) malloc(sizeof(stmt_t));	
    if (p == NULL) {							
	bail_with_error("Unable to allocate space for a %s!", "stmt_t"); 
    }		    
    *p = stmt;
    p->next = NULL;
    // there will be no statments after stmt in the list
    ret.start = p;					
    return ret;
}

// Return an AST for the list of statements 
extern stmt_list_t ast_stmt_list(stmt_list_t stmt_list, stmt_t stmt) {
    // debug_print("Entering ast_stmt_list...\n");
    stmt_list_t ret = stmt_list;
    // copy stmt to the heap
    stmt_t *s = (stmt_t *) malloc(sizeof(stmt_t));
    if (s == NULL) {
	bail_with_error("Cannot allocate space for %s!", "stmt_t");
    }
    *s = stmt;
    s->next = NULL;
    stmt_t *last = ast_last_list_elem(ret.start);
    assert(last != NULL); // because there are no empty lists of stmts
    last->next = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_assign(assign_stmt_t s)
{
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = assign_stmt;
    ret.data.assign_stmt = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_call(call_stmt_t s)
{
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = call_stmt;
    ret.data.call_stmt = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_block(block_stmt_t s)
{
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = block_stmt;
    ret.data.block_stmt = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_if(if_stmt_t s)
{
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = if_stmt;
    ret.data.if_stmt = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_while(while_stmt_t s)
{
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = while_stmt;
    ret.data.while_stmt = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_read(read_stmt_t s)
{
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = read_stmt;
    ret.data.read_stmt = s;
    return ret;
}

// Return an AST for the given statment
stmt_t ast_stmt_print(print_stmt_t s)
{
    // debug_print("Entering ast_stmt_print...\n");
    stmt_t ret;
    ret.file_loc = s.file_loc;
    ret.type_tag = stmt_ast;
    ret.next = NULL;
    ret.stmt_kind = print_stmt;
    ret.data.print_stmt = s;
    return ret;
}

// Return an AST for an odd condition
db_condition_t ast_db_condition(expr_t dividend, expr_t divisor)
{
    db_condition_t ret;
    ret.file_loc = dividend.file_loc;
    ret.type_tag = db_condition_ast;
    ret.dividend = dividend;
    ret.divisor = divisor;
    return ret;
}

// Return an AST for an initializer with the given value
rel_op_condition_t ast_rel_op_condition(expr_t expr1, token_t rel_op,
					expr_t expr2)
{
    rel_op_condition_t ret;
    ret.file_loc = expr1.file_loc;
    ret.type_tag = rel_op_condition_ast;
    ret.expr1 = expr1;
    ret.rel_op = rel_op;
    ret.expr2 = expr2;
    return ret;
}

// Return an AST for an odd condition
condition_t ast_condition_db(db_condition_t db_cond)
{
    condition_t ret;
    ret.file_loc = db_cond.file_loc;
    ret.type_tag = db_condition_ast;
    ret.cond_kind = ck_db;
    ret.data.db_cond = db_cond;
    return ret;
}

// Return an AST for a relational condition
condition_t ast_condition_rel_op(rel_op_condition_t rel_op_cond)
{
    condition_t ret;
    ret.file_loc = rel_op_cond.file_loc;
    ret.type_tag = condition_ast;
    ret.cond_kind = ck_rel;
    ret.data.rel_op_cond = rel_op_cond;
    return ret;
}

// Return an AST for an odd condition
binary_op_expr_t ast_binary_op_expr(expr_t expr1, token_t arith_op,
				    expr_t expr2)
{
    binary_op_expr_t ret;
    ret.file_loc = expr1.file_loc;
    ret.type_tag = binary_op_expr_ast;

    expr_t *p = (expr_t *) malloc(sizeof(expr_t));
    if (p == NULL) {
	bail_with_error("Unable to allocate space for a %s!", "expr_t");
    }
    *p = expr1;
    ret.expr1 = p;

    ret.arith_op = arith_op;
    
    p = (expr_t *) malloc(sizeof(expr_t));
    if (p == NULL) {
	bail_with_error("Unable to allocate space for a %s!", "expr_t");
    }
    *p = expr2;
    ret.expr2 = p;

    return ret;
}

// Return an expression AST for a binary operation expresion
expr_t ast_expr_binary_op(binary_op_expr_t e)
{
    expr_t ret;
    ret.file_loc = e.file_loc;
    ret.type_tag = expr_ast;
    ret.expr_kind = expr_bin;
    ret.data.binary = e;
    return ret;
}

// Return an expression AST for a signed expression
expr_t ast_expr_signed_expr(token_t sign, expr_t e)
{
    expr_t ret;
    ret.file_loc = file_location_copy(sign.file_loc);
    ret.type_tag = expr_ast;
    switch (sign.code) {
    case minussym:
	ret.expr_kind = expr_negated;
	negated_expr_t ne;
	ne.file_loc = ret.file_loc;
	ne.type_tag = negated_expr_ast;
	ne.expr = (expr_t *)ast_heap_copy((AST)e);
	ret.data.negated = ne;
        break;
    case plussym:
	// don't make any changes, use e as the result
	return e;
	break;
    default:
	bail_with_error("Unexpected sign token in ast_expr_signed_expr: %d",
			sign.code);
	break;
    }
    return ret;
}

// Return an expression AST for an signed number
expr_t ast_expr_pos_number(token_t sign, number_t number)
{
    expr_t ret;
    ret.file_loc = file_location_copy(sign.file_loc);
    ret.type_tag = expr_ast;
    ret.expr_kind = expr_number;
    ret.data.number = number;
    return ret;
}

// Return an AST for the given token
token_t ast_token(file_location *file_loc, const char *text, int code)
{
    token_t ret;
    ret.file_loc = file_loc;
    ret.type_tag = token_ast;
    ret.text = text;
    ret.code = code;
    return ret;
}

// Return an AST for a (signed) number with the given value
number_t ast_number(token_t sgn, word_type value)
{
    number_t ret;
    ret.file_loc = file_location_copy(sgn.file_loc);
    ret.type_tag = number_ast;
    ret.value = value;
    return ret;
}

// Return an AST for an identifier
ident_t ast_ident(file_location *file_loc, const char *name)
{
    ident_t ret;
    ret.file_loc = file_loc;
    ret.type_tag = ident_ast;
    ret.name = name;
    return ret;
}

// Return an AST for an expression that's a binary expression
expr_t ast_expr_binary_op_expr(binary_op_expr_t e)
{
    expr_t ret;
    ret.file_loc = e.file_loc;
    ret.type_tag = binary_op_expr_ast;
    ret.expr_kind = expr_bin;
    ret.data.binary = e;
    return ret;
}

// Return an AST for an expression that's an identifier
expr_t ast_expr_ident(ident_t e)
{
    expr_t ret;
    ret.file_loc = e.file_loc;
    ret.type_tag = expr_ast;
    ret.expr_kind = expr_ident;
    ret.data.ident = e;
    return ret;
}

// Return an AST for an expression that's a number
expr_t ast_expr_number(number_t e)
{
    expr_t ret;
    ret.file_loc = e.file_loc;
    ret.type_tag = expr_ast;
    ret.expr_kind = expr_number;
    ret.data.number = e;
    return ret;
}

// Requires: lst is a pointer to a non-circular 
//           linked list with next pointers
//           as in generic_t
// Return a pointer to the last element in lst.
// This only returns NULL if lst == NULL.
void *ast_last_list_elem(void *lst)
{
    // debug_print("Entering ast_last_list_elem\n");
    if (lst == NULL) {
	return lst;
    }
    // assert(lst != NULL);
    void *prev = NULL;
    while (lst != NULL) {
	prev = lst;
	lst = ((generic_t *)lst)->next;
    }
    // here lst == NULL;
    return prev;
}

// Requires: lst is a pointer to a non-circular 
//           linked list with next pointers
//           as in generic_t
// Return the number of elements in the linked list lst
int ast_list_length(void *lst)
{
    int ret = 0;
    generic_t *p = (generic_t *) lst;
    while (p != NULL) {
	p = p->next;
	ret++;
    }
    return ret;
}

// Requires: lst is a pointer to a non-circular 
//           linked list with next pointers
//           as in generic_t
// Is lst empty?
bool ast_list_is_empty(void *lst)
{
    return lst == NULL;
}
