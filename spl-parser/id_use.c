/* $Id: id_use.c,v 1.1 2023/10/15 21:29:24 leavens Exp $ */
#include <stdlib.h>
#include "id_use.h"
#include "utilities.h"

// Requires: attrs != NULL
// Return a (pointer to a fresh) id_use struct containing the attributes
// given by attrs and the information about the number of lexical levels
// outward from the current scope where the declaration was found.
// If there is no space, bail with an error message,
// so this should never return NULL.
extern id_use *id_use_create(id_attrs *attrs, unsigned int levelsOut)
{
    id_use *ret = (id_use *)malloc(sizeof(id_use));
    if (ret == NULL) {
	bail_with_error("No space to allocate id_use!");
    }
    ret->attrs = attrs;
    ret->levelsOutward = levelsOut;
    // Shouldn't create a label for procedures here!
    // A label should only be created when creating the proc_decl's AST!
    return ret;
}

// We'll use lexical addresses in HW4...
// Requires: idu != NULL
// Return (a pointer to) the lexical address for idu.
/*
extern lexical_address *id_use_2_lexical_address(id_use *idu)
{
    lexical_address *ret = (lexical_address *)malloc(sizeof(lexical_address));
    if (ret == NULL) {
	bail_with_error("No space to allocate lexical_address!");
    }
    ret->levelsOutward = idu->levelsOutward;
    ret->offsetInAR = idu->attrs->offset_count * BYTES_PER_WORD;
    return ret;
}
*/
