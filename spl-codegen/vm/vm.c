#include <stdio.h>
#include <stdlib.h>
#include "bof.h"
#include "utilities.h"
int main(int argc, char *argv[]) {
    if (argc >= 2) {
	BOFFILE bf = bof_read_open(argv[1]);
    } else {
	bail_with_error("Cannot read %s!", argv[1]);
    }
    return EXIT_SUCCESS;
}
