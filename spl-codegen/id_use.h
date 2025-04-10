/* $Id: id_use.h,v 1.7 2024/10/23 13:13:07 leavens Exp $ */
#ifndef _ID_USE_H
#define _ID_USE_H
#include "id_attrs.h"
// we'll use lexical_address in HW4
#include "lexical_address.h"

// An id_use struct gives all the information from
// a lookup in the symbol table for a name:
// the (pointer to the) id_attrs (attributes)
// and the number of lexical levels out
// from the current scope where the name was declared.
typedef struct {
    id_attrs *attrs;
    unsigned int levelsOutward;    
} id_use;

// Requires: attrs != NULL
// Return a (pointer to a fresh) id_use struct containing the attributes
// given by attrs and the information about the number of lexical levels
// outward from the current scope where the declaration was found.
extern id_use *id_use_create(id_attrs *attrs, unsigned int levelsOut);

// Requires: idu != NULL
// Return a pointer to the attributes of this id_use
// and the result will never be NULL
extern id_attrs *id_use_get_attrs(id_use *idu);

// Requires: idu != NULL
// Return (a pointer to) the lexical address for idu.
extern lexical_address *id_use_2_lexical_address(id_use *idu);
#endif
