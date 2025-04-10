/* $Id: symtab.h,v 1.5 2023/11/13 12:52:01 leavens Exp $ */
#ifndef _SYMTAB_H
#define _SYMTAB_H

#include "scope.h"
#include "id_use.h"

// Maximum number of declarations that can be stored in a scope
#define MAX_NESTING 100

// initialize the symbol table
extern void symtab_initialize();

// Return the number of scopes currently in the symbol table.
extern unsigned int symtab_size();

// Does this symbol table have any scopes in it?
extern bool symtab_empty();

// Return the current scope's next location count
// (of constants and variables).
extern unsigned int symtab_scope_loc_count();

// Return the current scope's size (the number of declared ids).
extern unsigned int symtab_scope_size();

// Is the current scope full?
extern bool symtab_scope_full();

// Return the current nesting level of the symbol table
// (this is the number of symtab_enter_scope() calls
// minus the number of symtab_leave_scope() calls
extern unsigned int symtab_current_nesting_level();

// Is the symbol table itself full
// (i.e., is symtab_current_nesting_level() equal to MAX_NESTING-1)?
extern bool symtab_full();

// Is the given name associated with some attributes?
// (this looks back through all scopes).
extern bool symtab_defined(const char *name);

// Is the given name associated with some attributes in the current scope?
// (this only looks in the current scope).
extern bool symtab_defined_in_current_scope(const char *name);

// Requires: !symtab_defined_in_current_scope(name) && attrs != NULL
// Modify the current scope (as recorded in the symbol table) to
// add an association from the given name to the given attributes attrs.
extern void symtab_insert(const char *name, id_attrs *attrs);

// Requires: !symtab_full()
// Start a new scope (for a procedure)
extern void symtab_enter_scope();

// Requires: !symtab_empty()
extern void symtab_leave_scope();

// Return (a pointer to) a struct containing:
// the attributes of the given name (attrs)
// and the number of lexical levels outward
// from the current scope at which the name was declared,
// or NULL if there is no association for name.
extern id_use *symtab_lookup(const char *name);

#endif
