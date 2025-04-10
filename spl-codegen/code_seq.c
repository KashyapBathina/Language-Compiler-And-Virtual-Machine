/* $Id: code_seq.c,v 1.4 2024/11/08 21:01:43 leavens Exp $ */
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "utilities.h"
#include "regname.h"
#include "code_seq.h"

static void code_seq_okay(code_seq seq)
{
    // seq.first and seq.last are either both null or both not null
    assert((seq.first == NULL) == (seq.last == NULL));
}

// Return an empty code_seq
code_seq code_seq_empty()
{
    code_seq ret;
    ret.first = NULL;
    ret.last = NULL;
    code_seq_okay(ret);
    return ret;
}

// Requires: c != NULL
// Return a code_seq containing just the given code
code_seq code_seq_singleton(code *c)
{
    code_seq ret;
    ret.first = c;
    ret.last = c;
    code_seq_okay(ret);
    return ret;
}

// Is seq empty?
bool code_seq_is_empty(code_seq seq)
{
    code_seq_okay(seq);
    return seq.first == NULL;
}

// Requires: !code_seq_is_empty(seq)
// Return the first element of the given code sequence, seq
code *code_seq_first(code_seq seq)
{
    assert(!code_seq_is_empty(seq));
    return seq.first;
}

// Requires: !code_seq_is_empty(seq)
// Return a new code_seq containing
// the rest of the given sequence, seq
// Note that seq is not modified
code_seq code_seq_rest(code_seq seq)
{
    assert(!code_seq_is_empty(seq));
    code *first = seq.first;
    code_seq ret;
    ret.first = first->next;
    if (ret.first == NULL) {
	ret.last = NULL;
    } else {
	ret.last = seq.last;
    }
    code_seq_okay(ret);
    return ret;
}

// Return the size (number of instructions/words) in seq
unsigned int code_seq_size(code_seq seq)
{
    unsigned int ret = 0;
    while (!code_seq_is_empty(seq)) {
	ret++;
	seq = code_seq_rest(seq);
    }
    return ret;
}

// Requires: !code_seq_is_empty(seq)
// Return the last element in the given sequence
code *code_seq_last_elem(code_seq seq)
{
    assert(!code_seq_is_empty(seq));
    return seq.last;
}

// Requires: c != NULL && seq != NULL
// Modify seq to add the given code *c added to its end
void code_seq_add_to_end(code_seq *seq, code *c)
{
    assert(c != NULL);
    if (code_seq_is_empty(*seq)) {
	seq->first = c;
	seq->last = c;
    } else {
	// assert(!code_seq_is_empty(seq));
	code *last = code_seq_last_elem(*seq);
	last->next = c;
	c->next = NULL;
	seq->last = c;
    }
    code_seq_okay(*seq);
}

// Requires: s1 != NULL && s2 != NULL
// Modifies s1 to be the concatenation of s1 followed by s2
void code_seq_concat(code_seq *s1, code_seq s2)
{
    if (code_seq_is_empty(*s1)) {
	s1->first = s2.first;
	s1->last = s2.last;
    } else if (code_seq_is_empty(s2)) {
        ; // s1 is already their concatenation
    } else {
	code *last = code_seq_last_elem(*s1);
	// assert(last != NULL);
	last->next = s2.first;
	s1->last = s2.last;
    }
    code_seq_okay(*s1);
}

// Requires: out is open for writing.
// Print the instructions in the code_seq to out
// in assembly language format
void code_seq_debug_print(FILE *out, code_seq seq)
{
    while(!code_seq_is_empty(seq)) {
	fprintf(out, "%s\n",
		instruction_assembly_form(0, code_seq_first(seq)->instr));
	seq = code_seq_rest(seq);
    }
}
