/* $Id: file_location.c,v 1.3 2024/10/06 01:07:29 leavens Exp $ */
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "file_location.h"
#include "utilities.h"

// Requires: filename != NULL
// Return a (pointer to a) fresh file_location with the given
// information
file_location *file_location_make(const char *filename,
					 unsigned int line)
{
    file_location *ret = (file_location *) malloc(sizeof(file_location));
    if (ret == NULL) {
	bail_with_error("Could not allocate space for a file_location!");
    }
    ret->filename = filename;
    ret->line = line;
    return ret;
}

// Requires: fl != NULL
// Return a (pointer to a) fresh copy of fl
file_location *file_location_copy(file_location *fl)
{
    file_location *ret = (file_location *) malloc(sizeof(file_location));
    if (ret == NULL) {
	bail_with_error("Could not allocate space for a file_location!");
    }
    ret->filename = fl->filename;
    ret->line = fl->line;
    return ret;
}
