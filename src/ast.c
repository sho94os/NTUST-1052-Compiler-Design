/*
 * ast.c
 * Functions for maintaining a abstract syntax tree.
 */

#include "ast.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokens.h"

ast_node_t* new_ast_node(ast_node_type_t type, int line_num, int column_num) {
    ast_node_t *ast_node = malloc(sizeof(ast_node_t));
    ast_node->type = type;
    ast_node->has_value = false;
    ast_node->child = NULL;
    ast_node->sibling = NULL;
    ast_node->source_line_num = line_num;
    ast_node->source_column_num = column_num;

    return ast_node;
}

void ast_node_set_value_identifier(ast_node_t *ast_node, const idtab_entry_t *idtab_entry) {
    ast_node->has_value = true;
    ast_node->value_type = identifier;
    ast_node->value.identifier = idtab_entry;
}

void ast_node_set_value_operatr(ast_node_t *ast_node, int value) {
    ast_node->has_value = true;
    ast_node->value_type = operatr;
    ast_node->value.operatr = value;
}

void ast_node_set_value_integer(ast_node_t *ast_node, int value) {
    ast_node->has_value = true;
    ast_node->value_type = integer;
    ast_node->value.integer = value;
}

void ast_node_set_value_string(ast_node_t *ast_node, const char* value) {
    char *stored_value = malloc(strlen(value) + 1);
    strcpy(stored_value, value);
    ast_node->has_value = true;
    ast_node->value_type = string;
    ast_node->value.string = stored_value;
}

ast_node_t* find_last_sibling(ast_node_t *node) {
    if (!node->sibling) return node;
    return find_last_sibling(node->sibling);
}

void ast_node_insert_child(ast_node_t *node, ast_node_t *child) {
    if (!node->child) {
        node->child = child;
    } else {
        ast_node_insert_sibling(node->child, child);
    }
}

void ast_node_insert_sibling(ast_node_t *node, ast_node_t *sibling) {
    if (!node->sibling) {
        node->sibling = sibling;
    } else {
        ast_node_t *last_sibling = find_last_sibling(node->sibling);
        last_sibling->sibling = sibling;
    }
}

ast_node_t* ast_node_get_child(ast_node_t* ast_node, int n) {
    ast_node_t* child = ast_node->child;

    while (n > 1) {
        child = child->sibling;
        --n;
    }

    return child;
}

#define GENERATE_CASE_FOR_AST_NODE_TYPE_NAMES(type_name) case type_name: return #type_name + 4; break;

const char* get_ast_node_type_name(ast_node_type_t type) {
    switch (type) {
        AST_NODE_TYPES(GENERATE_CASE_FOR_AST_NODE_TYPE_NAMES)
    }
}

#define GENERATE_CASE_FOR_AST_NODE_OPERATR_VALUES(value) case value: return #value + 8; break;

const char* get_ast_node_operatr_value_name(ast_operatr_value_t value) {
    switch (value) {
        AST_NODE_OPERATR_VALUES(GENERATE_CASE_FOR_AST_NODE_OPERATR_VALUES)
    }
}

// Warning: Ugly code below.

#define AST_DUMP_SIZE 100000

int dump_ast_node_to_str(ast_node_t *ast_node, char *str, int written, int level) {
    if (level == 0) {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "{\n");
    } else {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "%*c{\n", level * 2, ' ');
    }

    written += snprintf(str + written, AST_DUMP_SIZE - written, "%*c\"type\": \"%s\"", level * 2 + 2, ' ', get_ast_node_type_name(ast_node->type));

    if (ast_node->has_value) {
        switch (ast_node->value_type) {
            case operatr:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": \"%s\"", level * 2 + 2, ' ', get_ast_node_operatr_value_name(ast_node->value.operatr));
                break;
            case identifier:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": \"%s(%p)\"", level * 2 + 2, ' ', ast_node->value.identifier->identifier, ast_node->value.identifier);
                break;
            case integer:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": %d", level * 2 + 2, ' ', ast_node->value.integer);
                break;
            case string:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": \"%s\"", level * 2 + 2, ' ', ast_node->value.string);
                break;
        }
    }

    if (ast_node->child) {
        written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"children\": [\n", level * 2 + 2, ' ');
        ast_node_t *current_child = ast_node->child;

        while (current_child) {
            if (current_child != ast_node->child) written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n");
            written = dump_ast_node_to_str(current_child, str, written, level + 2);
            current_child = current_child->sibling;
        }

        written += snprintf(str + written, AST_DUMP_SIZE - written, "\n%*c]", level * 2 + 2, ' ');
    }

    if (level == 0) {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "\n}\n");
    } else {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "\n%*c}", level * 2, ' ');
    }

    return written;
}

