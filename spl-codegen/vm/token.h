/* $Id: token.h,v 1.5 2024/07/17 19:55:30 leavens Exp $ */
#ifndef _TOKEN_H
#define _TOKEN_H
#include "machine_types.h"

#define MAX_IDENT_LENGTH 255

// types of tokens
typedef enum {
    identsym, numbersym, dottextsym, dotdatasym, dotendsym,
    colonsym, equalsym,
    addopsym, subopsym, andopsym, boropsym, noropsym, xoropsym,
    mulopsym, divopsym, sllopsym, srlopsym, mfhiopsym, mfloopsym, jropsym,
    addiopsym, andiopsym, boriopsym, xoriopsym, noriopsym,
    beqopsym, bgezopsym, bgtzopsym, bltzopsym, bneopsym, lwopsym, swopsym,
    jmpaopsym, callopsym, rtnopsym
} token_type;

// information about each token
typedef struct token {
    token_type typ;
    const char *filename;
    unsigned int line;    // the line the token occurs on
    unsigned int start_column; // starting column for the token
    const char *text; // the characters that make up the token's input
    word_type value; // when typ==numbersym, its value
} token;

// Requires: fname != NULL
// Create and return a fresh token with the given information
extern token token_make(token_type typ, const char *fname,
			unsigned int line, unsigned int start_column,
			const char *text, word_type value);

// Return the name of the token_type enum
// corresponding to the given token_type value
extern const char *ttyp2str(token_type ttyp);

#endif
