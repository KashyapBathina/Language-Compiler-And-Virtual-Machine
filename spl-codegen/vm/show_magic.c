// $Id: show_magic.c,v 1.1 2024/07/09 17:48:37 leavens Exp $

#include <stdio.h>
#include <stdlib.h>
#include "bof.h"

extern void bof_write_magic(FILE *f);

int main() {
    bof_write_magic(stdout);
    exit(EXIT_SUCCESS);
}
