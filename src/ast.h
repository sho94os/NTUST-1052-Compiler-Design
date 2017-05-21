/*
 * ast.h
 * Defining a struct for nodes in an abstract syntax tree.
 */

#ifndef AST_H
#define AST_H

#include <stdbool.h>

#include "symbol_table.h"

/* Define node types of the abstract syntax tree. */
#define AST_NODE_TYPES(AST_NODE_TYPE)              \
        AST_NODE_TYPE(ast_program)                 \
        AST_NODE_TYPE(ast_func_def)                \
        AST_NODE_TYPE(ast_func_args)               \
        AST_NODE_TYPE(ast_func_arg)                \
        AST_NODE_TYPE(ast_func_body)               \
        AST_NODE_TYPE(ast_var_dec)                 \
        AST_NODE_TYPE(ast_const_dec)               \
        AST_NODE_TYPE(ast_id)                      \
        AST_NODE_TYPE(ast_assign)                  \
        AST_NODE_TYPE(ast_func_invo)               \
        AST_NODE_TYPE(ast_func_invo_args)          \
        AST_NODE_TYPE(ast_array_assign)            \
        AST_NODE_TYPE(ast_print)                   \
        AST_NODE_TYPE(ast_println)                 \
        AST_NODE_TYPE(ast_read)                    \
        AST_NODE_TYPE(ast_return)                  \
        AST_NODE_TYPE(ast_operation)               \
        AST_NODE_TYPE(ast_condition)               \
        AST_NODE_TYPE(ast_block)                   \
        AST_NODE_TYPE(ast_integer)                 \
        AST_NODE_TYPE(ast_real)                    \
        AST_NODE_TYPE(ast_string)                  \
        AST_NODE_TYPE(ast_things)                  \
        AST_NODE_TYPE(ast_thing)
#define GENERATE_ENUM_FOR_AST_NODE_TYPES(type_name) type_name,
typedef enum ast_node_type_e {
    AST_NODE_TYPES(GENERATE_ENUM_FOR_AST_NODE_TYPES)
} ast_node_type_t;

/* Possible value types for nodes of the abstract syntax tree. */
typedef enum ast_node_value_type_e {
    symbol,   /* for ids */
    operatr,  /* for operations */
    integer,  /* for interger literals */
    string    /* for real or string literals */
} ast_node_value_type_t;
typedef union ast_node_value_u {
    const symbol_table_entry_t  *symbol;
    int                         operatr;
    int                         integer;
    const char                  *string;
} ast_node_value_t;

/* Struct and type for nodes of the abstract syntax tree.
   Using binary tree with the left-child/right-sibling representation. */
typedef struct ast_node_s {
    /* Node type */
    ast_node_type_t type;
    /* Child and sibling */
    struct ast_node_s *child, *sibling;
    /* Const value, variable name or operation */
    bool has_value;
    ast_node_value_type_t value_type;
    ast_node_value_t value;
    /* Source map */
    int source_line_num;
    int source_column_num;
} ast_node_t;

/* Create a AST node with a given type and the source code location. */
ast_node_t* new_ast_node(ast_node_type_t type, int line_num, int column_num);

/* Set the value for a AST node. */
void ast_node_set_value_symbol(ast_node_t*, const symbol_table_entry_t*);
void ast_node_set_value_operatr(ast_node_t*, int);
void ast_node_set_value_integer(ast_node_t*, int);
void ast_node_set_value_string(ast_node_t*, const char*);

/* Insert a child or sibling for a AST node. */
void ast_node_insert_child(ast_node_t*, ast_node_t *child);
void ast_node_insert_sibling(ast_node_t*, ast_node_t *sibling);

/* Get the name in a string of a AST node type. */
const char* get_ast_node_type_name(ast_node_type_t);

/* Dump all children under a AST node. */
char* ast_dump_str(ast_node_t*);
char* ast_dump_graphviz(ast_node_t*);
char* ast_dump_graphviz_with_options(ast_node_t*, bool use_mem_key);

#endif
