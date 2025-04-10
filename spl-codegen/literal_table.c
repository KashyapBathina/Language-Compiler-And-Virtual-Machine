#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "literal_table.h"
#include "utilities.h"

// constant table entries
typedef struct literal_table_entry_s {
    struct literal_table_entry_s *next;
    const char *text;
    word_type value;
    unsigned int offset;
} literal_table_entry_t;


static literal_table_entry_t *first;
static literal_table_entry_t *last;
static unsigned int next_word_offset;
static bool iterating;
static literal_table_entry_t *iteration_next;

// Check the invariant
static void literal_table_okay()
{
    bool emp = literal_table_empty();
    assert(emp == (next_word_offset == 0));
    assert(emp == (first == NULL));
    assert(emp == (last == NULL));
}

// Return the size (in words/entries) in the literal table
unsigned int literal_table_size()
{
    return next_word_offset;
}

// is the literal_table empty?
bool literal_table_empty()
{
    return next_word_offset == 0;
}

// is the literal_table full?
bool literal_table_full()
{
    return false;
}

// Initialize the literal table
void literal_table_initialize(void) {
    first = NULL;
    last = NULL;
    next_word_offset = 0;
    literal_table_okay();
    iterating = false;
    iteration_next = NULL;
    literal_table_okay();
}

// Requires: sought is the print form of value
// return the offset of sought/value if it is in the table
// otherwise return -1.
int literal_table_find_offset(const char *sought, word_type value)
{
    literal_table_okay();
    literal_table_entry_t *entry = first;
    while (entry != NULL) {
	if (strcmp(entry->text, sought) == 0) {
	    return entry->offset;
	}
	entry = entry->next;
    }
    return -1;
}

// Requires: sought is the print form of value
// Return true just when sought is in the table
bool literal_table_present(const char *sought, word_type value) {
    literal_table_okay();
    return literal_table_find_offset(sought, value) >= 0;
}


// Return the word offset for val_string/value
// entering it in the table if it's not already present
unsigned int literal_table_lookup(const char *val_string, word_type value) {
    int ret = literal_table_find_offset(val_string, value);
    if (ret >= 0) {
    	  return ret; // don't insert if it's already present
    }
    
    // it's not already present, so insert it
    literal_table_entry_t *new_entry = (literal_table_entry_t *) malloc(sizeof(literal_table_entry_t));
    new_entry->text = val_string;
    new_entry->value = value;
    new_entry->next = NULL;
    ret = next_word_offset;
    new_entry->offset = next_word_offset++;
    
    if (new_entry == NULL) {
	      bail_with_error("No space to allocate new literal table entry!");
    }
    if (first == NULL) {
    	first = new_entry;
    	last = new_entry;
    } else {
    	last->next = new_entry;
    	last = new_entry;
    }
    literal_table_okay();
    return ret;
}

// Start an iteration over the literal table
// which can extract the elements
void literal_table_start_iteration() {
    if (iterating) {
        bail_with_error("Attempt to start literal_table iterating when already iterating!");
    }
    literal_table_okay();
    iterating = true;
    iteration_next = first;
}


// End the current iteration over the literal table.
void literal_table_end_iteration() {
    iterating = false;
}

// Is there another float in the literal table?
bool literal_table_iteration_has_next() {
    literal_table_okay();
    bool ret = (iteration_next != NULL);
    if (!ret) iterating = false;
    return ret;
}

// Return the next float in the literal table
// and advance the iteration
word_type literal_table_iteration_next() {
    assert(iteration_next != NULL);
    word_type ret = iteration_next->value;
    iteration_next = iteration_next->next;
    return ret;
}