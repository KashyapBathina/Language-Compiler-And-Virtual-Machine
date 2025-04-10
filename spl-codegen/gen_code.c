#include "gen_code.h"
#include "ast.h" // For block_t, stmt_t, expr_t, etc.
#include "code_seq.h" // For code_seq and related operations
#include "code_utils.h"
#include "bof.h" // For BOFHeader and related functions
#include "literal_table.h" // For managing literals
#include "instruction.h" // For instruction-related functions
#include "regname.h" // For register names
#include "utilities.h" // For utility functions
#include <string.h> // For memcpy
#include "spl.tab.h"
#include "code.h"


#define STACK_SPACE 4096

// Initialize the code generator
void gen_code_initialize() {
    literal_table_initialize();
}

// Requires: bf if open for writing in binary
// and prior to this scope checking and type checking have been done.
// Write all the instructions in cs to bf in order
static void gen_code_output_seq(BOFFILE bf, code_seq cs) {
    while (!code_seq_is_empty(cs)) {
      	bin_instr_t inst = code_seq_first(cs)->instr;
      	instruction_write_bin_instr(bf, inst);
      	cs = code_seq_rest(cs);
    }
}

// Generate the BOF program header
BOFHeader gen_code_program_header(code_seq main_cs) {
    BOFHeader ret;
    bof_write_magic_to_header(&ret);
    ret.text_start_address = 0;
    ret.text_length = code_seq_size(main_cs);
    ret.data_start_address = MAX(ret.text_length, 1024);
    ret.data_length = literal_table_size();
    ret.stack_bottom_addr = ret.data_start_address + ret.data_start_address + ret.data_length + STACK_SPACE;
    return ret;
}

// Output literals
void gen_code_output_literals(BOFFILE bf) {
    literal_table_start_iteration();
    while (literal_table_iteration_has_next()) {
        word_type literal = literal_table_iteration_next();
        bof_write_word(bf, literal);
    }
    literal_table_end_iteration();
}

// Output the program to a BOFFILE
void gen_code_output_program(BOFFILE bf, code_seq main_cs) {
    BOFHeader header = gen_code_program_header(main_cs);
    bof_write_header(bf, header);
    gen_code_output_seq(bf, main_cs);
    gen_code_output_literals(bf);
    bof_close(bf);
}

// Generate the entire program
void gen_code_program(BOFFILE bf, block_t prog) {
    code_seq main_cs = code_utils_set_up_program(); // calls save registers
    code_seq_concat(&main_cs, gen_code_block(prog));
    code_seq_concat(&main_cs, code_utils_tear_down_program());
    gen_code_output_program(bf, main_cs);
}

// Generate code for a block
code_seq gen_code_block(block_t block) {
    code_seq ret = code_seq_empty(); 
    
    if (block.var_decls.var_decls!=NULL) {
        code_seq var_decls_cs = gen_code_var_decls(block.var_decls);
        code_seq_concat(&ret, var_decls_cs);
    }
    
    if (block.const_decls.start!=NULL) {
        code_seq const_decls_cs = gen_code_const_decls(block.const_decls);
        code_seq_concat(&ret, const_decls_cs);
    }
    
    int total_stack_space = code_seq_size(ret);
    code_seq_concat(&ret, code_seq_singleton(code_cpr(3, FP)));
    code_seq_concat(&ret, code_utils_save_registers_for_AR()); 
    
    if (block.stmts.stmts_kind!=empty_stmts_e) {
        code_seq stmts_cs = gen_code_stmts(block.stmts);
        code_seq_concat(&ret, stmts_cs);
    }
    
    code_seq_concat(&ret, code_utils_restore_registers_from_AR());
    code_seq_concat(&ret, code_utils_deallocate_stack_space(total_stack_space/2));
    
    return ret;
}

// Generate code for variable declarations
code_seq gen_code_var_decls(var_decls_t var_decls) {
    code_seq ret = code_seq_empty();
    var_decl_t *vdp = var_decls.var_decls;

    while (vdp != NULL) {
        // Generate code for each variable declaration
        code_seq var_decl_cs = gen_code_var_decl(*vdp);
        code_seq_concat(&var_decl_cs, ret);
        ret = var_decl_cs;
        vdp = vdp->next;
    }
        
    return ret;
}

// Generate code for a single variable declaration
code_seq gen_code_var_decl(var_decl_t var_decl) {
    code_seq ret = gen_code_idents(var_decl.ident_list);
    return ret;
}

