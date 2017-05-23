/*
 * symtab.h
 * Declarations for a unscoped symbol table used by the scanner.
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#define SYMTAB_MAX_NAME_LENGTH 256
#define SYMTAB_HASHTAB_SIZE 32

/* Entry of the symbol table, which notes the name of the symbol.
   Using hash table with linked list to store entries with the same hash
   value. */
typedef struct symtab_entry_s {
    char name[SYMTAB_MAX_NAME_LENGTH];
    struct symtab_entry_s *next;
    int index;
} symtab_entry_t;

/* A symbol table, implemented using hash table. */
typedef struct symtab_s {
    symtab_entry_t *entries[SYMTAB_HASHTAB_SIZE];
    int size;
} symtab_t;

/* Functions for maintaining a symtab. */
symtab_t* symtab_create();
symtab_entry_t* symtab_insert(symtab_t*, char* name);
symtab_entry_t* symtab_lookup(symtab_t*, char* name);

/* Functions for dumping a symtab. */
char* symtab_dump(symtab_t*);
char* symtab_dump_str(symtab_t*);

#endif