char* ast_dump_str(ast_node_t* ast) {
    return ast_dump_str_with_options(ast, 0);
}

char* ast_dump_str_with_options(ast_node_t* ast, int initial_level) {
    char *dump_str = (char*) malloc(AST_DUMP_SIZE);
    dump_str[0] = 0;

    dump_ast_node_to_str(ast, dump_str, 0, initial_level);

    return dump_str;
}

int list_graphviz_node(ast_node_t *ast_node, char *str, int written, bool use_mem_key) {
    if (!use_mem_key)
        written += snprintf(str + written, AST_DUMP_SIZE - written, "    %sl%dc%d [label=\"%s", get_ast_node_type_name(ast_node->type), ast_node->source_line_num, ast_node->source_column_num, get_ast_node_type_name(ast_node->type));
    else
        written += snprintf(str + written, AST_DUMP_SIZE - written, "    %sl%dc%dm%d [label=\"%s", get_ast_node_type_name(ast_node->type), ast_node->source_line_num, ast_node->source_column_num, abs((int)ast_node), get_ast_node_type_name(ast_node->type));

    if (ast_node->has_value) {
        switch (ast_node->value_type) {
            case operatr:
                written += snprintf(str + written, AST_DUMP_SIZE - written, "\\n%s", get_ast_node_operatr_value_name(ast_node->value.operatr));
                break;
            case identifier:
                written += snprintf(str + written, AST_DUMP_SIZE - written, "\\n%s(%p)", ast_node->value.identifier->identifier, ast_node->value.identifier);
                break;
            case integer:
                written += snprintf(str + written, AST_DUMP_SIZE - written, "\\n%d", ast_node->value.integer);
                break;
            case string:
                written += snprintf(str + written, AST_DUMP_SIZE - written, "\\n\\\"%s\\\"", ast_node->value.string);
                break;
        }
    }

    written += snprintf(str + written, AST_DUMP_SIZE - written, "\"]\n");

    if (ast_node->child) written = list_graphviz_node(ast_node->child, str, written, use_mem_key);
    if (ast_node->sibling) written = list_graphviz_node(ast_node->sibling, str, written, use_mem_key);

    return written;
}

int list_graphviz_node_children(ast_node_t *ast_node, char *str, int written, bool use_mem_key) {
    if (ast_node->child) {
        if (!use_mem_key)
            written += snprintf(str + written, AST_DUMP_SIZE - written, "    %sl%dc%d->{ ", get_ast_node_type_name(ast_node->type), ast_node->source_line_num, ast_node->source_column_num);
        else
            written += snprintf(str + written, AST_DUMP_SIZE - written, "    %sl%dc%dm%d->{ ", get_ast_node_type_name(ast_node->type), ast_node->source_line_num, ast_node->source_column_num, abs((int)ast_node));

        ast_node_t *current_child = ast_node->child;

        while (current_child) {
            if (!use_mem_key)
                written += snprintf(str + written, AST_DUMP_SIZE - written, "%sl%dc%d ", get_ast_node_type_name(current_child->type), current_child->source_line_num, current_child->source_column_num);
            else
                written += snprintf(str + written, AST_DUMP_SIZE - written, "%sl%dc%dm%d ", get_ast_node_type_name(current_child->type), current_child->source_line_num, current_child->source_column_num, abs((int)current_child));
            current_child = current_child->sibling;
        }

        written += snprintf(str + written, AST_DUMP_SIZE - written, "}\n");
    }

    if (ast_node->child) written = list_graphviz_node_children(ast_node->child, str, written, use_mem_key);
    if (ast_node->sibling) written = list_graphviz_node_children(ast_node->sibling, str, written, use_mem_key);

    return written;
}

char* ast_dump_graphviz_with_options(ast_node_t* ast, bool use_mem_key) {
    char *dump = (char*) malloc(AST_DUMP_SIZE);
    dump[0] = 0;
    int written = 0;

    written += snprintf(dump + written, AST_DUMP_SIZE - written, "digraph ast {\n");

    written = list_graphviz_node(ast, dump, written, use_mem_key);
    written += snprintf(dump + written, AST_DUMP_SIZE - written, "\n");
    written = list_graphviz_node_children(ast, dump, written, use_mem_key);

    written += snprintf(dump + written, AST_DUMP_SIZE - written, "}\n");

    return dump;
}

char* ast_dump_graphviz(ast_node_t* ast) {
    return ast_dump_graphviz_with_options(ast, true);
}
