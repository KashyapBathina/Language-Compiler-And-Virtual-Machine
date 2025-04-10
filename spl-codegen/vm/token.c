#include "token.h"

#define NUM_TOKEN_TYPES 35

// Translation from enum values to strings
static const char *ttstrs[NUM_TOKEN_TYPES] =
    {"identsym", "numbersym", "dottextsym", "dotdatasym", "dotendsym",
    "colonsym", "equalsym",
    "addopsym", "subopsym", "andopsym", "boropsym", "noropsym", "xoropsym",
    "mulopsym", "divopsym", "sllopsym", "srlopsym", "mfhiopsym", "mfloopsym",
    "jropsym",
    "addiopsym", "andiopsym", "boriopsym", "xoriopsym", "noriopsym",
    "beqopsym", "bgezopsym", "bgtzopsym", "bltzopsym", "bneopsym",
    "lwopsym", "swopsym", "jmpaopsym", "callopsym", "rtnopsym"
};

// Requires: fname != NULL
// Create and return a fresh token with the given information
token token_make(token_type typ, const char *fname,
		 unsigned int line, unsigned int start_column,
		 const char *text, word_type value) {
    token ret;
    ret.typ = typ;
    ret.filename = fname;
    ret.line = line;
    ret.start_column = start_column;
    ret.text = text;
    ret.value = value;
    return ret;
}


// Return the name of the token_type enum
// corresponding to the given token_type value
const char *ttyp2str(token_type ttyp)
{
    return ttstrs[ttyp];
}
