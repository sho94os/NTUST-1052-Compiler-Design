/*
 * tokens.h
 * Declaration of tokens.
 */

#ifndef TOKENS_H
#define TOKENS_H

#include "symbol_table.h"
#include "ast.h"

typedef int token_t;

/** Token Definitions - defined by parser.y **/

#include "y.tab.h"

/** Token Names **/

#define TOKEN_NAMES(TOKEN_NAME)                              \
        TOKEN_NAME(ID,                           "id"       )\
        TOKEN_NAME(INTEGER_LITERAL,              "integer"  )\
        TOKEN_NAME(REAL_LITERAL,                 "real"     )\
        TOKEN_NAME(STRING_LITERAL,               "string"   )\
        TOKEN_NAME(COMMA,                        ","        )\
        TOKEN_NAME(COLON,                        ":"        )\
        TOKEN_NAME(SEMICOLON,                    ";"        )\
        TOKEN_NAME(LEFT_PARENTHESIS,             "("        )\
        TOKEN_NAME(RIGHT_PARENTHESIS,            ")"        )\
        TOKEN_NAME(LEFT_SQUARE_BRACKET,          "["        )\
        TOKEN_NAME(RIGHT_SQUARE_BRACKET,         "]"        )\
        TOKEN_NAME(LEFT_BRACKET,                 "{"        )\
        TOKEN_NAME(RIGHT_BRACKET,                "}"        )\
        TOKEN_NAME(OP_ADDITION,                  "+"        )\
        TOKEN_NAME(OP_SUBTRACTION,               "-"        )\
        TOKEN_NAME(OP_DIVISION,                  "/"        )\
        TOKEN_NAME(OP_MULTIPLICATION,            "*"        )\
        TOKEN_NAME(OP_REMAINDER,                 "%"        )\
        TOKEN_NAME(OP_EXPONENTIATION,            "^"        )\
        TOKEN_NAME(OP_EQUAL_TO,                  "=="       )\
        TOKEN_NAME(OP_NOT_EQUAL_TO,              "!="       )\
        TOKEN_NAME(OP_GREATER_THAN,              "\">\""    )\
        TOKEN_NAME(OP_LESS_THAN,                 "\"<\""    )\
        TOKEN_NAME(OP_GREATER_THAN_OR_EQUAL_TO,  "\">=\""   )\
        TOKEN_NAME(OP_LESS_THAN_OR_EQUAL_TO,     "\"<=\""   )\
        TOKEN_NAME(OP_LOGICAL_AND,               "&&"       )\
        TOKEN_NAME(OP_LOGICAL_OR,                "||"       )\
        TOKEN_NAME(OP_BINARY_AND,                "&"        )\
        TOKEN_NAME(OP_BINARY_OR,                 "|"        )\
        TOKEN_NAME(OP_NOT,                       "!"        )\
        TOKEN_NAME(OP_ASSIGNMENT,                "="        )\
        TOKEN_NAME(OP_ADDITION_ASSIGNMENT,       "+="       )\
        TOKEN_NAME(OP_SUBTRACTION_ASSIGNMENT,    "-="       )\
        TOKEN_NAME(OP_MULTIPLICATION_ASSIGNMENT, "*="       )\
        TOKEN_NAME(OP_DIVISION_ASSIGNMENT,       "/="       )\
        TOKEN_NAME(KW_BOOL,                      "BOOL"     )\
        TOKEN_NAME(KW_BREAK,                     "BREAK"    )\
        TOKEN_NAME(KW_CASE,                      "CASE"     )\
        TOKEN_NAME(KW_CONST,                     "CONST"    )\
        TOKEN_NAME(KW_CONTINUE,                  "CONTINUE" )\
        TOKEN_NAME(KW_DEFAULT,                   "DEFAULT"  )\
        TOKEN_NAME(KW_ELSE,                      "ELSE"     )\
        TOKEN_NAME(KW_FALSE,                     "FALSE"    )\
        TOKEN_NAME(KW_FOR,                       "FOR"      )\
        TOKEN_NAME(KW_FUNC,                      "FUNC"     )\
        TOKEN_NAME(KW_GO,                        "GO"       )\
        TOKEN_NAME(KW_IF,                        "IF"       )\
        TOKEN_NAME(KW_IMPORT,                    "IMPORT"   )\
        TOKEN_NAME(KW_INT,                       "INT"      )\
        TOKEN_NAME(KW_NIL,                       "NIL"      )\
        TOKEN_NAME(KW_PRINT,                     "PRINT"    )\
        TOKEN_NAME(KW_PRINTLN,                   "PRINTLN"  )\
        TOKEN_NAME(KW_REAL,                      "REAL"     )\
        TOKEN_NAME(KW_RETURN,                    "RETURN"   )\
        TOKEN_NAME(KW_STRING,                    "STRING"   )\
        TOKEN_NAME(KW_STRUCT,                    "STRUCT"   )\
        TOKEN_NAME(KW_SWITCH,                    "SWITCH"   )\
        TOKEN_NAME(KW_TRUE,                      "TRUE"     )\
        TOKEN_NAME(KW_TYPE,                      "TYPE"     )\
        TOKEN_NAME(KW_VAR,                       "VAR"      )\
        TOKEN_NAME(KW_VOID,                      "VOID"     )\
        TOKEN_NAME(KW_WHILE,                     "WHILE"    )\

#define HTML_TOKEN_NAMES(HTML_TOKEN_NAME)                    \
        HTML_TOKEN_NAME(OP_GREATER_THAN,             "&gt;" )\
        HTML_TOKEN_NAME(OP_LESS_THAN,                "&lt;" )\
        HTML_TOKEN_NAME(OP_GREATER_THAN_OR_EQUAL_TO, "&gt;=")\
        HTML_TOKEN_NAME(OP_LESS_THAN_OR_EQUAL_TO,    "&lt;=")\

/** Helpers **/

const char* get_token_name(token_t token);
const char* get_html_token_name(token_t token);

#endif
