%{
#include "tokens.h"
#include "symbol_table.h"

#define LIST { column_num += strlen(yytext); strcat(buf, yytext); }

#ifndef STANDALONE_SCANNER
    #define LINE { line_num++; column_num = 1; buf[0] = '\0'; }
    #define set_yylloc() { yylloc.first_line = line_num; yylloc.first_column = column_num; }
    #define token(t)           { LIST; set_yylloc(); return t; }
    #define tokenSymbol(t, s)  { LIST; set_yylloc(); yylval.symbol = s; return t; }
    #define tokenInteger(t, i) { LIST; set_yylloc(); yylval.integer = i; return t; }
    #define tokenReal(t, s)    { LIST; set_yylloc(); yylval.string = s; return t; }
    #define tokenString(t, s)  { LIST; set_yylloc(); yylval.string = s; return t; }
#else
    #include <math.h>
    #define OPTBUF_SIZE 4096
    char optbuf[OPTBUF_SIZE];
    int optbuf_w = 0;
    #define LINE {                                                            \
        printf("%d:%*c%s", line_num, 3 - (int)log10(line_num), ' ', buf);     \
        if (optbuf_w > 0) {                                                   \
            printf(" -> %s\n", optbuf);                                       \
        }                                                                     \
        optbuf_w = 0;                                                         \
        line_num++; column_num = 1; buf[0] = '\0';                            \
    }
    #define token(t) {                                                        \
        optbuf_w +=                                                           \
          snprintf(optbuf + optbuf_w, OPTBUF_SIZE - optbuf_w,                 \
            "<%s>", get_token_name(t));                                       \
        LIST;                                                                 \
    }
    #define tokenSymbol(t, s) {                                               \
        optbuf_w +=                                                           \
          snprintf(optbuf + optbuf_w, OPTBUF_SIZE - optbuf_w,                 \
            "<%s:%s>", get_token_name(t), s->identifier);                     \
        LIST;                                                                 \
    }
    #define tokenInteger(t, i) {                                              \
        optbuf_w +=                                                           \
          snprintf(optbuf + optbuf_w, OPTBUF_SIZE - optbuf_w,                 \
            "<%s:%d>", get_token_name(t), i);                                 \
        LIST;                                                                 \
    }
    #define tokenReal(t, s) {                                                 \
        optbuf_w +=                                                           \
          snprintf(optbuf + optbuf_w, OPTBUF_SIZE - optbuf_w,                 \
            "<%s:%s>", get_token_name(t), s);                                 \
        LIST;                                                                 \
    }
    #define tokenString(t, s) {                                               \
        optbuf_w +=                                                           \
          snprintf(optbuf + optbuf_w, OPTBUF_SIZE - optbuf_w,                 \
            "<%s:\"%s\">", get_token_name(t), s);                             \
        LIST;                                                                 \
    }
#endif

#define MAX_LINE_LENGTH 256

int line_num = 1;
int column_num = 1;
char buf[MAX_LINE_LENGTH];
char strbuf[MAX_LINE_LENGTH];
symbol_table_t *symbol_table;
%}

%s STRING LINE_COMMENT BLOCK_COMMENT

digit    [0-9]
decimals {digit}+
exponent [eE]["+"-]?{decimals}
alpha    [A-Za-z]
blank    [ \t]
newline  \r?\n

%%

 /** Delimiters **/

<INITIAL>","                    { token(COMMA); }
<INITIAL>":"                    { token(COLON); }
<INITIAL>";"                    { token(SEMICOLON); }
<INITIAL>"("                    { token(LEFT_PARENTHESIS); }
<INITIAL>")"                    { token(RIGHT_PARENTHESIS); }
<INITIAL>"["                    { token(LEFT_SQUARE_BRACKET); }
<INITIAL>"]"                    { token(RIGHT_SQUARE_BRACKET); }
<INITIAL>"{"                    { token(LEFT_BRACKET); }
<INITIAL>"}"                    { token(RIGHT_BRACKET); }

 /** Arithmetic, Relational, and Logical Operators **/

<INITIAL>"+"                    { token(OP_ADDITION); }
<INITIAL>"-"                    { token(OP_SUBTRACTION); }
<INITIAL>"/"                    { token(OP_DIVISION); }
<INITIAL>"*"                    { token(OP_MULTIPLICATION); }
<INITIAL>"^"                    { token(OP_EXPONENTIATION); }
<INITIAL>"%"                    { token(OP_REMAINDER); }

<INITIAL>"=="                   { token(OP_EQUAL_TO); }
<INITIAL>"!="                   { token(OP_NOT_EQUAL_TO); }
<INITIAL>">"                    { token(OP_GREATER_THAN); }
<INITIAL>"<"                    { token(OP_LESS_THAN); }
<INITIAL>">="                   { token(OP_GREATER_THAN_OR_EQUAL_TO); }
<INITIAL>"<="                   { token(OP_LESS_THAN_OR_EQUAL_TO); }

