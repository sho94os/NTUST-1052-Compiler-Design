#ifndef TOKENS_H
#define TOKENS_H

/** Identifier (01) **/

#define T_ID                         0x01

/** Literals (0a-0f) **/

#define T_INTEGER_LITERAL            0x0a
#define T_REAL_LITERAL               0x0b
#define T_STRING_LITERAL             0x0c

/** Delimiters (as ASCII code) **/

#define T_COMMA                      0x2c
#define T_COLON                      0x3a
#define T_SEMICOLON                  0x3b
#define T_LEFT_PARENTHESIS           0x28
#define T_RIGHT_PARENTHESIS          0x29
#define T_LEFT_SQUARE_BRACKET        0x5b
#define T_RIGHT_SQUARE_BRACKET       0x5d
#define T_LEFT_BRACKET               0x7b
#define T_RIGHT_BRACKET              0x7d

/** Arithmetic, Relational, and Logical Operators (as ASCII code, 10-1f) **/

#define T_ADDITION                   0x2b
#define T_SUBTRACTION                0x2d
#define T_DIVISION                   0x2f
#define T_MULTIPLICATION             0x2a

#define T_EXPONENTIATION             0x5e
#define T_REMAINDER                  0x25

#define T_EQUAL_TO                   0x11
#define T_NOT_EQUAL_TO               0x12
#define T_GREATER_THAN               0x13
#define T_LESS_THAN                  0x14
#define T_GREATER_THAN_OR_EQUAL_TO   0x15
#define T_LESS_THAN_OR_EQUAL_TO      0x16

#define T_LOGICAL_AND                0x17
#define T_LOGICAL_OR                 0x18
#define T_LOGICAL_NOT                0x21

#define T_ASSIGNMENT                 0x3d

#define T_ADDITION_ASSIGNMENT        0x19
#define T_SUBTRACTION_ASSIGNMENT     0x1a
#define T_MULTIPLICATION_ASSIGNMENT  0x1b
#define T_DIVISION_ASSIGNMENT        0x1c

/** Keywords (41-59, 61-79) **/

#define T_BOOL                       0x41
#define T_BREAK                      0x42
#define T_CASE                       0x43
#define T_CONST                      0x44
#define T_CONTINUE                   0x45
#define T_DEFAULT                    0x46
#define T_ELSE                       0x47
#define T_FALSE                      0x48
#define T_FOR                        0x49
#define T_FUNC                       0x4a
#define T_GO                         0x4b
#define T_IF                         0x4c
#define T_IMPORT                     0x4d
#define T_INT                        0x4e
#define T_NIL                        0x4f
#define T_PRINT                      0x50
#define T_PRINTLN                    0x51
#define T_REAL                       0x52
#define T_RETURN                     0x53
#define T_STRING                     0x54
#define T_STRUCT                     0x55
#define T_SWITCH                     0x56
#define T_TRUE                       0x57
#define T_TYPE                       0x58
#define T_VAR                        0x59
#define T_VOID                       0x61
#define T_WHILE                      0x62

/** Token Names **/

#define TNAME_ID                         "id"
#define TNAME_INTEGER_LITERAL            "integer"
#define TNAME_REAL_LITERAL               "real"
#define TNAME_STRING_LITERAL             "string"
#define TNAME_COMMA                      "','"
#define TNAME_COLON                      "':'"
#define TNAME_SEMICOLON                  "';'"
#define TNAME_LEFT_PARENTHESIS           "'('"
#define TNAME_RIGHT_PARENTHESIS          "')'"
#define TNAME_LEFT_SQUARE_BRACKET        "'['"
#define TNAME_RIGHT_SQUARE_BRACKET       "']'"
#define TNAME_LEFT_BRACKET               "'{'"
#define TNAME_RIGHT_BRACKET              "'}'"
#define TNAME_ADDITION                   "'+'"
#define TNAME_SUBTRACTION                "'-'"
#define TNAME_DIVISION                   "'/'"
#define TNAME_MULTIPLICATION             "'*'"
#define TNAME_EXPONENTIATION             "'^'"
#define TNAME_REMAINDER                  "'%'"
#define TNAME_EQUAL_TO                   "'=='"
#define TNAME_NOT_EQUAL_TO               "'!='"
#define TNAME_GREATER_THAN               "'>'"
#define TNAME_LESS_THAN                  "'<'"
#define TNAME_GREATER_THAN_OR_EQUAL_TO   "'>='"
#define TNAME_LESS_THAN_OR_EQUAL_TO      "'<='"
#define TNAME_LOGICAL_AND                "'&&'"
#define TNAME_LOGICAL_OR                 "'||'"
#define TNAME_LOGICAL_NOT                "'!'"
#define TNAME_ASSIGNMENT                 "'='"
#define TNAME_ADDITION_ASSIGNMENT        "'+='"
#define TNAME_SUBTRACTION_ASSIGNMENT     "'-='"
#define TNAME_MULTIPLICATION_ASSIGNMENT  "'*='"
#define TNAME_DIVISION_ASSIGNMENT        "'/='"
#define TNAME_BOOL                       "BOOL"
#define TNAME_BREAK                      "BREAK"
#define TNAME_CASE                       "CASE"
#define TNAME_CONST                      "CONST"
#define TNAME_CONTINUE                   "CONTINUE"
#define TNAME_DEFAULT                    "DEFAULT"
#define TNAME_ELSE                       "ELSE"
#define TNAME_FALSE                      "FALSE"
#define TNAME_FOR                        "FOR"
#define TNAME_FUNC                       "FUNC"
#define TNAME_GO                         "GO"
#define TNAME_IF                         "IF"
#define TNAME_IMPORT                     "IMPORT"
#define TNAME_INT                        "INT"
#define TNAME_NIL                        "NIL"
#define TNAME_PRINT                      "PRINT"
#define TNAME_PRINTLN                    "PRINTLN"
#define TNAME_REAL                       "REAL"
#define TNAME_RETURN                     "RETURN"
#define TNAME_STRING                     "STRING"
#define TNAME_STRUCT                     "STRUCT"
#define TNAME_SWITCH                     "SWITCH"
#define TNAME_TRUE                       "TRUE"
#define TNAME_TYPE                       "TYPE"
#define TNAME_VAR                        "VAR"
#define TNAME_VOID                       "VOID"
#define TNAME_WHILE                      "WHILE"

const char* get_token_name(char token);

#endif
