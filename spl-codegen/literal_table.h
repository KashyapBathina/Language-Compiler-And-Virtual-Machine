// $Id: literal_table.h,v 1.2 2023/11/13 12:45:52 leavens Exp $
#ifndef _LITERAL_TABLE_H
#define _LITERAL_TABLE_H
#include <stdbool.h>
#include "machine_types.h"

// Return the size (in words/entries) in the literal table
extern unsigned int literal_table_size();

// is the literal_table empty?
extern bool literal_table_empty();

// is the literal_table full?
extern bool literal_table_full();

// initialize the literal_table
extern void literal_table_initialize();

// Return the offset of sought if it is in the table,
// otherwise return -1.
extern int literal_table_find_offset(const char *sought, word_type value);

// Return true just when sought is in the table
extern bool literal_table_present(const char *sought, word_type value);

// Return the word offset for val_string/value
// entering it in the table if it's not already present
extern unsigned int literal_table_lookup(const char *val_string, word_type value);

// === iteration helpers ===

// Start an iteration over the literal table
// which can extract the elements
extern void literal_table_start_iteration();

// End the current iteration over the literal table.
extern void literal_table_end_iteration();

// Is there another float in the literal table?
extern bool literal_table_iteration_has_next();

// Return the next word_type in the literal table
// and advance the iteration
extern word_type literal_table_iteration_next();

#endif