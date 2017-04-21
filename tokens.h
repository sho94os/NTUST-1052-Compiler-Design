#ifndef TOKENS_H
#define TOKENS_H

#define T_ID       0x41

#define T_BOOL     0x51
#define T_BREAK    0x52
#define T_CASE     0x53
#define T_CONST    0x54
#define T_CONTINUE 0x55
#define T_DEFAULT  0x56
#define T_ELSE     0x57
#define T_FALSE    0x58
#define T_FOR      0x59
#define T_FUNC     0x5a
#define T_GO       0x5b
#define T_IF       0x5c
#define T_IMPORT   0x5d
#define T_INT      0x5e
#define T_NIL      0x5f
#define T_PRINT    0x60
#define T_PRINTLN  0x61
#define T_REAL     0x62
#define T_RETURN   0x63
#define T_STRING   0x64
#define T_STRUCT   0x65
#define T_SWITCH   0x66
#define T_TRUE     0x67
#define T_TYPE     0x68
#define T_VAR      0x69
#define T_VOID     0x6a
#define T_WHILE    0x6b

const char* get_token_name(char token);

#endif
