/* $Id: id_attrs.h,v 1.6 2023/10/15 12:32:59 leavens Exp $ */
#ifndef _ID_ATTRS_H
#define _ID_ATTRS_H
#include "file_location.h"

// kinds of entries in the symbol table
typedef enum {constant_idk, variable_idk, procedure_idk} id_kind;

// attributes of identifiers in the symbol table
typedef struct {
    // file_loc is the source file location of the identifier's declaration
    file_location file_loc;
    id_kind kind;  // kind of identifier
    // offset_count is the number of constant or variable decls before this one
    // in this scope
    unsigned int offset_count;
} id_attrs;

// Return a freshly allocated id_attrs struct
// with its field file_loc set to floc, kind set to k, 
// and its offset_count set to ofst_cnt.
// If there is no space, bail with an error message,
// so this should never return NULL.
extern id_attrs *create_id_attrs(file_location floc, id_kind k,
				 unsigned int ofst_cnt);

// Return a lowercase version of the kind's name as a string
// (i.e. if k == variable_idk, return "variable"
//       else if k == constant_idk, return "constant",
//       else if k == procedure_idk, return "procedure")
extern const char *kind2str(id_kind k);
#endif
