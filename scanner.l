%{
#include "tokens.h"

#define LIST { strcat(buf, yytext); }

#define token(t)           { LIST; printf("<%s>\n", get_token_name(t)); }
#define tokenInteger(t, i) { LIST; printf("<%s:%d>\n", get_token_name(t), i); }
#define tokenString(t, s)  { LIST; printf("<%s:%s>\n", get_token_name(t), s); }

#define MAX_LINE_LENGTH 256

int linenum = 1;
char buf[MAX_LINE_LENGTH];
char strbuf[MAX_LINE_LENGTH];
%}

%s STRING LINE_COMMENT

digit    [0-9]
decimals {digit}+
exponent [eE]["+"-]?{decimals}
alpha    [A-Za-z]
blank    [ \t]
newline  \r?\n

%%

 /** Delimiters **/

<INITIAL>","                    { token(T_COMMA); }
<INITIAL>":"                    { token(T_COLON); }
<INITIAL>";"                    { token(T_SEMICOLON); }
<INITIAL>"("                    { token(T_LEFT_PARENTHESIS); }
<INITIAL>")"                    { token(T_RIGHT_PARENTHESIS); }
<INITIAL>"["                    { token(T_LEFT_SQUARE_BRACKET); }
<INITIAL>"]"                    { token(T_RIGHT_SQUARE_BRACKET); }
<INITIAL>"{"                    { token(T_LEFT_BRACKET); }
<INITIAL>"}"                    { token(T_RIGHT_BRACKET); }

 /** Arithmetic, Relational, and Logical Operators **/

<INITIAL>"+"                    { token(T_ADDITION); }
<INITIAL>"-"                    { token(T_SUBTRACTION); }
<INITIAL>"/"                    { token(T_DIVISION); }
<INITIAL>"*"                    { token(T_MULTIPLICATION); }
<INITIAL>"^"                    { token(T_EXPONENTIATION); }
<INITIAL>"%"                    { token(T_REMAINDER); }

<INITIAL>"=="                   { token(T_EQUAL_TO); }
<INITIAL>"!="                   { token(T_NOT_EQUAL_TO); }
<INITIAL>">"                    { token(T_GREATER_THAN); }
<INITIAL>"<"                    { token(T_LESS_THAN); }
<INITIAL>">="                   { token(T_GREATER_THAN_OR_EQUAL_TO); }
<INITIAL>"<="                   { token(T_LESS_THAN_OR_EQUAL_TO); }

<INITIAL>"&&"                   { token(T_LOGICAL_AND); }
<INITIAL>"||"                   { token(T_LOGICAL_OR); }
<INITIAL>"!"                    { token(T_LOGICAL_NOT); }

<INITIAL>"="                    { token(T_ASSIGNMENT); }

<INITIAL>"+="                   { token(T_ADDITION_ASSIGNMENT); }
<INITIAL>"-="                   { token(T_SUBTRACTION_ASSIGNMENT); }
<INITIAL>"*="                   { token(T_MULTIPLICATION_ASSIGNMENT); }
<INITIAL>"/="                   { token(T_DIVISION_ASSIGNMENT); }

 /** Keywords **/

<INITIAL>"bool"                 { token(T_BOOL); }
<INITIAL>"break"                { token(T_BREAK); }
<INITIAL>"case"                 { token(T_CASE); }
<INITIAL>"const"                { token(T_CONST); }
<INITIAL>"continue"             { token(T_CONTINUE); }
<INITIAL>"default"              { token(T_DEFAULT); }
<INITIAL>"else"                 { token(T_ELSE); }
<INITIAL>"false"                { token(T_FALSE); }
<INITIAL>"for"                  { token(T_FOR); }
<INITIAL>"func"                 { token(T_FUNC); }
<INITIAL>"go"                   { token(T_GO); }
<INITIAL>"if"                   { token(T_IF); }
<INITIAL>"import"               { token(T_IMPORT); }
<INITIAL>"int"                  { token(T_INT); }
<INITIAL>"nil"                  { token(T_NIL); }
<INITIAL>"print"                { token(T_PRINT); }
<INITIAL>"println"              { token(T_PRINTLN); }
<INITIAL>"real"                 { token(T_REAL); }
<INITIAL>"return"               { token(T_RETURN); }
<INITIAL>"string"               { token(T_STRING); }
<INITIAL>"struct"               { token(T_STRUCT); }
<INITIAL>"switch"               { token(T_SWITCH); }
<INITIAL>"true"                 { token(T_TRUE); }
<INITIAL>"type"                 { token(T_TYPE); }
<INITIAL>"var"                  { token(T_VAR); }
<INITIAL>"void"                 { token(T_VOID); }
<INITIAL>"while".               { token(T_WHILE); }

 /** Blank **/

<INITIAL>{blank}*                        { LIST; }

 /** Identifier **/

<INITIAL>{alpha}({alpha}|{digit}|_)* {
    tokenString(T_ID, yytext);
}

 /** Interger Literal **/

<INITIAL>{decimals} {
    tokenInteger(T_INTEGER_LITERAL, atoi(yytext))
}

 /** Real Literal **/

<INITIAL>["+"-]?({decimals}"."{decimals}?{exponent}?|"."{decimals}{exponent}?|{decimals}{exponent}) {
    tokenString(T_REAL_LITERAL, yytext)
}

 /** String Literal **/

<INITIAL>\" {
    LIST;
    strbuf[0] = '\0';
    BEGIN STRING;
}

<STRING>\" {
    LIST;
    tokenString(T_STRING_LITERAL, strbuf);
    strbuf[0] = '\0';
    BEGIN INITIAL;
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

 /** New Line **/

<LINE_COMMENT>{newline} |
<INITIAL>{newline} {
    LIST;
    BEGIN INITIAL;
    printf("%d: %s", linenum++, buf);
    buf[0] = '\0';
}

 /** Bad Character **/

. {
    LIST;
    printf("%d: %s\n", linenum + 1, buf);
    printf("bad character: '%s'\n", yytext);
    exit(-1);
}

%%

int main(int argc, char **argv) {
    yylex();
    exit(0);
}
