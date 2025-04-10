/* $Id: lexical_address.c,v 1.3 2023/11/13 05:13:56 leavens Exp $ */
#include "lexical_address.h"
#include "utilities.h"

// Allocate and return a (fresh) lexical address
// where the levelsOutwards field is levelsOut
// and the offsetInAR field is the byte offset in the AR
lexical_address *lexical_address_create(unsigned int levelsOut,
					unsigned int offset)
{
    lexical_address *ret = (lexical_address *) malloc(sizeof(lexical_address));
    if (ret == NULL) {
	bail_with_error("No space to create a lexical_address!");
    }
    ret->levelsOutward = levelsOut;
    ret->offsetInAR = offset;
    return ret;
}

// Requires: out is not NULL and is open for writing
// Requires: la is not NULL
// Print the lexical address la in the form "(l,o)",
// where l is la->levelsOutwards and o is la->offsetInAR.
// Note: no newline or other spacing is added.
extern void lexical_address_print(FILE *out, lexical_address *la)
{
    fprintf(out, "(%d,%d)", la->levelsOutward, la->offsetInAR);
}
