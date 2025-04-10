#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scope_check.h"
#include "id_attrs.h"
#include "file_location.h"
#include "ast.h"
#include "utilities.h"
#include "symtab.h"

// Function to check the scope of the program
void scope_check_program(block_t prog) {
    symtab_enter_scope();

    // Handle constants, variables, and procedures in the program
    scope_check_const_decls(prog.const_decls);
    scope_check_var_decls(prog.var_decls);
    scope_check_proc_decls(prog.proc_decls);
    prog.stmts = scope_check_stmts(prog.stmts);

    // Ensure the global scope is correctly left
    symtab_leave_scope();
}


// Check constant declarations
void scope_check_const_decls(const_decls_t const_decls) {
    const_decl_t *cdp = const_decls.start;
    while (cdp != NULL) {
        const_def_t *def = cdp->const_def_list.start;
        while (def != NULL) {
            scope_check_declare_ident(def->ident, constant_idk);
            def = def->next;
        }
        cdp = cdp->next;
    }
}

// Check procedure declarations
void scope_check_proc_decls(proc_decls_t proc_decls) {
    proc_decl_t *pdp = proc_decls.proc_decls;
    while (pdp != NULL) {
        ident_t proc_ident = { .file_loc = pdp->file_loc, .type_tag = ident_ast, .name = pdp->name };
        scope_check_declare_ident(proc_ident, procedure_idk);
        symtab_enter_scope();

        // Check declarations within the procedure block
        if (pdp->block) {
            if (pdp->block->const_decls.start) {
                scope_check_const_decls(pdp->block->const_decls);
            }
            if (pdp->block->var_decls.var_decls) {
                scope_check_var_decls(pdp->block->var_decls);
            }
            if (pdp->block->proc_decls.proc_decls) {
                scope_check_proc_decls(pdp->block->proc_decls);
            }
            // Check procedure statements
            if (pdp->block->stmts.stmt_list.start) {
                pdp->block->stmts = scope_check_stmts(pdp->block->stmts);
            }
        }

        symtab_leave_scope();
        pdp = pdp->next;
    }
}



// Check variable declarations
void scope_check_var_decls(var_decls_t var_decls) {
    var_decl_t *vdp = var_decls.var_decls;
    while (vdp != NULL) {
        scope_check_idents(vdp->ident_list, variable_idk);
        vdp = vdp->next;
    }
}



// Check identifiers and report duplicate declarations
void scope_check_idents(ident_list_t ids, id_kind kind) {
    ident_t *idp = ids.start;
    while (idp != NULL) {
        scope_check_declare_ident(*idp, kind);
        idp = idp->next;
    }
}




// Check if the identifier is already declared and handle errors
void scope_check_declare_ident(ident_t id, id_kind kind) {
    // Retrieve attributes if the identifier is already declared in the current scope
    id_attrs *existing_attrs = symtab_get_attrs(id.name);
    if (symtab_declared_in_current_scope(id.name) && existing_attrs) {
        // Use the correct kinds for both the existing identifier and the new one
        const char *existing_kind_str = (existing_attrs->kind == constant_idk) ? "constant" :
                                        (existing_attrs->kind == procedure_idk) ? "procedure" : "variable";
        const char *new_kind_str = (kind == constant_idk) ? "constant" :
                                   (kind == procedure_idk) ? "procedure" : "variable";
        bail_with_prog_error(*(id.file_loc),
                             "%s \"%s\" is already declared as a %s",
                             new_kind_str, id.name, existing_kind_str);
    } else {
        id_attrs *attrs = create_id_attrs(*(id.file_loc), kind, symtab_scope_loc_count());
        symtab_insert(id.name, attrs);
    }
}



// possible area of error


// Ensure that the identifier has been declared, and update AST
id_use *scope_check_ident_declared(file_location floc, const char *name) {
    id_use *ret = symtab_lookup(name);
    if (!ret) {
        bail_with_prog_error(floc, "identifier \"%s\" is not declared!", name);
    }
    return ret;
    
}

// Check the statement to ensure all identifiers are declared
stmt_t scope_check_stmt(stmt_t stmt) {
    switch (stmt.stmt_kind) {
        case assign_stmt:
            if (stmt.data.assign_stmt.name) {
                stmt.data.assign_stmt = scope_check_assign_stmt(stmt.data.assign_stmt);
            }
            break;
        case call_stmt:
            if (stmt.data.call_stmt.name) {
                stmt.data.call_stmt = scope_check_call_stmt(stmt.data.call_stmt);
            }
            break;
        case if_stmt:
            stmt.data.if_stmt = scope_check_if_stmt(stmt.data.if_stmt);
            break;
        case while_stmt:
            stmt.data.while_stmt = scope_check_while_stmt(stmt.data.while_stmt);
            break;
        case read_stmt:
            if (stmt.data.read_stmt.name) {
                stmt.data.read_stmt = scope_check_read_stmt(stmt.data.read_stmt);
            }
            break;
        case print_stmt:
            stmt.data.print_stmt = scope_check_print_stmt(stmt.data.print_stmt);
            break;
        case block_stmt:
            if (stmt.data.block_stmt.block) {
                stmt.data.block_stmt = scope_check_block_stmt(stmt.data.block_stmt);
            }
            break;
        default:
            bail_with_error("Unknown statement type in scope_check_stmt!");
    }
    return stmt;
}



