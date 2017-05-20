#include "ast.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define AST_DUMP_SIZE 100000

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

void ast_node_set_value_symbol(ast_node_t *ast_node, const symbol_table_entry_t *symbol_table_entry) {
    ast_node->has_value = true;
    ast_node->value_type = symbol;
    ast_node->value.symbol = symbol_table_entry;
}

void ast_node_set_value_integer(ast_node_t *ast_node, int value) {
    ast_node->has_value = true;
    ast_node->value_type = integer;
    ast_node->value.integer = value;
}

void ast_node_set_value_string(ast_node_t *ast_node, const char* value) {
    ast_node->has_value = true;
    ast_node->value_type = string;
    ast_node->value.string = value;
}

ast_node_t* find_last_sibling(ast_node_t *node) {
    if (!node->sibling) return node;
    return find_last_sibling(node->sibling);
}

void ast_node_insert_child(ast_node_t *node, ast_node_t *child) {
    if (!node->child) {
        node->child = child;
    } else {
        ast_node_t *last_child_sibling = find_last_sibling(node->child);
        last_child_sibling->sibling = child;
    }
}

const char* get_ast_node_type_name(ast_node_type_t type) {
    switch (type) {
        case program:
            return "program";
            break;
        case function_def:
            return "function_def";
            break;
        case function_body:
            return "function_body";
            break;
        case expression:
            return "expression";
            break;
        case string_constant:
            return "string_constant";
            break;
        case println_statement:
            return "println_statement";
            break;
        case things:
            return "things";
            break;
        case thing:
            return "thing";
            break;
    }
}

int dump_ast_node_to_str(ast_node_t *ast_node, char *str, int written, int level) {
    if (level == 0) {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "{\n");
    } else {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "%*c{\n", level * 4, ' ');
    }

    written += snprintf(str + written, AST_DUMP_SIZE - written, "%*c\"type\": \"%s\"", level * 4 + 2, ' ', get_ast_node_type_name(ast_node->type));

    if (ast_node->has_value) {
        switch (ast_node->value_type) {
            case symbol:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": \"%s(%p)\"", level * 4 + 2, ' ', ast_node->value.symbol->identifier, ast_node->value.symbol);
                break;
            case integer:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": %d", level * 4 + 2, ' ', ast_node->value.integer);
                break;
            case string:
                written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"value\": \"%s\"", level * 4 + 2, ' ', ast_node->value.string);
                break;
        }
    }

    if (ast_node->child) {
        written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n%*c\"children\": [\n", level * 4 + 2, ' ');
        ast_node_t *current_child = ast_node->child;

        while (current_child) {
            if (current_child != ast_node->child) written += snprintf(str + written, AST_DUMP_SIZE - written, ",\n");
            written = dump_ast_node_to_str(current_child, str, written, level + 1);
            current_child = current_child->sibling;
        }

        written += snprintf(str + written, AST_DUMP_SIZE - written, "\n%*c]", level * 4 + 2, ' ');
    }

    if (level == 0) {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "\n}\n");
    } else {
        written += snprintf(str + written, AST_DUMP_SIZE - written, "\n%*c}", level * 4, ' ');
    }

    return written;
}

char* ast_dump_str(ast_node_t* ast) {
    char *dump_str = (char*) malloc(AST_DUMP_SIZE);
    dump_str[0] = 0;

    dump_ast_node_to_str(ast, dump_str, 0, 0);

    return dump_str;
}

int list_graphviz_node(ast_node_t *ast_node, char *str, int written, bool use_mem_key) {
    if (!use_mem_key)
        written += snprintf(str + written, AST_DUMP_SIZE - written, "    %sl%dc%d [label=\"%s", get_ast_node_type_name(ast_node->type), ast_node->source_line_num, ast_node->source_column_num, get_ast_node_type_name(ast_node->type));
    else
        written += snprintf(str + written, AST_DUMP_SIZE - written, "    %sl%dc%dm%d [label=\"%s", get_ast_node_type_name(ast_node->type), ast_node->source_line_num, ast_node->source_column_num, abs((int)ast_node), get_ast_node_type_name(ast_node->type));

    if (ast_node->has_value) {
        switch (ast_node->value_type) {
            case symbol:
                written += snprintf(str + written, AST_DUMP_SIZE - written, "\\n%s(%p)", ast_node->value.symbol->identifier, ast_node->value.symbol);
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
