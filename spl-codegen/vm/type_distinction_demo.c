// $Id: type_distinction_demo.c,v 1.1 2024/07/28 13:02:44 leavens Exp $
// This demonstration shows how one could leverage the C type checker
// to distinguish word and byte addresses.
// Unfortunately, one has to use structs for this,
// becuase C does structural type checking for all types except struct types
// yet it does by-name (nominal) type checking for struct types.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// in C, type checking will distinguish these types
typedef struct w_s { unsigned int w; } word_addr;
typedef struct b_s { unsigned int b; } byte_addr;

// An example conversion factor
#define BYTES_PER_WORD 4

// Return the equivalent of the word address w as a byte address
byte_addr word2byte_address(word_addr w)
{
    byte_addr ret;
    ret.b = BYTES_PER_WORD * w.w;
    return ret;
}

// Requires: b.b is a multiple of BYTES_PER_WORD.
// Return the equivalent of the byte address b as a word address
word_addr byte2word_address(byte_addr b)
{
    assert((b.b % BYTES_PER_WORD) == 0);
    word_addr ret;
    ret.w = b.b / BYTES_PER_WORD;
    return ret;
}

// A little demonstration
int main()
{
    word_addr worda;
    byte_addr bytea;
    worda.w = 1;
    bytea = word2byte_address(worda);  // okay, checked conversion
    // bytea = worda;   // type error!
    worda.w += 1;
    bytea = word2byte_address(worda);
    bytea.b += 4;
    worda = byte2word_address(bytea);
    printf("worda: %d, bytea: %d\n", worda.w, bytea.b);
    exit(0);
}
