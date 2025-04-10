/* $Id: scope.h,v 1.3 2023/11/03 12:29:45 leavens Exp $ */
#ifndef _SCOPE_H
#define _SCOPE_H

#include <stdbool.h>
#include "ast.h"
#include "machine_types.h"
#include "id_attrs.h"

// Maximum number of declarations
// that can be stored in a scope
#define MAX_SCOPE_SIZE 4096

typedef struct {
    const char *id;
    id_attrs *attrs;
} scope_assoc_t;

// Invariant: 0 <= size < MAX_SCOPE_SIZE;
typedef struct scope_s {
    unsigned int size;
    // num. of associations in this scope
    unsigned int loc_count;
    scope_assoc_t
                *entries[MAX_SCOPE_SIZE];
} scope_t;

// Allocate a fresh scope symbol table and return (a pointer to) it.
// Issues an error message (on stderr) if there is no space
// and exits with a failure error code in that case.
extern scope_t *scope_create();

// Return the number of constant and variables declarations
// that have been added to this scope.
extern address_type scope_loc_count(scope_t *s);

// Return the number of declared identifier associations in s
extern unsigned int scope_size(scope_t *s);

// Is the current scope full?
extern bool scope_full(scope_t *s);

// Is the given name associated with some attributes in the current scope?
extern bool scope_declared(scope_t *s, const char *name);

// Requires: attrs != NULL &&
//                  !scope_declared(name);
// Add an association from name to attrs,
// store the next_loc_offset value into
// attrs->loc_offset, then increase
// the next_loc_offset for s by 1.
extern void scope_insert(scope_t *s,
      const char *name, id_attrs *attrs);

// Return (a pointer to) the attributes
// of the given name in s
// or NULL if name is not declared in s
extern id_attrs *scope_lookup(scope_t *s,
                        const char *name);

#endif