/* $Id: id_use.c,v 1.10 2024/10/23 13:13:07 leavens Exp $ */
#include <stdlib.h>
#include "machine_types.h"
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

// Requires: idu != NULL
// Return a pointer to the attributes of this id_use
// and the result will never be NULL
id_attrs *id_use_get_attrs(id_use *idu)
{
    assert(idu != NULL);
    return idu->attrs;
}


// Requires: idu != NULL
// Return (a pointer to) the lexical address for idu.
lexical_address *id_use_2_lexical_address(id_use *idu)
{
    lexical_address *ret = (lexical_address *)malloc(sizeof(lexical_address));
    if (ret == NULL) {
	bail_with_error("No space to allocate lexical_address!");
    }
    ret->levelsOutward = idu->levelsOutward;
    ret->offsetInAR = idu->attrs->offset_count;
    return ret;
}