// Generate code for the identifiers in idents
code_seq gen_code_idents(ident_list_t idents) {
    code_seq ret = code_seq_empty();
    ident_t *idp = idents.start;
    
    while (idp != NULL) {
        // Allocate space for the variable on the stack and initialize
        // alloc backwards so 1st variables allocated last, because these 1st variables are at top of stack (stack grows down) so at higher address
        code_seq alloc_initialize_space = code_utils_allocate_stack_space(1);
   	    code_seq_add_to_end(&alloc_initialize_space, code_lit(SP, 0, 0));
        code_seq_concat(&alloc_initialize_space, ret);
        ret = alloc_initialize_space;
        
        idp = idp->next;
    }
    
    return ret;
}

// Generate code for constant declarations
code_seq gen_code_const_decls(const_decls_t const_decls) {
    code_seq ret = code_seq_empty();
    const_decl_t *cd_listp = const_decls.start;

    while (cd_listp != NULL) {
        // Generate code for each constant declaration
        code_seq const_decl_cs = gen_code_const_decl(*cd_listp);
        code_seq_concat(&const_decl_cs, ret);
        ret = const_decl_cs;
        
        cd_listp = cd_listp->next;
    }

    return ret;
}

// Generate code for a single constant declaration
code_seq gen_code_const_decl(const_decl_t const_decl) {
    code_seq ret = code_seq_empty();

    // Traverse the list of constant definitions
    code_seq const_def_list_cs = gen_code_const_def_list(const_decl.const_def_list);
    code_seq_concat(&const_def_list_cs, ret);
    ret = const_def_list_cs;

    return ret;
}

// Generate code for a list of constant definitions
code_seq gen_code_const_def_list(const_def_list_t const_def_list) {
    code_seq ret = code_seq_empty();
    const_def_t *cdp = const_def_list.start;

    while (cdp != NULL) {
        // Generate code for each constant definition
        code_seq const_def_cs = gen_code_const_def(*cdp);
        code_seq_concat(&const_def_cs, ret);
        ret = const_def_cs;
        cdp = cdp->next;
    }

    return ret;
}

// Generate code for a single constant definition
code_seq gen_code_const_def(const_def_t const_def) {
    code_seq ret = code_seq_empty();
    
    // Find the offset of the constant in the literal table
    unsigned int literal_offset = literal_table_lookup(const_def.number.text, const_def.number.value);

    // Allocate space for the constant on the stack & store the constant value at the allocated space
    code_seq alloc_initialize_space = code_utils_allocate_stack_space(1);
    code_seq_add_to_end(&alloc_initialize_space, code_cpw(SP, 0, GP, literal_offset)); // Copy constant value to stack
    code_seq_concat(&alloc_initialize_space, ret);
    ret = alloc_initialize_space;
        
    return ret;

}

























// Generate code for a list of statements----------------------------------------------------------------------------------------------------works
code_seq gen_code_stmts(stmts_t stmts) {
    code_seq ret = code_seq_empty();
    code_seq_concat(&ret, gen_code_stmt_list(stmts.stmt_list));

    return ret;
}

// Generate code for a list of statements--------------------------------------------------------------------------------------------------------works
code_seq gen_code_stmt_list(stmt_list_t stmt_list) {
    code_seq ret = code_seq_empty();
    stmt_t *stmt = stmt_list.start;
    
    while (stmt != NULL) {
        code_seq stmt_cs = gen_code_stmt(*stmt); 
        code_seq_concat(&ret, stmt_cs);
        stmt = stmt->next;
    }
    return ret;
}


// Generate code for a single statement---------------------------------------------------------------------------------------------------------------works
code_seq gen_code_stmt(stmt_t stmt) {
    switch (stmt.stmt_kind) {
        case assign_stmt:
            return gen_code_assign_stmt(stmt.data.assign_stmt);
        case if_stmt:
            return gen_code_if_stmt(stmt.data.if_stmt);
        case while_stmt:
            return gen_code_while_stmt(stmt.data.while_stmt);
        case read_stmt:
            return gen_code_read_stmt(stmt.data.read_stmt);
        case print_stmt:
            return gen_code_print_stmt(stmt.data.print_stmt);
        case block_stmt:
            return gen_code_block_stmt(stmt.data.block_stmt);
        default:
            bail_with_error("Unknown stmt_kind (%d) in gen_code_stmt!", stmt.stmt_kind);
    }
    return code_seq_empty(); // should never reach here
}