// Check assignment statement
assign_stmt_t scope_check_assign_stmt(assign_stmt_t stmt) {
    if (stmt.name) {
        scope_check_ident_declared(*(stmt.file_loc), stmt.name);
    }
    if (stmt.expr) {
        *stmt.expr = scope_check_expr(*stmt.expr);
    }
    return stmt;
}

// Check call statement
call_stmt_t scope_check_call_stmt(call_stmt_t stmt) {
    if (stmt.name) {
        scope_check_ident_declared(*(stmt.file_loc), stmt.name);
    }
    return stmt;
}

// Check if statement
if_stmt_t scope_check_if_stmt(if_stmt_t stmt) {
    stmt.condition = scope_check_condition(stmt.condition);
    if (stmt.then_stmts && stmt.then_stmts->stmt_list.start) {
        *stmt.then_stmts = scope_check_stmts(*stmt.then_stmts);
    }
    if (stmt.else_stmts && stmt.else_stmts->stmt_list.start) {
        *stmt.else_stmts = scope_check_stmts(*stmt.else_stmts);
    }
    return stmt;
}



// Check while statement
while_stmt_t scope_check_while_stmt(while_stmt_t stmt) {
    stmt.condition = scope_check_condition(stmt.condition);
    if (stmt.body && stmt.body->stmt_list.start) {
        *stmt.body = scope_check_stmts(*stmt.body);
    }
    return stmt;
}

// Check read statement
read_stmt_t scope_check_read_stmt(read_stmt_t stmt) {
    if (stmt.name) {
        scope_check_ident_declared(*(stmt.file_loc), stmt.name);
    }
    return stmt;
}

// Check print statement
print_stmt_t scope_check_print_stmt(print_stmt_t stmt) {
    if (stmt.expr.file_loc) {
        stmt.expr = scope_check_expr(stmt.expr);
    }
    return stmt;
}

// Check block statement
block_stmt_t scope_check_block_stmt(block_stmt_t stmt) {
    symtab_enter_scope();
    if (stmt.block) {
        if (stmt.block->const_decls.start) {
            scope_check_const_decls(stmt.block->const_decls);
        }
        if (stmt.block->var_decls.var_decls) {
            scope_check_var_decls(stmt.block->var_decls);
        }
        if (stmt.block->proc_decls.proc_decls) {
            scope_check_proc_decls(stmt.block->proc_decls);
        }
        if (stmt.block->stmts.stmt_list.start) {
            stmt.block->stmts = scope_check_stmts(stmt.block->stmts);
        }
    }
    symtab_leave_scope();
    return stmt;
}



// source of all errors

// Check list of statements
stmts_t scope_check_stmts(stmts_t stmts) {
    // Check if the statement list is non-empty
    if (stmts.stmts_kind == stmt_list_e) {
        stmt_t *sp = stmts.stmt_list.start;
        while (sp != NULL) {
            *sp = scope_check_stmt(*sp);  // process each statement in the list
            sp = sp->next;
        }
    }
    return stmts;
}




// Check condition
condition_t scope_check_condition(condition_t cond) {
    switch (cond.cond_kind) {
        case ck_db:
            if (&cond.data.db_cond.dividend != NULL) {
                cond.data.db_cond.dividend = scope_check_expr(cond.data.db_cond.dividend);
            }
            if (&cond.data.db_cond.divisor != NULL) {
                cond.data.db_cond.divisor = scope_check_expr(cond.data.db_cond.divisor);
            }
            break;
        case ck_rel:
            if (&cond.data.rel_op_cond.expr1 != NULL) {
                cond.data.rel_op_cond.expr1 = scope_check_expr(cond.data.rel_op_cond.expr1);
            }
            if (&cond.data.rel_op_cond.expr2 != NULL) {
                cond.data.rel_op_cond.expr2 = scope_check_expr(cond.data.rel_op_cond.expr2);
            }
            break;
        default:
            bail_with_error("Unexpected condition type in scope_check_condition.");
    }
    return cond;
}


// Check expression for undeclared identifiers
expr_t scope_check_expr(expr_t exp) {
    switch (exp.expr_kind) {
        case expr_bin:
            if (&exp.data.binary.expr1 != NULL) {
                *exp.data.binary.expr1 = scope_check_expr(*exp.data.binary.expr1);
            }
            if (&exp.data.binary.expr2 != NULL) {
                *exp.data.binary.expr2 = scope_check_expr(*exp.data.binary.expr2);
            }
            break;
        case expr_ident:
            exp.data.ident = scope_check_ident_expr(exp.data.ident);
            break;
        case expr_number:
            break;
        case expr_negated:
            if (exp.data.negated.expr) {
                *exp.data.negated.expr = scope_check_expr(*exp.data.negated.expr);
            }
            break;
        default:
            bail_with_error("Unexpected expression type in scope_check_expr.");
    }
    return exp;
}

// check binary operator expression
binary_op_expr_t scope_check_binary_op_expr(binary_op_expr_t exp) {
    if (&exp.expr1 != NULL) {
        *exp.expr1 = scope_check_expr(*exp.expr1);
    }
    if (&exp.expr2 != NULL) {
        *exp.expr2 = scope_check_expr(*exp.expr2);
    }
    return exp;
}



// Check identifier expressions
ident_t scope_check_ident_expr(ident_t id) {
    scope_check_ident_declared(*(id.file_loc), id.name);
    return id;
}


