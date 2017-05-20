%{
#include "lex.yy.c"
#include "ast.h"

#ifdef STANDALONE_PARSER
#else
#endif

ast_node_t* ast_root;
%}

%locations

%start program

%union {
    int   integer;
    char* string;
    ast_node_t* ast_node;
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

/** Nonterminals **/

%type<ast_node> program
%type<ast_node> things
%type<ast_node> thing

%%

program : things { $$ = new_ast_node(program, @$.first_line, @$.first_column); ast_node_insert_child($$, $1); ast_root = $$; }
        ;

things : thing { $$ = new_ast_node(things, @$.first_line, @$.first_column); ast_node_insert_child($$, $1); }
       | thing things { $$ = new_ast_node(things, @$.first_line, @$.first_column); ast_node_insert_child($$, $1); ast_node_insert_child($$, $2); }
       ;

thing : ID { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(ID)); }
      | INTEGER_LITERAL { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(INTEGER_LITERAL)); }
      | REAL_LITERAL { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(REAL_LITERAL)); }
      | STRING_LITERAL { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(STRING_LITERAL)); }
      | COMMA { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(COMMA)); }
      | COLON { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(COLON)); }
      | SEMICOLON { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(SEMICOLON)); }
      | LEFT_PARENTHESIS { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(LEFT_PARENTHESIS)); }
      | RIGHT_PARENTHESIS { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(RIGHT_PARENTHESIS)); }
      | LEFT_SQUARE_BRACKET { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(LEFT_SQUARE_BRACKET)); }
      | RIGHT_SQUARE_BRACKET { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(RIGHT_SQUARE_BRACKET)); }
      | LEFT_BRACKET { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(LEFT_BRACKET)); }
      | RIGHT_BRACKET { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(RIGHT_BRACKET)); }
      | OP_ADDITION { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_ADDITION)); }
      | OP_SUBTRACTION { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_SUBTRACTION)); }
      | OP_DIVISION { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_DIVISION)); }
      | OP_MULTIPLICATION { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_MULTIPLICATION)); }
      | OP_REMAINDER { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_REMAINDER)); }
      | OP_EXPONENTIATION { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_EXPONENTIATION)); }
      | OP_EQUAL_TO { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_EQUAL_TO)); }
      | OP_NOT_EQUAL_TO { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_NOT_EQUAL_TO)); }
      | OP_GREATER_THAN { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_GREATER_THAN)); }
      | OP_LESS_THAN { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_LESS_THAN)); }
      | OP_GREATER_THAN_OR_EQUAL_TO { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_GREATER_THAN_OR_EQUAL_TO)); }
      | OP_LESS_THAN_OR_EQUAL_TO { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_LESS_THAN_OR_EQUAL_TO)); }
      | OP_LOGICAL_AND { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_LOGICAL_AND)); }
      | OP_LOGICAL_OR { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_LOGICAL_OR)); }
      | OP_LOGICAL_NOT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_LOGICAL_NOT)); }
      | OP_ASSIGNMENT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_ASSIGNMENT)); }
      | OP_ADDITION_ASSIGNMENT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_ADDITION_ASSIGNMENT)); }
      | OP_SUBTRACTION_ASSIGNMENT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_SUBTRACTION_ASSIGNMENT)); }
      | OP_MULTIPLICATION_ASSIGNMENT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_MULTIPLICATION_ASSIGNMENT)); }
      | OP_DIVISION_ASSIGNMENT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(OP_DIVISION_ASSIGNMENT)); }
      | KW_BOOL { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_BOOL)); }
      | KW_BREAK { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_BREAK)); }
      | KW_CASE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_CASE)); }
      | KW_CONST { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_CONST)); }
      | KW_CONTINUE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_CONTINUE)); }
      | KW_DEFAULT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_DEFAULT)); }
      | KW_ELSE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_ELSE)); }
      | KW_FALSE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_FALSE)); }
      | KW_FOR { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_FOR)); }
      | KW_FUNC { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_FUNC)); }
      | KW_GO { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_GO)); }
      | KW_IF { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_IF)); }
      | KW_IMPORT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_IMPORT)); }
      | KW_INT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_INT)); }
      | KW_NIL { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_NIL)); }
      | KW_PRINT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_PRINT)); }
      | KW_PRINTLN { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_PRINTLN)); }
      | KW_REAL { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_REAL)); }
      | KW_RETURN { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_RETURN)); }
      | KW_STRING { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_STRING)); }
      | KW_STRUCT { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_STRUCT)); }
      | KW_SWITCH { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_SWITCH)); }
      | KW_TRUE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_TRUE)); }
      | KW_TYPE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_TYPE)); }
      | KW_VAR { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_VAR)); }
      | KW_VOID { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_VOID)); }
      | KW_WHILE { $$ = new_ast_node(thing, @$.first_line, @$.first_column); ast_node_set_value_string($$, get_token_name(KW_WHILE)); }
      ;

%%

int yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    return 0;
}