// Generate code for an assignment statement------------------------------------------------------------------------------------------------------------works
code_seq gen_code_assign_stmt(assign_stmt_t stmt) {
    // Generate code for the right-hand side expression
    code_seq ret = gen_code_expr(*stmt.expr);

    // Pop the result of the expression into $r3
    code_seq_concat(&ret, code_seq_singleton(code_lwr(5, SP, 0))); // Load result into $r5
    code_seq_concat(&ret, code_utils_deallocate_stack_space(1)); // Deallocate stack space used for result

    // Compute the frame pointer for the variable's scope
    code_seq fp_seq = code_utils_compute_fp(4, stmt.idu->levelsOutward); // Compute FP into $r4
    code_seq_concat(&ret, fp_seq);

    // Store the value in the variable's memory location
    unsigned int offset_count = id_use_get_attrs(stmt.idu)->offset_count;
    code_seq_add_to_end(&ret, code_swr(4, offset_count, 5)); // Store $r5 into memory at offset

    return ret;
}


// Generate code for a block statement----------------------------------------------------------------------------------------------------------------works
code_seq gen_code_block_stmt(block_stmt_t stmt) {
    return gen_code_block(*stmt.block);
}

// Generate code for an if statement-------------------------------------------------------------------------------------------------------------------works
code_seq gen_code_if_stmt(if_stmt_t stmt) {
    code_seq ret = gen_code_condition(stmt.condition); // Evaluate condition which gets put in stack

    // can either be: if-then or if-then-else
    code_seq then_cs = gen_code_stmts(*stmt.then_stmts);
    code_seq else_cs = (stmt.else_stmts->stmts_kind!=empty_stmts_e) ? gen_code_stmts(*stmt.else_stmts) : code_seq_empty();

    int then_len = code_seq_size(then_cs);
    int else_len = code_seq_size(else_cs);

    // Load 0 into $r6 for comparison
    code_seq_add_to_end(&ret, code_lit(SP, -1, 0));
    
    // If condition is false, skip "then" block
    code_seq_add_to_end(&ret, code_beq(SP, -1, then_len+2)); // Skip "then" block if false
    code_seq_concat(&ret, then_cs); // then block

    // If there's an "else" block, jump over it after executing "then"
    if (!code_seq_is_empty(else_cs)) {
        code_seq_add_to_end(&ret, code_jrel(else_len+1));
    }
    else {
        code_seq_add_to_end(&ret, code_jrel(else_len));
    }
    
    code_seq_concat(&ret, else_cs);
    code_seq_concat(&ret, code_utils_deallocate_stack_space(1)); // Clean up the stack
    return ret;
}

// Generate code for a while statement
code_seq gen_code_while_stmt(while_stmt_t stmt) {
    code_seq ret = gen_code_condition(stmt.condition); // Evaluate condition which gets put in stack
    int cond_len = code_seq_size(ret);
    
    code_seq body_cs = gen_code_stmts(*stmt.body); // Generate body code
    int body_len = code_seq_size(body_cs);

    // Load 0 into $r6 for comparison
    code_seq_add_to_end(&ret, code_lit(SP, -1, 0));

    // If condition is false, skip "body" block
    code_seq_add_to_end(&ret, code_beq(SP, -1, body_len+2)); // Skip "body" block if false
    code_seq_concat(&ret, body_cs); // body block
    
    // Jump back to condition
    int jump_back_offset = -(cond_len + body_len + 2);
    code_seq_add_to_end(&ret, code_jrel(jump_back_offset));
    
    code_seq_concat(&ret, code_utils_deallocate_stack_space(1)); // Clean up the stack
    return ret;
}


// Generate code for a read statement---------------------------------------------------------------------------------------------works
code_seq gen_code_read_stmt(read_stmt_t stmt) {
    code_seq ret = code_seq_empty();
    
    code_seq_concat(&ret, code_utils_compute_fp(5, stmt.idu->levelsOutward));
   
    //Calculate the offset within the target's range
    unsigned int offset_count = id_use_get_attrs(stmt.idu)->offset_count;

     //Add instruction to read ASCII value into target's address
    code_seq_add_to_end(&ret, code_rch(5, offset_count));
    
    return ret;

}

// Generate code for a print statement----------------------------------------------------------------------------------------works
code_seq gen_code_print_stmt(print_stmt_t stmt) {
    code_seq ret = code_seq_empty(); // Initialize empty code sequence
    code_seq expr_cs = gen_code_expr(stmt.expr); // Generate the code to evaluate the expression, or just get back number
    code_seq_concat(&ret, expr_cs); // Concatenate the evaluated expression

    // Print the value from the stack
    code_seq print_instr = code_seq_singleton(code_pint(SP, 0));
    code_seq_concat(&ret, print_instr);

    // Deallocate stack space (1 word)
    code_seq dealloc_cs = code_utils_deallocate_stack_space(1);
    code_seq_concat(&ret, dealloc_cs);

    return ret;
}
























