#!/bin/sh
: ${PREFIX=lexer_test}
for suf in bof lst out
do	      
    for i in $@
    do
	rm -f ${PREFIX}${i}.${suf}
	make IMTHEINSTRUCTOR=true ${PREFIX}${i}.${suf}
    done
done
