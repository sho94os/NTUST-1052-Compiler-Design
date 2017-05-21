/*
 * ast.h
 * Defining a struct for node types in an abstract
 * syntax tree.
 */

#ifndef AST_H
#define AST_H

#include <stdbool.h>

#include "symbol_table.h"

/* Define node types of the abstract syntax tree. */
#define AST_NODE_TYPES(AST_NODE_TYPE)              \
        AST_NODE_TYPE(program)                     \
        AST_NODE_TYPE(function_def)                \
        AST_NODE_TYPE(function_body)               \
        AST_NODE_TYPE(expression)                  \
        AST_NODE_TYPE(string_constant)             \
        AST_NODE_TYPE(println_statement)           \
        AST_NODE_TYPE(things)                      \
        AST_NODE_TYPE(thing)
#define GENERATE_ENUM_FOR_AST_NODE_TYPES(type_name) type_name,
typedef enum ast_node_type_e {
    AST_NODE_TYPES(GENERATE_ENUM_FOR_AST_NODE_TYPES)
} ast_node_type_t;

/* Possible value types for nodes of the abstract syntax tree. */
typedef enum ast_node_value_type_e {
    symbol,   /* for identifiers */
    integer,  /* for interger constants */
    string    /* for real or string constants */
} ast_node_value_type_t;
typedef union ast_node_value_u {
    const symbol_table_entry_t  *symbol;
    int                         integer;
    const char                  *string;
} ast_node_value_t;

/* Struct and type for nodes of the abstract syntax tree.
   Using binary tree with the left-child/right-sibling representation. */
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

/* Create a AST node with a given type and the source code location. */
ast_node_t* new_ast_node(ast_node_type_t type, int line_num, int column_num);

/* Set the value for a AST node. */
void ast_node_set_value_symbol(ast_node_t*, const symbol_table_entry_t*);
void ast_node_set_value_integer(ast_node_t*, int);
void ast_node_set_value_string(ast_node_t*, const char*);

/* Insert a child for a AST node. */
void ast_node_insert_child(ast_node_t*, ast_node_t *child);

/* Get the name in a string of a AST node type. */
const char* get_ast_node_type_name(ast_node_type_t);

/* Dump all children under a AST node. */
char* ast_dump_str(ast_node_t*);
char* ast_dump_graphviz(ast_node_t*);
char* ast_dump_graphviz_with_options(ast_node_t*, bool use_mem_key);

#endif
