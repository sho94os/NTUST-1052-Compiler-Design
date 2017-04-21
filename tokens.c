#include <string.h>
#include "tokens.h"

const char* get_token_name(char token) {
    static char token_name[16];

    switch (token) {
        case T_ID:
            strcpy(token_name, "ID");
            break;

        case T_BOOL:
            strcpy(token_name, "BOOL");
            break;

        case T_BREAK:
            strcpy(token_name, "BREAK");
            break;

        case T_CASE:
            strcpy(token_name, "CASE");
            break;

        case T_CONST:
            strcpy(token_name, "CONST");
            break;

        case T_CONTINUE:
            strcpy(token_name, "CONTINUE");
            break;

        case T_DEFAULT:
            strcpy(token_name, "DEFAULT");
            break;

        case T_ELSE:
            strcpy(token_name, "ELSE");
            break;

        case T_FALSE:
            strcpy(token_name, "FALSE");
            break;

        case T_FOR:
            strcpy(token_name, "FOR");
            break;

        case T_FUNC:
            strcpy(token_name, "FUNC");
            break;

        case T_GO:
            strcpy(token_name, "GO");
            break;

        case T_IF:
            strcpy(token_name, "IF");
            break;

        case T_IMPORT:
            strcpy(token_name, "IMPORT");
            break;

        case T_INT:
            strcpy(token_name, "INT");
            break;

        case T_NIL:
            strcpy(token_name, "NIL");
            break;

        case T_PRINT:
            strcpy(token_name, "PRINT");
            break;

        case T_PRINTLN:
            strcpy(token_name, "PRINTLN");
            break;

        case T_REAL:
            strcpy(token_name, "REAL");
            break;

        case T_RETURN:
            strcpy(token_name, "RETURN");
            break;

        case T_STRING:
            strcpy(token_name, "STRING");
            break;

        case T_STRUCT:
            strcpy(token_name, "STRUCT");
            break;

        case T_SWITCH:
            strcpy(token_name, "SWITCH");
            break;

        case T_TRUE:
            strcpy(token_name, "TRUE");
            break;

        case T_TYPE:
            strcpy(token_name, "TYPE");
            break;

        case T_VAR:
            strcpy(token_name, "VAR");
            break;

        case T_VOID:
            strcpy(token_name, "VOID");
            break;

        case T_WHILE:
            strcpy(token_name, "WHILE");
            break;

        default:
            token_name[0] = '\'';
            token_name[1] = token;
            token_name[2] = '\'';
            token_name[3] = '\0';
            break;
    }

    return token_name;
}
