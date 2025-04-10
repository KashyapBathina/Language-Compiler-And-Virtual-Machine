/* $Id: spl_lexer_user_code.c,v 1.4 2024/10/06 18:43:01 leavens Exp leavens $ */

%%

 /* This code goes in the user code section of the spl_lexer.l file,
   following the last %% above. */

// Requires: fname != NULL
// Requires: fname is the name of a readable file
// Initialize the lexer and start it reading
// from the given file name
void lexer_init(char *fname)
{
    errors_noted = false;
    yyin = fopen(fname, "r");
    if (yyin == NULL) {
	bail_with_error("Cannot open %s", fname);
    }
    input_filename = fname;
}

// Close the file yyin
// and return 0 to indicate that there are no more files
int yywrap() {
    if (yyin != NULL) {
	int rc = fclose(yyin);
	if (rc == EOF) {
	    bail_with_error("Cannot close %s!", input_filename);
	}
    }
    input_filename = NULL;
    return 1;  /* no more input */
}

// Return the name of the current input file
const char *lexer_filename() {
    return input_filename;
}

// Return the line number of the next token
unsigned int lexer_line() {
    return yylineno;
}

/* Report an error to the user on stderr */
void yyerror(const char *filename, const char *msg)
{
    fflush(stdout);
    fprintf(stderr, "%s:%d: %s\n", input_filename, lexer_line(), msg);
    errors_noted = true;
}

// On standard output:
// Print a message about the file name of the lexer's input
// and then print a heading for the lexer's output.
void lexer_print_output_header()
{
    printf("Tokens from file %s\n", lexer_filename());
    printf("%-6s %-4s  %s\n", "Number", "Line", "Text");
}

// Have any errors been noted by the lexer?
bool lexer_has_errors()
{
    return errors_noted;
}

// Print information about the token t to stdout
// followed by a newline
void lexer_print_token(enum yytokentype t, unsigned int tline,
		       const char *txt)
{
    printf("%-6d %-4d \"%s\"\n", t, tline, txt);
}


/* Read all the tokens from the input file
 * and print each token on standard output
 * using the format in lexer_print_token */
void lexer_output()
{
    lexer_print_output_header();
    AST dummy;
    yytoken_kind_t t;
    do {
	t = yylex(&dummy);
	if (t == YYEOF) {
	    break;
        }
        lexer_print_token(t, yylineno, yytext);
    } while (t != YYEOF);
}
