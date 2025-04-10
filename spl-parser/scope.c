/* $Id: scope.c,v 1.5 2023/11/03 12:29:45 leavens Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scope.h"
#include "utilities.h"

// Allocate a fresh scope symbol table and return (a pointer to) it.
// Issues an error message (on stderr) if there is no space
// and exits with a failure error code in that case.
scope_t *scope_create()
{
    scope_t *new_s
	= (scope_t *) malloc(sizeof(scope_t));
    if (new_s == NULL) {
	bail_with_error("No space for new scope_t!");
    }
    new_s->size = 0;
    new_s->loc_count = 0;
    for (int j = 0; j < MAX_SCOPE_SIZE; j++) {
	new_s->entries[j] = NULL;
    }
    return new_s;
}

// Return the number of constant and variables declarations
// that have been added to this scope.
extern unsigned int scope_loc_count(scope_t *s)
{
    return s->loc_count;
}

// Return the current scope's size (number of declared ids).
unsigned int scope_size(scope_t *s)
{
    return s->size;
}

// Is the current scope full?
bool scope_full(scope_t *s)
{
    return scope_size(s) >= MAX_SCOPE_SIZE;
}

// Requires: assoc != NULL && !scope_full() && !scope_declared(assoc->id);
// Add an association from the given name to the given id attributes
// in the current scope.
// If assoc->attrs->kind != procedure_idk, 
// then this stores the scope_count value into assoc->attrs->offset_count
// and then increases loc_count by 1.
static void scope_add(scope_t *s, scope_assoc_t *assoc)
{
    assoc->attrs->offset_count = (s->loc_count)++;
    s->entries[(s->size)++] = assoc;
    
}

// Requires: !scope_declared(name) && attrs != NULL;
// Modify the current scope symbol table to
// add an association from the given name to the given id_attrs attrs,
// and if attrs->kind != procedure, 
// then this stores the loc_count value into attrs->offset_count
// and then increases the loc_count for this scope by 1.
void scope_insert(scope_t *s, const char *name, id_attrs *attrs)
{
    
    scope_assoc_t *new_assoc = malloc(sizeof(scope_assoc_t));
    if (new_assoc == NULL) {
	bail_with_error("No space for association!");
    }
    new_assoc->id = name;
    new_assoc->attrs = attrs;
    scope_add(s, new_assoc);
}

// Requires: name != NULL;
// Is the given name associated with some attributes in the current scope?
bool scope_declared(scope_t *s, const char *name)
{
    
    return scope_lookup(s, name) != NULL;
}

// Requires: name != NULL and scope_initialize() has been called previously.
// Return (a pointer to) the attributes of the given name in the current scope
// or NULL if there is no association for name.
id_attrs *scope_lookup(scope_t *s, const char *name)
{
    int i;
    
    for (i = 0; i < s->size; i++) {
	
	if (strcmp(s->entries[i]->id, name) == 0) {
	    
	    return s->entries[i]->attrs;
	}
    }
    
    return NULL;
}