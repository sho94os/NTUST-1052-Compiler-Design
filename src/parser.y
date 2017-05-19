%{
#include <stdio.h>
#include "tokens.h"
#define Trace(a, t, r) printf("%s %s to %s\n", a, t, r);
%}

%start program

%union {
    char* string;
    int   integer;
}

/** Identifier **/

%token ID

/** Literals **/

%token <integer> INTEGER_LITERAL
%token <string>  REAL_LITERAL
%token <string>  STRING_LITERAL

/** Delimiters **/

%token COMMA
%token COLON
%token SEMICOLON
%token LEFT_PARENTHESIS
%token RIGHT_PARENTHESIS
%token LEFT_SQUARE_BRACKET
%token RIGHT_SQUARE_BRACKET
%token LEFT_BRACKET
%token RIGHT_BRACKET

/** Arithmetic, Relational, and Logical Operators **/

%left OP_ADDITION
%left OP_SUBTRACTION
%left OP_DIVISION
%left OP_MULTIPLICATION
%left OP_REMAINDER
%right OP_EXPONENTIATION

%nonassoc OP_EQUAL_TO
%nonassoc OP_NOT_EQUAL_TO
%nonassoc OP_GREATER_THAN
%nonassoc OP_LESS_THAN
%nonassoc OP_GREATER_THAN_OR_EQUAL_TO
%nonassoc OP_LESS_THAN_OR_EQUAL_TO

%left OP_LOGICAL_AND
%left OP_LOGICAL_OR
%left OP_LOGICAL_NOT

%right OP_ASSIGNMENT

%right OP_ADDITION_ASSIGNMENT
%right OP_SUBTRACTION_ASSIGNMENT
%right OP_MULTIPLICATION_ASSIGNMENT
%right OP_DIVISION_ASSIGNMENT

/** Keywords **/

%token KW_BOOL
%token KW_BREAK
%token KW_CASE
%token KW_CONST
%token KW_CONTINUE
%token KW_DEFAULT
%token KW_ELSE
%token KW_FALSE
%token KW_FOR
%token KW_FUNC
%token KW_GO
%token KW_IF
%token KW_IMPORT
%token KW_INT
%token KW_NIL
%token KW_PRINT
%token KW_PRINTLN
%token KW_REAL
%token KW_RETURN
%token KW_STRING
%token KW_STRUCT
%token KW_SWITCH
%token KW_TRUE
%token KW_TYPE
%token KW_VAR
%token KW_VOID
%token KW_WHILE

%%

program : thing { Trace("Reducing", "thing", "program"); }
        ;

