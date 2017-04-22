#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_IDENTIFIER_LENGTH 256
#define SYMBOL_TABLE_SIZE 32

typedef struct symbol_table_entry_s {
    char identifier[MAX_IDENTIFIER_LENGTH];
    int index;
    struct symbol_table_entry_s *next;
} symbol_table_entry_t;

typedef struct symbol_table_s {
    symbol_table_entry_t *entries[SYMBOL_TABLE_SIZE];
    int size;
} symbol_table_t;

symbol_table_t* symbol_table_create();
int symbol_table_insert(symbol_table_t*, char* identifier);
int symbol_table_lookup(symbol_table_t*, char* identifier);
char* symbol_table_dump(symbol_table_t*);
char* symbol_table_dump_str(symbol_table_t*);

#endif
