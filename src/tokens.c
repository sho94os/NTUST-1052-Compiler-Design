#include <string.h>
#include "tokens.h"

const char* get_token_name(char token) {
    static char token_name[16];

    switch (token) {
        case T_ID:
            strcpy(token_name, TNAME_ID);
            break;
        case T_INTEGER_LITERAL:
            strcpy(token_name, TNAME_INTEGER_LITERAL);
            break;
        case T_REAL_LITERAL:
            strcpy(token_name, TNAME_REAL_LITERAL);
            break;
        case T_STRING_LITERAL:
            strcpy(token_name, TNAME_STRING_LITERAL);
            break;
        case T_COMMA:
            strcpy(token_name, TNAME_COMMA);
            break;
        case T_COLON:
            strcpy(token_name, TNAME_COLON);
            break;
        case T_SEMICOLON:
            strcpy(token_name, TNAME_SEMICOLON);
            break;
        case T_LEFT_PARENTHESIS:
            strcpy(token_name, TNAME_LEFT_PARENTHESIS);
            break;
        case T_RIGHT_PARENTHESIS:
            strcpy(token_name, TNAME_RIGHT_PARENTHESIS);
            break;
        case T_LEFT_SQUARE_BRACKET:
            strcpy(token_name, TNAME_LEFT_SQUARE_BRACKET);
            break;
        case T_RIGHT_SQUARE_BRACKET:
            strcpy(token_name, TNAME_RIGHT_SQUARE_BRACKET);
            break;
        case T_LEFT_BRACKET:
            strcpy(token_name, TNAME_LEFT_BRACKET);
            break;
        case T_RIGHT_BRACKET:
            strcpy(token_name, TNAME_RIGHT_BRACKET);
            break;
        case T_ADDITION:
            strcpy(token_name, TNAME_ADDITION);
            break;
        case T_SUBTRACTION:
            strcpy(token_name, TNAME_SUBTRACTION);
            break;
        case T_DIVISION:
            strcpy(token_name, TNAME_DIVISION);
            break;
        case T_MULTIPLICATION:
            strcpy(token_name, TNAME_MULTIPLICATION);
            break;
        case T_EXPONENTIATION:
            strcpy(token_name, TNAME_EXPONENTIATION);
            break;
        case T_REMAINDER:
            strcpy(token_name, TNAME_REMAINDER);
            break;
        case T_EQUAL_TO:
            strcpy(token_name, TNAME_EQUAL_TO);
            break;
        case T_NOT_EQUAL_TO:
            strcpy(token_name, TNAME_NOT_EQUAL_TO);
            break;
        case T_GREATER_THAN:
            strcpy(token_name, TNAME_GREATER_THAN);
            break;
        case T_LESS_THAN:
            strcpy(token_name, TNAME_LESS_THAN);
            break;
        case T_GREATER_THAN_OR_EQUAL_TO:
            strcpy(token_name, TNAME_GREATER_THAN_OR_EQUAL_TO);
            break;
        case T_LESS_THAN_OR_EQUAL_TO:
            strcpy(token_name, TNAME_LESS_THAN_OR_EQUAL_TO);
            break;
        case T_LOGICAL_AND:
            strcpy(token_name, TNAME_LOGICAL_AND);
            break;
        case T_LOGICAL_OR:
            strcpy(token_name, TNAME_LOGICAL_OR);
            break;
        case T_LOGICAL_NOT:
            strcpy(token_name, TNAME_LOGICAL_NOT);
            break;
        case T_ASSIGNMENT:
            strcpy(token_name, TNAME_ASSIGNMENT);
            break;
        case T_ADDITION_ASSIGNMENT:
            strcpy(token_name, TNAME_ADDITION_ASSIGNMENT);
            break;
        case T_SUBTRACTION_ASSIGNMENT:
            strcpy(token_name, TNAME_SUBTRACTION_ASSIGNMENT);
            break;
        case T_MULTIPLICATION_ASSIGNMENT:
            strcpy(token_name, TNAME_MULTIPLICATION_ASSIGNMENT);
            break;
        case T_DIVISION_ASSIGNMENT:
            strcpy(token_name, TNAME_DIVISION_ASSIGNMENT);
            break;
        case T_BOOL:
            strcpy(token_name, TNAME_BOOL);
            break;
        case T_BREAK:
            strcpy(token_name, TNAME_BREAK);
            break;
        case T_CASE:
            strcpy(token_name, TNAME_CASE);
            break;
        case T_CONST:
            strcpy(token_name, TNAME_CONST);
            break;
        case T_CONTINUE:
            strcpy(token_name, TNAME_CONTINUE);
            break;
        case T_DEFAULT:
            strcpy(token_name, TNAME_DEFAULT);
            break;
        case T_ELSE:
            strcpy(token_name, TNAME_ELSE);
            break;
        case T_FALSE:
            strcpy(token_name, TNAME_FALSE);
            break;
        case T_FOR:
            strcpy(token_name, TNAME_FOR);
            break;
        case T_FUNC:
            strcpy(token_name, TNAME_FUNC);
            break;
        case T_GO:
            strcpy(token_name, TNAME_GO);
            break;
        case T_IF:
            strcpy(token_name, TNAME_IF);
            break;
        case T_IMPORT:
            strcpy(token_name, TNAME_IMPORT);
            break;
        case T_INT:
            strcpy(token_name, TNAME_INT);
            break;
        case T_NIL:
            strcpy(token_name, TNAME_NIL);
            break;
        case T_PRINT:
            strcpy(token_name, TNAME_PRINT);
            break;
        case T_PRINTLN:
            strcpy(token_name, TNAME_PRINTLN);
            break;
        case T_REAL:
            strcpy(token_name, TNAME_REAL);
            break;
        case T_RETURN:
            strcpy(token_name, TNAME_RETURN);
            break;
        case T_STRING:
            strcpy(token_name, TNAME_STRING);
            break;
        case T_STRUCT:
            strcpy(token_name, TNAME_STRUCT);
            break;
        case T_SWITCH:
            strcpy(token_name, TNAME_SWITCH);
            break;
        case T_TRUE:
            strcpy(token_name, TNAME_TRUE);
            break;
        case T_TYPE:
            strcpy(token_name, TNAME_TYPE);
            break;
        case T_VAR:
            strcpy(token_name, TNAME_VAR);
            break;
        case T_VOID:
            strcpy(token_name, TNAME_VOID);
            break;
        case T_WHILE:
            strcpy(token_name, TNAME_WHILE);
            break;
    }

    return token_name;
}
