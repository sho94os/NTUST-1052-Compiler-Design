/*
 * idtab.c
 * Implementation for the symbol (identifier) table.
 */

#include "idtab.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 32

/* Hash function for the hash table */
int idtab_hash(char *string) {
    unsigned long int hash_value = 0;

    int string_length = strlen(string);
    if (string_length > IDTAB_MAX_IDENTIFIER_LENGTH) string_length = IDTAB_MAX_IDENTIFIER_LENGTH;
    for (int i = 0; i < string_length; ++i) {
        hash_value += string[i];
    }

    hash_value = hash_value % IDTAB_HASHTAB_SIZE;

    return hash_value;
}

idtab_entry_t* idtab_get_leave_entry(idtab_entry_t *entry) {
    if (entry->next) return idtab_get_leave_entry(entry->next);
    return entry;
}

idtab_entry_t* find_through_entries_by_identifier(idtab_entry_t *entry, char *identifier) {
    if (strcmp(entry->identifier, identifier) == 0) return entry;
    if (!entry->next) return NULL;
    return find_through_entries_by_identifier(entry->next, identifier);
}

idtab_t* idtab_create() {
    idtab_t *idtab = malloc(sizeof(idtab_t));
    idtab->scope = NULL;
    idtab->upper_idtab = NULL;
    for (int i = 0; i < IDTAB_HASHTAB_SIZE; ++i) {
        idtab->entries[i] = NULL;
    }
    idtab->size = 0;
    return idtab;
}

idtab_t* idtab_entry_idtab_create(idtab_t* idtab, idtab_entry_t* entry) {
    idtab_t *scoped_idtab = idtab_create();
    scoped_idtab->scope = entry;
    scoped_idtab->upper_idtab = idtab;
    entry->scoped_idtab = scoped_idtab;
    return scoped_idtab;
}

idtab_entry_t* idtab_insert(idtab_t* idtab, idtab_entry_type_t type, char* identifier, idtab_entry_value_type_t value_type) {
    // TODO: Check if there an entry with the same identifier

    idtab_entry_t *entry = malloc(sizeof(idtab_entry_t));
    entry->idtab = idtab;
    entry->next = NULL;
    entry->type = type;
    entry->value_type = value_type;
    strcpy(entry->identifier, identifier);
    entry->serial = idtab->size++;

    int hash_value = idtab_hash(identifier);

    if (!idtab->entries[hash_value]) {
        idtab->entries[hash_value] = entry;
    } else {
        idtab_entry_t *leave_entry = idtab_get_leave_entry(idtab->entries[hash_value]);
        leave_entry->next = entry;
    }

    return entry;
}

idtab_entry_t* idtab_lookup(idtab_t* idtab, char* identifier) {
    int hash_value = idtab_hash(identifier);

    if (!idtab->entries[hash_value]) {
        if (idtab->upper_idtab) return idtab_lookup(idtab->upper_idtab, identifier);
        else return NULL;
    }

    idtab_entry_t *entry = idtab->entries[hash_value];
    entry = find_through_entries_by_identifier(entry, identifier);

    if (!entry) {
        if (idtab->upper_idtab) return idtab_lookup(idtab->upper_idtab, identifier);
        else return NULL;
    }

    return entry;
}

// Warning: Ugly code below.

#define IDTAB_DUMP_SIZE 100000

int add_entry_to_dump(idtab_entry_t *entry, char *str, int written, int level, bool dump_mem_loc);

int add_entry_chain_to_dump(idtab_entry_t *entry, char *str, int written, int level, bool dump_mem_loc) {
    written = add_entry_to_dump(entry, str, written, level, dump_mem_loc);
    if (entry->next) {
        return add_entry_chain_to_dump(entry->next, str, written, level, dump_mem_loc);
    } else {
        return written;
    }
}

int dump_idtab_to_str(idtab_t *idtab, char *str, int written, int level, bool dump_mem_loc) {
    written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "{\n");

    for (int i = 0; i < IDTAB_HASHTAB_SIZE; ++i) {
        idtab_entry_t *entry = idtab->entries[i];

        if (!entry) continue;
        written = add_entry_chain_to_dump(entry, str, written, level, dump_mem_loc);
    }

    if (str[written - 1] == '\n' && str[written - 2] == '{') {
        str[written - 1] = 0;
        --written;
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "}");
        return written;
    }

    if (level == 0) {
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "\n}\n");
    } else {
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "\n%*c}", level * 2, ' ');
    }

    return written;
}

int add_entry_to_dump(idtab_entry_t *entry, char *str, int written, int level, bool dump_mem_loc) {
    if (str[written - 1] == '}') {
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n");
    }

    if (dump_mem_loc) {
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "%*c\"%s(%p)\": {", level * 2 + 2, ' ', entry->identifier, entry);
    } else {
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "%*c\"%s\": {", level * 2 + 2, ' ', entry->identifier);
    }

    switch (entry->type) {
        case function_identifier_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "\n%*c\"type\": \"%s\"", level * 2 + 4, ' ', "function");
            break;
        case variable_identifier_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "\n%*c\"type\": \"%s\"", level * 2 + 4, ' ', "variable");
            break;
        case constant_identifier_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "\n%*c\"type\": \"%s\"", level * 2 + 4, ' ', "constant");
            break;
    }

    switch (entry->value_type) {
        case void_value_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"value_type\": \"%s\"", level * 2 + 4, ' ', "void");
            break;
        case bool_value_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"value_type\": \"%s\"", level * 2 + 4, ' ', "bool");
            break;
        case int_value_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"value_type\": \"%s\"", level * 2 + 4, ' ', "int");
            break;
        case real_value_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"value_type\": \"%s\"", level * 2 + 4, ' ', "real");
            break;
        case string_value_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"value_type\": \"%s\"", level * 2 + 4, ' ', "string");
            break;
        case unknown_value_type:
            written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"value_type\": \"%s\"", level * 2 + 4, ' ', "unknown");
            break;
    }

    if (entry->scoped_idtab) {
        written += snprintf(str + written, IDTAB_DUMP_SIZE - written, ",\n%*c\"scoped_identifiers\": ", level * 2 + 4, ' ');
        written = dump_idtab_to_str(entry->scoped_idtab, str, written, level + 2, dump_mem_loc);
    }

    written += snprintf(str + written, IDTAB_DUMP_SIZE - written, "\n%*c}", level * 2 + 2, ' ');

    return written;
}

char* idtab_dump_str(idtab_t* idtab) {
    return idtab_dump_str_with_options(idtab, false, 0);
}

char* idtab_dump_str_with_options(idtab_t* idtab, bool dump_mem_loc, int initial_level) {
    char *dump_str = (char*) malloc(IDTAB_DUMP_SIZE);
    dump_str[0] = 0;

    dump_idtab_to_str(idtab, dump_str, 0, initial_level, dump_mem_loc);

    return dump_str;
}
