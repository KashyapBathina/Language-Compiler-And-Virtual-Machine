/* $Id: symtab.h,v 1.5 2023/11/03 12:29:45 leavens Exp $ */
#ifndef _SYMTAB_H
#define _SYMTAB_H

#include "scope.h"
#include "id_use.h"

// Maximum nesting of potential scopes
#define MAX_NESTING 100

// initialize the symbol table
extern void symtab_initialize();

// Return the number of scopes currently in the symbol table.
extern unsigned int symtab_size();

// Does this symbol table have any scopes in it?
extern bool symtab_empty();

// Return the current scope's
// count of variables declared
extern unsigned int symtab_scope_loc_count();

// Return the current scope's size
// (the number of declared ids).
extern unsigned int symtab_scope_size();

// Is the current scope full?
extern bool symtab_scope_full();

// Return the current nesting level 
// (num. of symtab_enter_scope() calls
//  - num. of symtab_leave_scope() calls
extern unsigned int
   symtab_current_nesting_level();

// Is the symbol table itself full?
extern bool symtab_full();

// Is name declared?
// (this looks back through all scopes)
extern bool symtab_declared(const char *name);

// Is name declared in the current scope?
// (this only looks in the current scope)
extern bool
         symtab_declared_in_current_scope(
		        const char *name);

id_attrs *symtab_get_attrs(const char *name); // for scope_check_declare_ident


// Requires: attrs != NULL &&
// !symtab_declared_in_current_scope(name)
// Add an association from the given name
// to the given attributes
extern void symtab_insert(
       const char *name, id_attrs *attrs);

// Requires: !symtab_full()
// Start a new scope (for a block)
extern void symtab_enter_scope();

// Requires: !symtab_empty()
extern void symtab_leave_scope();

// If name is declared, return
// an id_use pointer for it, otherwise
// return NULL if name isn't declared
extern id_use *symtab_lookup(
                       const char *name);

#endif