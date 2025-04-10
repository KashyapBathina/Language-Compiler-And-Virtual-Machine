/* lexer_main.c */
#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {//arg count & array of args passed
    //checks if input file is provided
    if (argc < 2) {//user did not pass input file
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1; //error
    }

    // Initialize the lexer with the input file
    lexer_init(argv[1]); //initializes lexer, adds passing input file name, then from lexer.h opens input file, sets up lexer to read

    // Run the lexer and output tokens
    lexer_output(); //lexer output scans inout file, identifies tokens based on defoned rules and print tokens recognized.

    // Check if any errors occurred
    if (lexer_has_errors()) {    //returns true if errors detected
        //fprintf(stderr, "Errors were found during lexical analysis.\n");
        return 1;
    }

    return 0;
}
