/* $Id: symtab.c,v 1.9 2024/11/10 22:48:40 leavens Exp $ */
#include <stddef.h>
#include "symtab.h"
#include "scope.h"
#include "utilities.h"

// The symbol table is a stack of scope (see the scope module).

// index of the top of the stack of scopes
static int symtab_top_idx = -1;

// the symbol table itself
static scope_t *symtab[MAX_NESTING];

// initialize the symbol table
void symtab_initialize()
{
    // initialize the internal state
    symtab_top_idx = -1;
    for (int i = 0; i < MAX_NESTING; i++) {
	symtab[i] = NULL;
    }
}

// Return the number of scopes currently in the symbol table.
unsigned int symtab_size()
{
    return symtab_top_idx + 1;
}

// Does this symbol table have any scopes in it?
bool symtab_empty()
{
    return symtab_size() == 0;
}

// Return the current scope's next location count
// (of constants and variables).
unsigned int symtab_scope_loc_count()
{
    return scope_loc_count(symtab[symtab_top_idx]);
}

// Return the current scope's size (the number of declared ids).
unsigned int symtab_scope_size()
{
    return scope_size(symtab[symtab_top_idx]);
}

// Is the current scope full?
bool symtab_scope_full()
{
    return scope_full(symtab[symtab_top_idx]);
}

// Return the current nesting level of the symbol table
// (this is the number of (client made) symtab_enter_scope() calls
// minus the number of symtab_leave_scope() calls
unsigned int symtab_current_nesting_level()
{
    // assert(symtab_top_idx >= 0);
    return symtab_top_idx;
}

// Is the symbol table itself full
// (i.e., is symtab_current_nesting_level() equal to MAX_NESTING-1)?
bool symtab_full()
{
    return symtab_current_nesting_level() == MAX_NESTING - 1;
}

// Is the given name associated with some attributes?
// (this looks back through all scopes).
bool symtab_defined(const char *name)
{
    return symtab_lookup(name) != NULL;
}

// Is the given name associated with some attributes in the current scope?
// (this only looks in the current scope).
bool symtab_defined_in_current_scope(const char *name)
{
    id_attrs *attrs = scope_lookup(symtab[symtab_top_idx], name);
    return attrs != NULL;
}


// Put the given name, which is to be declared with kind k,
// and has its declaration at the given file location (floc),
// into the current scope's symbol table at the offset scope_next_offset().
static void add_ident(scope_t *s, const char*name, id_attrs *attrs)
{
    id_attrs *old_attrs = scope_lookup(s, name);
    if (old_attrs != NULL) {
        bail_with_prog_error(attrs->file_loc,
		      "%s \"%s\" is already declared as a %s",
		      id_attrs_id_kind_string(attrs->kind), name,
		      id_attrs_id_kind_string(old_attrs->kind));
    } else {
	scope_insert(s, name, attrs);
    }
}

// Requires: !symtab_defined(name) && attrs != NULL
// Modify the current scope (as recorded in the symbol table) to
// add an association from the given name to attributes appropriate
// for k and floc.
void symtab_insert(const char *name, id_attrs *attrs)
{
    add_ident(symtab[symtab_top_idx], name, attrs);
}

// Requires: !symtab_full()
// Start a new scope (for a procedure)
void symtab_enter_scope()
{
    symtab_top_idx++;
    symtab[symtab_top_idx] = scope_create();
}

// Requires: !symtab_empty()
void symtab_leave_scope()
{
    if (symtab_top_idx < 0) {
	bail_with_error("Cannot leave scope, no scope on symtab's stack!");
    }
    symtab_top_idx--;
}

// Return (a pointer to) the attributes of the given name 
// or NULL if there is no association for name in the symbol table.
// (this looks back through all scopes).
id_use *symtab_lookup(const char *name)
{
    unsigned int levelsOut = 0;
    for (int level = symtab_top_idx; 0 <= level; level--) {
	id_attrs *attrs = scope_lookup(symtab[level], name);
	if (attrs != NULL) {
	    // debug_print("symtab_lookup returning with levelsOut == %d for %s\n",
	    //       	levelsOut, name);
	    return id_use_create(attrs, levelsOut);
	}
	levelsOut++;
    }
    return NULL;
}

// We'll use lexical addresses in HW4...
// Requires: symtab_defined(name)
// Return (a pointer to) the lexical address of the given name
// or NULL if there is no association for name.
/*
lexical_address *symtab_lexical_address(const char *name)
{
    // maintaining: -1 <= level <= symtab_top_idx;
    // maintaining: (for all int j:
    //                level < j <= symtab_top_idx
    //                   ==> !scope_defined(symtab[j], name))
    for (int level = symtab_top_idx; 0 <= level; level--) {
	id_attrs *attrs = scope_lookup(symtab[level], name);
	if (attrs != NULL) {
	    return lexical_address_create(symtab_top_idx - level,
					  attrs->loc_offset);
	}
    }
    bail_with_error("Couldn't find %s for symtab_lexical_address!", name);
    return NULL;
}
*/
