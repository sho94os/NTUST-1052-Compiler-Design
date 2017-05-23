/*
 * symtab.h
 * Implementation of a unscoped symbol table.
 */

#include "symtab.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 32

int hash(char *string) {
    unsigned long int hash_value = 0;

    int string_length = strlen(string);
    if (string_length > SYMTAB_MAX_NAME_LENGTH) string_length = SYMTAB_MAX_NAME_LENGTH;
    for (int i = 0; i < string_length; ++i) {
        hash_value += string[i];
    }

    hash_value = hash_value % SYMTAB_HASHTAB_SIZE;

    return hash_value;
}

symtab_entry_t* get_leave_entry(symtab_entry_t *entry) {
    if (entry->next) return get_leave_entry(entry->next);
    return entry;
}

symtab_entry_t* find_through_entries_by_name(symtab_entry_t *entry, char *name) {
    if (strcmp(entry->name, name) == 0) return entry;
    if (!entry->next) return NULL;
    return find_through_entries_by_name(entry->next, name);
}

symtab_t* symtab_create() {
    symtab_t *symtab = malloc(sizeof(symtab_t));
    symtab->size = 0;
    for (int i = 0; i < SYMTAB_HASHTAB_SIZE; ++i) {
        symtab->entries[i] = NULL;
    }
    return symtab;
}

symtab_entry_t* symtab_insert(symtab_t* symtab, char* name) {
    symtab_entry_t* lookup_entry = symtab_lookup(symtab, name);
    if (lookup_entry) return lookup_entry;

    symtab_entry_t *entry = malloc(sizeof(symtab_entry_t));
    entry->next = NULL;
    entry->index = symtab->size;
    strcpy(entry->name, name);

    int hash_value = hash(name);

    if (!symtab->entries[hash_value]) {
        symtab->entries[hash_value] = entry;
    } else {
        symtab_entry_t *leave_entry = get_leave_entry(symtab->entries[hash_value]);
        leave_entry->next = entry;
    }

    symtab->size += 1;

    return entry;
}

symtab_entry_t* symtab_lookup(symtab_t* symtab, char* name) {
    int hash_value = hash(name);
    if (!symtab->entries[hash_value]) return NULL;
    symtab_entry_t *entry = symtab->entries[hash_value];
    entry = find_through_entries_by_name(entry, name);
    if (!entry) return NULL;
    return entry;
}

void insert_to_dump(symtab_entry_t *entry, char *dump) {
    char *insert_location = dump + entry->index * SYMTAB_MAX_NAME_LENGTH;
    insert_location[0] = 0;
    strcpy(insert_location, entry->name);
}

void insert_entry_chain_to_dump(symtab_entry_t *entry, char *dump) {
    insert_to_dump(entry, dump);
    if (entry->next) insert_entry_chain_to_dump(entry->next, dump);
}

char* symtab_dump(symtab_t* symtab) {
    char *dump = (char*) malloc(sizeof(char) * SYMTAB_MAX_NAME_LENGTH * symtab->size);

    for (int i = 0; i < SYMTAB_HASHTAB_SIZE; ++i) {
        symtab_entry_t *entry = symtab->entries[i];

        if (!entry) continue;
        insert_entry_chain_to_dump(entry, dump);
    }

    return dump;
}

char* symtab_dump_str(symtab_t* symtab) {
    size_t buffer_size = sizeof(char) * (SYMTAB_MAX_NAME_LENGTH + BUF_SIZE) * symtab->size;
    char *dump = symtab_dump(symtab);
    char *dump_str = (char*) malloc(buffer_size);
    int written = 0;
    dump_str[0] = 0;

    for (int i = 0; i < symtab->size; ++i) {
        char *ptr = dump + i * SYMTAB_MAX_NAME_LENGTH;
        written += snprintf(dump_str + written, buffer_size - written, "%d\t%s\n", i, ptr);
    }

    free(dump);
    return dump_str;
}
