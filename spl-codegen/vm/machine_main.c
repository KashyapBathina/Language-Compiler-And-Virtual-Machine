/* $Id: machine_main.c,v 1.6 2024/11/10 13:22:31 leavens Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bof.h"
#include "machine.h"
#include "utilities.h"

/* Print a usage message on stderr and exit with exit code 1. */
static void usage(const char *cmdname)
{
    bail_with_error(
		    "Usage: %s [-p] file.bof\n        %s [-t] file.bof",
		    cmdname, cmdname);
}

// Run the VM on the .bof file name given in argv[1]
int main(int argc, char *argv[])
{
    const char *cmdname = argv[0];
    argc--;
    argv++;

    bool print_program = false;
    bool trace_execution = false;
    if (argc == 2 && strcmp(argv[0], "-p") == 0) {
	print_program = true;
	argc--;
	argv++;
    } else if (argc == 2 && strcmp(argv[0], "-t") == 0) {
	trace_execution = true;
	argc--;
	argv++;
    }

    // now there should be exactly 1 file argument
    if (argc != 1 || argv[0][0] == '-') {
	usage(cmdname);
    }

    char *suffix = strchr(argv[0], '.');
    if (suffix == NULL || strncmp(suffix, ".bof", 4) != 0) {
	usage(cmdname);
    }

    BOFFILE bf = bof_read_open(argv[0]);

    machine_load(bf);

    // if printing, don't run the program
    if (print_program) {
	machine_print_loaded_program(stdout);
	return EXIT_SUCCESS;
    }
    
    machine_run(trace_execution);

    // the following should never execute,
    // as the exit system call will call exit(0),
    // and if the machine goes into an infinite loop it never gets here!
    return EXIT_SUCCESS;
}
