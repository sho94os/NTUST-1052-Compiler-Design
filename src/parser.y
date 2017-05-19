%{
#include <stdio.h>
#include "tokens.h"

#ifdef STANDALONE_PARSER
#else
#endif
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

program : thing {}
        ;

thing : thing thing
      | ID {}
      | INTEGER_LITERAL {}
      | REAL_LITERAL {}
      | STRING_LITERAL {}
      | COMMA {}
      | COLON {}
      | SEMICOLON {}
      | LEFT_PARENTHESIS {}
      | RIGHT_PARENTHESIS {}
      | LEFT_SQUARE_BRACKET {}
      | RIGHT_SQUARE_BRACKET {}
      | LEFT_BRACKET {}
      | RIGHT_BRACKET {}
      | OP_ADDITION {}
      | OP_SUBTRACTION {}
      | OP_DIVISION {}
      | OP_MULTIPLICATION {}
      | OP_REMAINDER {}
      | OP_EXPONENTIATION {}
      | OP_EQUAL_TO {}
      | OP_NOT_EQUAL_TO {}
      | OP_GREATER_THAN {}
      | OP_LESS_THAN {}
      | OP_GREATER_THAN_OR_EQUAL_TO {}
      | OP_LESS_THAN_OR_EQUAL_TO {}
      | OP_LOGICAL_AND {}
      | OP_LOGICAL_OR {}
      | OP_LOGICAL_NOT {}
      | OP_ASSIGNMENT {}
      | OP_ADDITION_ASSIGNMENT {}
      | OP_SUBTRACTION_ASSIGNMENT {}
      | OP_MULTIPLICATION_ASSIGNMENT {}
      | OP_DIVISION_ASSIGNMENT {}
      | KW_BOOL {}
      | KW_BREAK {}
      | KW_CASE {}
      | KW_CONST {}
      | KW_CONTINUE {}
      | KW_DEFAULT {}
      | KW_ELSE {}
      | KW_FALSE {}
      | KW_FOR {}
      | KW_FUNC {}
      | KW_GO {}
      | KW_IF {}
      | KW_IMPORT {}
      | KW_INT {}
      | KW_NIL {}
      | KW_PRINT {}
      | KW_PRINTLN {}
      | KW_REAL {}
      | KW_RETURN {}
      | KW_STRING {}
      | KW_STRUCT {}
      | KW_SWITCH {}
      | KW_TRUE {}
      | KW_TYPE {}
      | KW_VAR {}
      | KW_VOID {}
      | KW_WHILE {}
      ;

%%

#include "lex.yy.c"

int yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    return 0;
}