thing : thing thing
      | ID { Trace("Reducing", get_token_name(ID), "thing") }
      | INTEGER_LITERAL { Trace("Reducing", get_token_name(INTEGER_LITERAL), "thing") }
      | REAL_LITERAL { Trace("Reducing", get_token_name(REAL_LITERAL), "thing") }
      | STRING_LITERAL { Trace("Reducing", get_token_name(STRING_LITERAL), "thing") }
      | COMMA { Trace("Reducing", get_token_name(COMMA), "thing") }
      | COLON { Trace("Reducing", get_token_name(COLON), "thing") }
      | SEMICOLON { Trace("Reducing", get_token_name(SEMICOLON), "thing") }
      | LEFT_PARENTHESIS { Trace("Reducing", get_token_name(LEFT_PARENTHESIS), "thing") }
      | RIGHT_PARENTHESIS { Trace("Reducing", get_token_name(RIGHT_PARENTHESIS), "thing") }
      | LEFT_SQUARE_BRACKET { Trace("Reducing", get_token_name(LEFT_SQUARE_BRACKET), "thing") }
      | RIGHT_SQUARE_BRACKET { Trace("Reducing", get_token_name(RIGHT_SQUARE_BRACKET), "thing") }
      | LEFT_BRACKET { Trace("Reducing", get_token_name(LEFT_BRACKET), "thing") }
      | RIGHT_BRACKET { Trace("Reducing", get_token_name(RIGHT_BRACKET), "thing") }
      | OP_ADDITION { Trace("Reducing", get_token_name(OP_ADDITION), "thing") }
      | OP_SUBTRACTION { Trace("Reducing", get_token_name(OP_SUBTRACTION), "thing") }
      | OP_DIVISION { Trace("Reducing", get_token_name(OP_DIVISION), "thing") }
      | OP_MULTIPLICATION { Trace("Reducing", get_token_name(OP_MULTIPLICATION), "thing") }
      | OP_REMAINDER { Trace("Reducing", get_token_name(OP_REMAINDER), "thing") }
      | OP_EXPONENTIATION { Trace("Reducing", get_token_name(OP_EXPONENTIATION), "thing") }
      | OP_EQUAL_TO { Trace("Reducing", get_token_name(OP_EQUAL_TO), "thing") }
      | OP_NOT_EQUAL_TO { Trace("Reducing", get_token_name(OP_NOT_EQUAL_TO), "thing") }
      | OP_GREATER_THAN { Trace("Reducing", get_token_name(OP_GREATER_THAN), "thing") }
      | OP_LESS_THAN { Trace("Reducing", get_token_name(OP_LESS_THAN), "thing") }
      | OP_GREATER_THAN_OR_EQUAL_TO { Trace("Reducing", get_token_name(OP_GREATER_THAN_OR_EQUAL_TO), "thing") }
      | OP_LESS_THAN_OR_EQUAL_TO { Trace("Reducing", get_token_name(OP_LESS_THAN_OR_EQUAL_TO), "thing") }
      | OP_LOGICAL_AND { Trace("Reducing", get_token_name(OP_LOGICAL_AND), "thing") }
      | OP_LOGICAL_OR { Trace("Reducing", get_token_name(OP_LOGICAL_OR), "thing") }
      | OP_LOGICAL_NOT { Trace("Reducing", get_token_name(OP_LOGICAL_NOT), "thing") }
      | OP_ASSIGNMENT { Trace("Reducing", get_token_name(OP_ASSIGNMENT), "thing") }
      | OP_ADDITION_ASSIGNMENT { Trace("Reducing", get_token_name(OP_ADDITION_ASSIGNMENT), "thing") }
      | OP_SUBTRACTION_ASSIGNMENT { Trace("Reducing", get_token_name(OP_SUBTRACTION_ASSIGNMENT), "thing") }
      | OP_MULTIPLICATION_ASSIGNMENT { Trace("Reducing", get_token_name(OP_MULTIPLICATION_ASSIGNMENT), "thing") }
      | OP_DIVISION_ASSIGNMENT { Trace("Reducing", get_token_name(OP_DIVISION_ASSIGNMENT), "thing") }
      | KW_BOOL { Trace("Reducing", get_token_name(KW_BOOL), "thing") }
      | KW_BREAK { Trace("Reducing", get_token_name(KW_BREAK), "thing") }
      | KW_CASE { Trace("Reducing", get_token_name(KW_CASE), "thing") }
      | KW_CONST { Trace("Reducing", get_token_name(KW_CONST), "thing") }
      | KW_CONTINUE { Trace("Reducing", get_token_name(KW_CONTINUE), "thing") }
      | KW_DEFAULT { Trace("Reducing", get_token_name(KW_DEFAULT), "thing") }
      | KW_ELSE { Trace("Reducing", get_token_name(KW_ELSE), "thing") }
      | KW_FALSE { Trace("Reducing", get_token_name(KW_FALSE), "thing") }
      | KW_FOR { Trace("Reducing", get_token_name(KW_FOR), "thing") }
      | KW_FUNC { Trace("Reducing", get_token_name(KW_FUNC), "thing") }
      | KW_GO { Trace("Reducing", get_token_name(KW_GO), "thing") }
      | KW_IF { Trace("Reducing", get_token_name(KW_IF), "thing") }
      | KW_IMPORT { Trace("Reducing", get_token_name(KW_IMPORT), "thing") }
      | KW_INT { Trace("Reducing", get_token_name(KW_INT), "thing") }
      | KW_NIL { Trace("Reducing", get_token_name(KW_NIL), "thing") }
      | KW_PRINT { Trace("Reducing", get_token_name(KW_PRINT), "thing") }
      | KW_PRINTLN { Trace("Reducing", get_token_name(KW_PRINTLN), "thing") }
      | KW_REAL { Trace("Reducing", get_token_name(KW_REAL), "thing") }
      | KW_RETURN { Trace("Reducing", get_token_name(KW_RETURN), "thing") }
      | KW_STRING { Trace("Reducing", get_token_name(KW_STRING), "thing") }
      | KW_STRUCT { Trace("Reducing", get_token_name(KW_STRUCT), "thing") }
      | KW_SWITCH { Trace("Reducing", get_token_name(KW_SWITCH), "thing") }
      | KW_TRUE { Trace("Reducing", get_token_name(KW_TRUE), "thing") }
      | KW_TYPE { Trace("Reducing", get_token_name(KW_TYPE), "thing") }
      | KW_VAR { Trace("Reducing", get_token_name(KW_VAR), "thing") }
      | KW_VOID { Trace("Reducing", get_token_name(KW_VOID), "thing") }
      | KW_WHILE { Trace("Reducing", get_token_name(KW_WHILE), "thing") }
      ;

%%

#include "lex.yy.c"

int yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    return 0;
}

int main(int argc, char **argv) {
    init_symbol_table();
    yyparse();
    return 0;
}