<INITIAL>"&&"                   { token(OP_LOGICAL_AND); }
<INITIAL>"||"                   { token(OP_LOGICAL_OR); }
<INITIAL>"!"                    { token(OP_LOGICAL_NOT); }

<INITIAL>"="                    { token(OP_ASSIGNMENT); }

<INITIAL>"+="                   { token(OP_ADDITION_ASSIGNMENT); }
<INITIAL>"-="                   { token(OP_SUBTRACTION_ASSIGNMENT); }
<INITIAL>"*="                   { token(OP_MULTIPLICATION_ASSIGNMENT); }
<INITIAL>"/="                   { token(OP_DIVISION_ASSIGNMENT); }

 /** Keywords **/

<INITIAL>"bool"                 { token(KW_BOOL); }
<INITIAL>"break"                { token(KW_BREAK); }
<INITIAL>"case"                 { token(KW_CASE); }
<INITIAL>"const"                { token(KW_CONST); }
<INITIAL>"continue"             { token(KW_CONTINUE); }
<INITIAL>"default"              { token(KW_DEFAULT); }
<INITIAL>"else"                 { token(KW_ELSE); }
<INITIAL>"false"                { token(KW_FALSE); }
<INITIAL>"for"                  { token(KW_FOR); }
<INITIAL>"func"                 { token(KW_FUNC); }
<INITIAL>"go"                   { token(KW_GO); }
<INITIAL>"if"                   { token(KW_IF); }
<INITIAL>"import"               { token(KW_IMPORT); }
<INITIAL>"int"                  { token(KW_INT); }
<INITIAL>"nil"                  { token(KW_NIL); }
<INITIAL>"print"                { token(KW_PRINT); }
<INITIAL>"println"              { token(KW_PRINTLN); }
<INITIAL>"real"                 { token(KW_REAL); }
<INITIAL>"return"               { token(KW_RETURN); }
<INITIAL>"string"               { token(KW_STRING); }
<INITIAL>"struct"               { token(KW_STRUCT); }
<INITIAL>"switch"               { token(KW_SWITCH); }
<INITIAL>"true"                 { token(KW_TRUE); }
<INITIAL>"type"                 { token(KW_TYPE); }
<INITIAL>"var"                  { token(KW_VAR); }
<INITIAL>"void"                 { token(KW_VOID); }
<INITIAL>"while"                { token(KW_WHILE); }

 /** Blank **/

<INITIAL>{blank}*               { LIST; }

 /** Identifier **/

<INITIAL>{alpha}({alpha}|{digit}|_)* {
    tokenSymbol(ID, symbol_table_insert(symbol_table, yytext));
}

 /** Interger Literal **/

<INITIAL>{decimals} {
    tokenInteger(INTEGER_LITERAL, atoi(yytext))
}

 /** Real Literal **/

<INITIAL>["+"-]?({decimals}"."{decimals}?{exponent}?|"."{decimals}{exponent}?|{decimals}{exponent}) {
    tokenReal(REAL_LITERAL, yytext)
}

 /** String Literal **/

<INITIAL>\" {
    LIST;
    strbuf[0] = '\0';
    BEGIN STRING;
}

<STRING>\" {
    BEGIN INITIAL;
    tokenString(STRING_LITERAL, strbuf);
}

<STRING>\"\" {
    LIST;
    strcat(strbuf, "\"");
}

<STRING>. {
    LIST;
    strcat(strbuf, yytext);
}

 /** Comments **/

<INITIAL>"//" {
    LIST;
    BEGIN LINE_COMMENT;
}

<LINE_COMMENT>. {
    LIST;
}

<INITIAL>"/*" {
    LIST;
    BEGIN BLOCK_COMMENT;
}

<BLOCK_COMMENT>. {
    LIST;
}

<BLOCK_COMMENT>"*/" {
    LIST;
    BEGIN INITIAL;
}

 /** New Line **/

<LINE_COMMENT>{newline} |
<INITIAL>{newline} {
    LIST;
    BEGIN INITIAL;
    LINE;
}

<BLOCK_COMMENT>{newline} {
    LIST;
    LINE;
}

 /** Bad Character **/

. {
    LIST;
    printf("%d: %s\n", line_num + 1, buf);
    printf("bad character: '%s'\n", yytext);
    exit(-1);
}

%%

void init_symbol_table() {
    symbol_table = symbol_table_create();
}

void print_symbol_table() {
    printf("\nSymbol Table:\n");
    printf("%s", symbol_table_dump_str(symbol_table));
}
