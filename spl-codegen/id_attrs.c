/* $Id: id_attrs.c,v 1.10 2023/11/17 21:56:45 leavens Exp $ */
// Attributes of identifiers in the symbol table
#include <stdlib.h>
#include <stddef.h>
#include "utilities.h"
#include "id_attrs.h"

// Return a freshly allocated id_attrs struct
// with its field file_loc set to floc, kind set to k, 
// and its offset_count set to ofst_cnt.
// If there is no space, bail with an error message,
// so this should never return NULL.
id_attrs *id_attrs_create(file_location floc, id_kind k,
				 unsigned int ofst_cnt)
{
    id_attrs *ret = (id_attrs *)malloc(sizeof(id_attrs));
    if (ret == NULL) {
	bail_with_error("No space to allocate id_attrs!");
    }
    ret->file_loc = floc;
    ret->kind = k;
    ret->offset_count = ofst_cnt;
    return ret;
}

// Return a freshly allocated id_attrs struct for a procedure
// declared at floc.
// If there is no space, bail with an error message,
// so this should never return NULL.
extern id_attrs *id_attrs_proc_create(file_location floc)
{
    id_attrs *ret = (id_attrs *)malloc(sizeof(id_attrs));
    if (ret == NULL) {
	bail_with_error("No space to allocate id_attrs!");
    }
    ret->file_loc = floc;
    ret->kind = procedure_idk;
    return ret;
}


// Return a lowercase version of the kind's name as a string
// (i.e. if k == variable_idk, return "variable"
//       else if k == constant_idk, return "constant",
//       else if k == procedure_idk, return "procedure")
const char *id_attrs_id_kind_string(id_kind k)
{
    static const char *kind_names[3] = {"constant", "variable", "procedure"};
    return kind_names[k];
}
