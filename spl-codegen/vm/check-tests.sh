#!/bin/sh
: ${PREFIX=lexer_test}
for i in $@
do
    emacs ${PREFIX}${i}.lst ${PREFIX}${i}.asm && emacs ${PREFIX}${i}.asm ${PREFIX}${i}.out
done
