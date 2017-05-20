#ifndef AST_H
#define AST_H

#include <stdbool.h>

#include "symbol_table.h"

typedef enum ast_node_type_e {
    program,
    function_def,
    function_body,
    expression,
    string_constant,
    println_statement,
    things,
    thing
} ast_node_type_t;

typedef enum ast_node_value_type_e {
    symbol,
    integer,
    string
} ast_node_value_type_t;

typedef union ast_node_value_u {
    const symbol_table_entry_t *symbol;
    int integer;
    const char *string;
} ast_node_value_t;

typedef struct ast_node_s {
    // Node type
    ast_node_type_t type;
    // Child and sibling
    struct ast_node_s *child, *sibling;
    // Const value, variable name or operation
    bool has_value;
    ast_node_value_type_t value_type;
    ast_node_value_t value;
    // Source map
    int source_line_num;
    int source_column_num;
} ast_node_t;

ast_node_t* new_ast_node(ast_node_type_t type, int line_num, int column_num);
void ast_node_set_value_symbol(ast_node_t*, const symbol_table_entry_t*);
void ast_node_set_value_integer(ast_node_t*, int);
void ast_node_set_value_string(ast_node_t*, const char*);
void ast_node_insert_child(ast_node_t*, ast_node_t *child);

char* ast_dump_str(ast_node_t*);
char* ast_dump_graphviz(ast_node_t*);
char* ast_dump_graphviz_with_options(ast_node_t*, bool use_mem_key);

#endif
