#include <string.h>
#include "tokens.h"

const char* get_token_name(token_t token) {
    switch (token) {
        case ID:
            return TNAME_ID;
            break;
        case INTEGER_LITERAL:
            return TNAME_INTEGER_LITERAL;
            break;
        case REAL_LITERAL:
            return TNAME_REAL_LITERAL;
            break;
        case STRING_LITERAL:
            return TNAME_STRING_LITERAL;
            break;
        case COMMA:
            return TNAME_COMMA;
            break;
        case COLON:
            return TNAME_COLON;
            break;
        case SEMICOLON:
            return TNAME_SEMICOLON;
            break;
        case LEFT_PARENTHESIS:
            return TNAME_LEFT_PARENTHESIS;
            break;
        case RIGHT_PARENTHESIS:
            return TNAME_RIGHT_PARENTHESIS;
            break;
        case LEFT_SQUARE_BRACKET:
            return TNAME_LEFT_SQUARE_BRACKET;
            break;
        case RIGHT_SQUARE_BRACKET:
            return TNAME_RIGHT_SQUARE_BRACKET;
            break;
        case LEFT_BRACKET:
            return TNAME_LEFT_BRACKET;
            break;
        case RIGHT_BRACKET:
            return TNAME_RIGHT_BRACKET;
            break;
        case OP_ADDITION:
            return TNAME_OP_ADDITION;
            break;
        case OP_SUBTRACTION:
            return TNAME_OP_SUBTRACTION;
            break;
        case OP_DIVISION:
            return TNAME_OP_DIVISION;
            break;
        case OP_MULTIPLICATION:
            return TNAME_OP_MULTIPLICATION;
            break;
        case OP_REMAINDER:
            return TNAME_OP_REMAINDER;
            break;
        case OP_EXPONENTIATION:
            return TNAME_OP_EXPONENTIATION;
            break;
        case OP_EQUAL_TO:
            return TNAME_OP_EQUAL_TO;
            break;
        case OP_NOT_EQUAL_TO:
            return TNAME_OP_NOT_EQUAL_TO;
            break;
        case OP_GREATER_THAN:
            return TNAME_OP_GREATER_THAN;
            break;
        case OP_LESS_THAN:
            return TNAME_OP_LESS_THAN;
            break;
        case OP_GREATER_THAN_OR_EQUAL_TO:
            return TNAME_OP_GREATER_THAN_OR_EQUAL_TO;
            break;
        case OP_LESS_THAN_OR_EQUAL_TO:
            return TNAME_OP_LESS_THAN_OR_EQUAL_TO;
            break;
        case OP_LOGICAL_AND:
            return TNAME_OP_LOGICAL_AND;
            break;
        case OP_LOGICAL_OR:
            return TNAME_OP_LOGICAL_OR;
            break;
        case OP_LOGICAL_NOT:
            return TNAME_OP_LOGICAL_NOT;
            break;
        case OP_ASSIGNMENT:
            return TNAME_OP_ASSIGNMENT;
            break;
        case OP_ADDITION_ASSIGNMENT:
            return TNAME_OP_ADDITION_ASSIGNMENT;
            break;
        case OP_SUBTRACTION_ASSIGNMENT:
            return TNAME_OP_SUBTRACTION_ASSIGNMENT;
            break;
        case OP_MULTIPLICATION_ASSIGNMENT:
            return TNAME_OP_MULTIPLICATION_ASSIGNMENT;
            break;
        case OP_DIVISION_ASSIGNMENT:
            return TNAME_OP_DIVISION_ASSIGNMENT;
            break;
        case KW_BOOL:
            return TNAME_KW_BOOL;
            break;
        case KW_BREAK:
            return TNAME_KW_BREAK;
            break;
        case KW_CASE:
            return TNAME_KW_CASE;
            break;
        case KW_CONST:
            return TNAME_KW_CONST;
            break;
        case KW_CONTINUE:
            return TNAME_KW_CONTINUE;
            break;
        case KW_DEFAULT:
            return TNAME_KW_DEFAULT;
            break;
        case KW_ELSE:
            return TNAME_KW_ELSE;
            break;
        case KW_FALSE:
            return TNAME_KW_FALSE;
            break;
        case KW_FOR:
            return TNAME_KW_FOR;
            break;
        case KW_FUNC:
            return TNAME_KW_FUNC;
            break;
        case KW_GO:
            return TNAME_KW_GO;
            break;
        case KW_IF:
            return TNAME_KW_IF;
            break;
        case KW_IMPORT:
            return TNAME_KW_IMPORT;
            break;
        case KW_INT:
            return TNAME_KW_INT;
            break;
        case KW_NIL:
            return TNAME_KW_NIL;
            break;
        case KW_PRINT:
            return TNAME_KW_PRINT;
            break;
        case KW_PRINTLN:
            return TNAME_KW_PRINTLN;
            break;
        case KW_REAL:
            return TNAME_KW_REAL;
            break;
        case KW_RETURN:
            return TNAME_KW_RETURN;
            break;
        case KW_STRING:
            return TNAME_KW_STRING;
            break;
        case KW_STRUCT:
            return TNAME_KW_STRUCT;
            break;
        case KW_SWITCH:
            return TNAME_KW_SWITCH;
            break;
        case KW_TRUE:
            return TNAME_KW_TRUE;
            break;
        case KW_TYPE:
            return TNAME_KW_TYPE;
            break;
        case KW_VAR:
            return TNAME_KW_VAR;
            break;
        case KW_VOID:
            return TNAME_KW_VOID;
            break;
        case KW_WHILE:
            return TNAME_KW_WHILE;
            break;
        default:
            return NULL;
            break;
    }
}
