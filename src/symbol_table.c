#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 32

int hash(char *string) {
    unsigned long int hash_value = 0;

    int string_length = strlen(string);
    if (string_length > MAX_IDENTIFIER_LENGTH) string_length = MAX_IDENTIFIER_LENGTH;
    for (int i = 0; i < string_length; ++i) {
        hash_value += string[i];
    }

    hash_value = hash_value % SYMBOL_TABLE_SIZE;

    return hash_value;
}

symbol_table_entry_t* get_leave_entry(symbol_table_entry_t *entry) {
    if (entry->next) return get_leave_entry(entry->next);
    return entry;
}

symbol_table_entry_t* find_through_entries_by_identifier(symbol_table_entry_t *entry, char *identifier) {
    if (strcmp(entry->identifier, identifier) == 0) return entry;
    if (!entry->next) return NULL;
    return find_through_entries_by_identifier(entry->next, identifier);
}

symbol_table_t* symbol_table_create() {
    symbol_table_t *symbol_table = malloc(sizeof(symbol_table_t));
    symbol_table->size = 0;
    for (int i = 0; i < SYMBOL_TABLE_SIZE; ++i) {
        symbol_table->entries[i] = NULL;
    }
    return symbol_table;
}

symbol_table_entry_t* symbol_table_insert(symbol_table_t* symbol_table, char* identifier) {
    symbol_table_entry_t* lookup_entry = symbol_table_lookup(symbol_table, identifier);
    if (lookup_entry) return lookup_entry;

    symbol_table_entry_t *entry = malloc(sizeof(symbol_table_entry_t));
    entry->next = NULL;
    entry->index = symbol_table->size;
    strcpy(entry->identifier, identifier);

    int hash_value = hash(identifier);

    if (!symbol_table->entries[hash_value]) {
        symbol_table->entries[hash_value] = entry;
    } else {
        symbol_table_entry_t *leave_entry = get_leave_entry(symbol_table->entries[hash_value]);
        leave_entry->next = entry;
    }

    symbol_table->size += 1;

    return entry;
}

symbol_table_entry_t* symbol_table_lookup(symbol_table_t* symbol_table, char* identifier) {
    int hash_value = hash(identifier);
    if (!symbol_table->entries[hash_value]) return NULL;
    symbol_table_entry_t *entry = symbol_table->entries[hash_value];
    entry = find_through_entries_by_identifier(entry, identifier);
    if (!entry) return NULL;
    return entry;
}

void insert_to_dump(symbol_table_entry_t *entry, char *dump) {
    char *insert_location = dump + entry->index * MAX_IDENTIFIER_LENGTH;
    insert_location[0] = 0;
    strcpy(insert_location, entry->identifier);
}

void insert_entry_chain_to_dump(symbol_table_entry_t *entry, char *dump) {
    insert_to_dump(entry, dump);
    if (entry->next) insert_entry_chain_to_dump(entry->next, dump);
}

char* symbol_table_dump(symbol_table_t* symbol_table) {
    char *dump = (char*) malloc(sizeof(char) * MAX_IDENTIFIER_LENGTH * symbol_table->size);

    for (int i = 0; i < SYMBOL_TABLE_SIZE; ++i) {
        symbol_table_entry_t *entry = symbol_table->entries[i];

        if (!entry) continue;
        insert_entry_chain_to_dump(entry, dump);
    }

    return dump;
}


char* symbol_table_dump_str(symbol_table_t* symbol_table) {
    size_t buffer_size = sizeof(char) * (MAX_IDENTIFIER_LENGTH + BUF_SIZE) * symbol_table->size;
    char *dump = symbol_table_dump(symbol_table);
    char *dump_str = (char*) malloc(buffer_size);
    int written = 0;
    dump_str[0] = 0;

    for (int i = 0; i < symbol_table->size; ++i) {
        char *ptr = dump + i * MAX_IDENTIFIER_LENGTH;
        written += snprintf(dump_str + written, buffer_size - written, "%d\t%s\n", i, ptr);
    }

    free(dump);
    return dump_str;
}