// Generate code for conditions----------------------------------------------------------------------------------------------------------------works
code_seq gen_code_condition(condition_t cond) {
    switch (cond.cond_kind) {
        case ck_db:
            return gen_code_db_condition(cond.data.db_cond);
        case ck_rel:
            return gen_code_rel_op_condition(cond.data.rel_op_cond);
        default:
            bail_with_error("Unexpected condition_kind_e (%d)", cond.cond_kind);
    }
    return code_seq_empty(); // unreachable
}

// Generate code for db conditions
code_seq gen_code_db_condition(db_condition_t cond) {
    code_seq ret = gen_code_expr(cond.divisor); // Generate divisor at stack offset 1    // try get dividedn stack top, divisor 2nd from stack
    code_seq_concat(&ret, gen_code_expr(cond.dividend));     // Generate dividend at stack top

    
    // Perform division: SP[0] / SP[1]: dividend / divisor
    code_seq_add_to_end(&ret, code_div(SP, 1));               // Divide SP[0] by SP[-1];

    // Check if remainder is zero, then go to true
    code_seq_add_to_end(&ret, code_lit(SP, -1, 0));            // Load 0 (SP[0]) into $r6   
    code_seq_add_to_end(&ret, code_cfhi(SP, 0));               // Load remainder (HI) into $SP 
    code_seq_add_to_end(&ret, code_beq(SP, -1, 3));           // If remainder is 0, jump to "true"
    
    
    
    // If condition is false (either divisor 0 or just not divisible), push 0
    code_seq_add_to_end(&ret, code_lit(SP, 1, 0));           // Push 0 (false) to the value from stack
    code_seq_add_to_end(&ret, code_jrel(2));                 // Skip the error handling

    // If condition is true (divisible), push 1
    code_seq_add_to_end(&ret, code_lit(SP, 1, 1));           // Push 0 (false) to the 2nd from stack
    code_seq_concat(&ret, code_utils_deallocate_stack_space(1));    // Deallocate one word for the divisor (SP[0])
    return ret;
}

// Generate code for relational operator conditions----------------------------------------------------------------------------------------------works
code_seq gen_code_rel_op_condition(rel_op_condition_t cond) {
    code_seq ret = gen_code_expr(cond.expr2); // evaluate expression 2 to top stack - 1 (2nd from stack)
    code_seq_concat(&ret, gen_code_expr(cond.expr1)); // evaluate expression 1 to top stack 
    code_seq_concat(&ret, gen_code_rel_op(cond.rel_op));
    
    return ret;
}




















// Generate code for expressions----------------------------------------------------------------------------------------works
code_seq gen_code_expr(expr_t expr) {
    switch (expr.expr_kind) {
        case expr_bin:
            return gen_code_binary_op_expr(expr.data.binary);
        case expr_ident:
            return gen_code_ident(expr.data.ident); 
        case expr_number:
            return gen_code_number(expr.data.number); 
        case expr_negated:
            return gen_code_negated_expr(expr.data.negated);
        default:
            bail_with_error("Unexpected expr_kind_e (%d)", expr.expr_kind);
    }
    return code_seq_empty(); // unreachable
}

// Generate binary operation expressions-------------------------------------------------------------------------------------works
code_seq gen_code_binary_op_expr(binary_op_expr_t expr) {
    code_seq ret = gen_code_expr(*expr.expr1);
    code_seq_concat(&ret, gen_code_expr(*expr.expr2));
    code_seq_concat(&ret, gen_code_op(expr.arith_op));
    return ret;
}

// Generate negated expressions-----------------------------------------------------------------------------------------works
code_seq gen_code_negated_expr(negated_expr_t expr) {
    code_seq ret = gen_code_expr(*expr.expr); // Generate the inner to get expression--get the number literal which is on stack
    code_seq_concat(&ret, code_seq_singleton(code_neg(SP, 0, SP, 0))); // Negate the value at the top of the stack
    return ret;
}

// Generate code for identifiers----------------------------------------------------------------------------------------works
code_seq gen_code_ident(ident_t id) {
    code_seq ret = code_utils_allocate_stack_space(1); // Allocate 1 word
    code_seq_concat(&ret, code_utils_compute_fp(3, id.idu->levelsOutward)); // Compute FP for variable's AR into $r3
    unsigned int offset_count = id_use_get_attrs(id.idu)->offset_count; // Retrieve the offset
    code_seq_add_to_end(&ret, code_cpw(SP, 0, 3, offset_count));       // Push value at $r3 + offset to stack

    return ret;
}

