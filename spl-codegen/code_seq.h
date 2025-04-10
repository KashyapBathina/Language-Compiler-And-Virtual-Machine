/* $Id: code_seq.h,v 1.3 2024/11/08 21:01:43 leavens Exp $ */
#ifndef _CODE_SEQ_H
#define _CODE_SEQ_H
#include <stdbool.h>
#include "code.h"

// code sequences are linked lists
// with an additional last pointer to the last node
typedef struct {
    code *first;
    code *last;
} code_seq;

// Return an empty code_seq
extern code_seq code_seq_empty();

// Return a code_seq containing just the given code
extern code_seq code_seq_singleton(code *c);

// Is seq empty?
extern bool code_seq_is_empty(code_seq seq);

// Requires: !code_seq_is_empty(seq)
// Return the first element of the given code sequence, seq
extern code *code_seq_first(code_seq seq);

// Requires: !code_seq_is_empty(seq)
// Return a new code_seq containing
// the rest of the given sequence, seq
// Note that seq is not modified
extern code_seq code_seq_rest(code_seq seq);

// Return the size (number of instructions/words) in seq
extern unsigned int code_seq_size(code_seq seq);

// Requires: !code_seq_is_empty(seq)
// Return the last element in the given sequence
extern code *code_seq_last_elem(code_seq seq);

// Requires: c != NULL && seq != NULL
// Modify seq to add the given code *c added to its end
extern void code_seq_add_to_end(code_seq *seq, code *c);

// Requires: s1 != NULL && s2 != NULL
// Modifies s1 to be the concatenation of s1 followed by s2
extern void code_seq_concat(code_seq *s1, code_seq s2);

// Requires: out is open for writing.
// Print the instructions in the code_seq to out
// in assembly language format
extern void code_seq_debug_print(FILE *out, code_seq seq);

#endif
