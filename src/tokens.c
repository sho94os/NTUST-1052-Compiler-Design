#include <string.h>
#include "tokens.h"

const char* get_token_name(token_t token) {
    switch (token) {
        case T_ID:
            return TNAME_ID;
            break;
        case T_INTEGER_LITERAL:
            return TNAME_INTEGER_LITERAL;
            break;
        case T_REAL_LITERAL:
            return TNAME_REAL_LITERAL;
            break;
        case T_STRING_LITERAL:
            return TNAME_STRING_LITERAL;
            break;
        case T_COMMA:
            return TNAME_COMMA;
            break;
        case T_COLON:
            return TNAME_COLON;
            break;
        case T_SEMICOLON:
            return TNAME_SEMICOLON;
            break;
        case T_LEFT_PARENTHESIS:
            return TNAME_LEFT_PARENTHESIS;
            break;
        case T_RIGHT_PARENTHESIS:
            return TNAME_RIGHT_PARENTHESIS;
            break;
        case T_LEFT_SQUARE_BRACKET:
            return TNAME_LEFT_SQUARE_BRACKET;
            break;
        case T_RIGHT_SQUARE_BRACKET:
            return TNAME_RIGHT_SQUARE_BRACKET;
            break;
        case T_LEFT_BRACKET:
            return TNAME_LEFT_BRACKET;
            break;
        case T_RIGHT_BRACKET:
            return TNAME_RIGHT_BRACKET;
            break;
        case T_ADDITION:
            return TNAME_ADDITION;
            break;
        case T_SUBTRACTION:
            return TNAME_SUBTRACTION;
            break;
        case T_DIVISION:
            return TNAME_DIVISION;
            break;
        case T_MULTIPLICATION:
            return TNAME_MULTIPLICATION;
            break;
        case T_EXPONENTIATION:
            return TNAME_EXPONENTIATION;
            break;
        case T_REMAINDER:
            return TNAME_REMAINDER;
            break;
        case T_EQUAL_TO:
            return TNAME_EQUAL_TO;
            break;
        case T_NOT_EQUAL_TO:
            return TNAME_NOT_EQUAL_TO;
            break;
        case T_GREATER_THAN:
            return TNAME_GREATER_THAN;
            break;
        case T_LESS_THAN:
            return TNAME_LESS_THAN;
            break;
        case T_GREATER_THAN_OR_EQUAL_TO:
            return TNAME_GREATER_THAN_OR_EQUAL_TO;
            break;
        case T_LESS_THAN_OR_EQUAL_TO:
            return TNAME_LESS_THAN_OR_EQUAL_TO;
            break;
        case T_LOGICAL_AND:
            return TNAME_LOGICAL_AND;
            break;
        case T_LOGICAL_OR:
            return TNAME_LOGICAL_OR;
            break;
        case T_LOGICAL_NOT:
            return TNAME_LOGICAL_NOT;
            break;
        case T_ASSIGNMENT:
            return TNAME_ASSIGNMENT;
            break;
        case T_ADDITION_ASSIGNMENT:
            return TNAME_ADDITION_ASSIGNMENT;
            break;
        case T_SUBTRACTION_ASSIGNMENT:
            return TNAME_SUBTRACTION_ASSIGNMENT;
            break;
        case T_MULTIPLICATION_ASSIGNMENT:
            return TNAME_MULTIPLICATION_ASSIGNMENT;
            break;
        case T_DIVISION_ASSIGNMENT:
            return TNAME_DIVISION_ASSIGNMENT;
            break;
        case T_BOOL:
            return TNAME_BOOL;
            break;
        case T_BREAK:
            return TNAME_BREAK;
            break;
        case T_CASE:
            return TNAME_CASE;
            break;
        case T_CONST:
            return TNAME_CONST;
            break;
        case T_CONTINUE:
            return TNAME_CONTINUE;
            break;
        case T_DEFAULT:
            return TNAME_DEFAULT;
            break;
        case T_ELSE:
            return TNAME_ELSE;
            break;
        case T_FALSE:
            return TNAME_FALSE;
            break;
        case T_FOR:
            return TNAME_FOR;
            break;
        case T_FUNC:
            return TNAME_FUNC;
            break;
        case T_GO:
            return TNAME_GO;
            break;
        case T_IF:
            return TNAME_IF;
            break;
        case T_IMPORT:
            return TNAME_IMPORT;
            break;
        case T_INT:
            return TNAME_INT;
            break;
        case T_NIL:
            return TNAME_NIL;
            break;
        case T_PRINT:
            return TNAME_PRINT;
            break;
        case T_PRINTLN:
            return TNAME_PRINTLN;
            break;
        case T_REAL:
            return TNAME_REAL;
            break;
        case T_RETURN:
            return TNAME_RETURN;
            break;
        case T_STRING:
            return TNAME_STRING;
            break;
        case T_STRUCT:
            return TNAME_STRUCT;
            break;
        case T_SWITCH:
            return TNAME_SWITCH;
            break;
        case T_TRUE:
            return TNAME_TRUE;
            break;
        case T_TYPE:
            return TNAME_TYPE;
            break;
        case T_VAR:
            return TNAME_VAR;
            break;
        case T_VOID:
            return TNAME_VOID;
            break;
        case T_WHILE:
            return TNAME_WHILE;
            break;
        default:
            return NULL;
            break;
    }
}
