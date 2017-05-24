/*
 * idtab.h
 * Declarations for the symbol (identifier) table.
 */

#ifndef IDTAB_H
#define IDTAB_H

#define IDTAB_MAX_IDENTIFIER_LENGTH 256
#define IDTAB_HASHTAB_SIZE 32

/* Type of the identifier. */
typedef enum idtab_entry_identifier_type_e {
    function_identifier_type,
    variable_identifier_type,
    constant_identifier_type
} idtab_entry_type_t;

/* Constant, variable or function return type. */
typedef enum idtab_entry_value_type_e {
    bool_value_type,
    int_value_type,
    real_value_type,
    string_value_type
} idtab_entry_value_type_t;

/* Entry of the symbol table, which notes the info of a identifier.
   Using hash table with linked list to store entries with the same hash
   value. */
typedef struct idtab_entry_s {
    /* The table this entry is on */
    struct idtab_s *idtab;
    /* Identifier name, type and representing value type */
    char identifier[IDTAB_MAX_IDENTIFIER_LENGTH];
    idtab_entry_type_t type;
    idtab_entry_value_type_t value_type;
    /* The symbol table of identifiers that is scoped under this identifier */
    struct idtab_s *scoped_idtab;
    /* Link to the next entry with the same hash value */
    struct idtab_entry_s *next;
} idtab_entry_t;

/* A symbol table, implemented using hash table. */
typedef struct idtab_s {
    /* Hash table of entries */
    idtab_entry_t *entries[IDTAB_HASHTAB_SIZE];
    /* The scope of this symbol table */
    struct idtab_entry_s *scope;
    /* The symbol table of the upper scope */
    struct idtab_s *upper_idtab;
} idtab_t;

/* Create a new, top-scope idtab. */
idtab_t* idtab_create();

/* Create a scoped idtab for an identifier. */
idtab_t* idtab_entry_idtab_create(idtab_t*, idtab_entry_t*);

/* Insert entry into an idtab. */
idtab_entry_t* idtab_insert(idtab_t*, idtab_entry_type_t, char* identifier, idtab_entry_value_type_t);

/* Lookup entry by identifier of an idtab (and all upper-scope idtabs). */
idtab_entry_t* idtab_lookup(idtab_t*, char* identifier);

/* Dump an idtab for debugging */
char* idtab_dump_str(idtab_t*);
char* idtab_dump_str_with_options(idtab_t*, int initial_level);

#endif