// Generate code for number literals-------------------------------------------------------------------------------------works
code_seq gen_code_number(number_t number) {
    unsigned int offset = literal_table_lookup(number.text, number.value); // Offset in the literal table
    code_seq ret = code_utils_allocate_stack_space(1); // Allocate 1 word
    code_seq_add_to_end(&ret, code_cpw(SP, 0, GP, offset)); // Copy literal value to stack
    return ret;
}

// Generate code for an operator-------------------------------------------------------------------------------------works
code_seq gen_code_op(token_t op) {
    switch (op.code) {
        case plussym:
        case minussym:
        case multsym:
        case divsym:
            return gen_code_arith_op(op);
        case eqsym:
        case neqsym:
        case ltsym:
        case leqsym:
        case gtsym:
        case geqsym:
            return gen_code_rel_op(op);
        default:
            bail_with_error("Unknown token code (%d) in gen_code_op", op.code);
    }
    return code_seq_empty(); // should never reach here
}

// Generate code for arithmetic operator---------------------------------------------------------------------------------works
code_seq gen_code_arith_op(token_t op) {
    code_seq ret = code_utils_deallocate_stack_space(1);
    switch (op.code) {
        case plussym:
            code_seq_concat(&ret, code_seq_singleton(code_add(SP, 0, SP, -1)));
            break;
        case minussym:
            code_seq_concat(&ret, code_seq_singleton(code_sub(SP, 0, SP, -1)));
            break;
        case multsym:
            code_seq_concat(&ret, code_seq_singleton(code_mul(SP, -1)));
            code_seq_concat(&ret, code_seq_singleton(code_cflo(SP, 0)));
            break;
        case divsym:
            code_seq_concat(&ret, code_seq_singleton(code_div(SP, -1)));
            code_seq_concat(&ret, code_seq_singleton(code_cflo(SP, 0)));
            break;
        default:
            bail_with_error("Unknown arithmetic operator (%d) in gen_code_arith_op", op.code);
    }

    return ret;
}

// Generate code for relation operator
code_seq gen_code_rel_op(token_t op) {
    //bail_with_error("problem----------------------------------------------------------------------------");
    code_seq ret = code_seq_empty();
    
    code_seq do_op = code_seq_empty();
    // Compare $r3 (left) and $r4 (right), push result (1 or 0) onto stacl
    switch (op.code) {
        case eqsym:
        case eqeqsym:
            do_op = code_seq_singleton(code_beq(SP, 1, 3)); // If equal, jump to "true"
            break;
        case neqsym:
            do_op = code_seq_singleton(code_bne(SP, 1, 3)); // If not equal, jump to "true"
            break;
        case ltsym:
            do_op = code_seq_singleton(code_sub(SP, 1, SP, 1));
            code_seq_add_to_end(&do_op, code_bltz(SP, 1, 3)); // If less, jump to "true"
            break;
        case leqsym:  
            do_op = code_seq_singleton(code_sub(SP, 1, SP, 1));
            code_seq_add_to_end(&do_op, code_blez(SP, 1, 3)); // If less or equal, jump to "true"
            break;
        case gtsym:  
            do_op = code_seq_singleton(code_sub(SP, 1, SP, 1));
            code_seq_add_to_end(&do_op, code_bgtz(SP, 1, 3)); // If greater, jump to "true"
            break;
        case geqsym:
            do_op = code_seq_singleton(code_sub(SP, 1, SP, 1));
            code_seq_add_to_end(&do_op, code_bgez(SP, 1, 3)); // If greater or equal, jump to "true"
            break;
        default:
            bail_with_error("Unknown relational operator (%d) in gen_code_rel_op_condition");
    }
    code_seq_concat(&ret, do_op);

    // If condition is false, push 0
    code_seq_add_to_end(&ret, code_lit(SP, 1, 0)); // Push 0 (false)
    code_seq_add_to_end(&ret, code_jrel(2)); // Skip over "true"

    // If condition is true, push 1
    code_seq_add_to_end(&ret, code_lit(SP, 1, 1)); // Push 1 (true) onto 2nd from stack
    code_seq_add_to_end(&ret, code_ari(SP, 1)); // deallocate one word from stack
    //code_seq_concat(&ret, code_utils_deallocate_stack_space(1)); // dealloc top stack since we place truth at 2nd from stack
    return ret;
}