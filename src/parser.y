%{
#include "lex.yy.c"
#include "symbol_table.h"
#include "ast.h"

#ifdef STANDALONE_PARSER
#else
#endif

/** Shorthands For Commonly Used Code **/
ast_node_t* n(ast_node_type_t t, YYLTYPE l) { return new_ast_node(t, l.first_line, l.first_column); }
void vsym(ast_node_t *n, symbol_table_entry_t *v) { ast_node_set_value_symbol(n, v); }
void vopt(ast_node_t *n, int v) { ast_node_set_value_operatr(n, v); }
void vint(ast_node_t *n, int v) { ast_node_set_value_integer(n, v); }
void vstr(ast_node_t *n, char *v) { ast_node_set_value_string(n, v); }
void ich(ast_node_t *n, ast_node_t *child) { ast_node_insert_child(n, child); }
void isb(ast_node_t *n, ast_node_t *sibling) { ast_node_insert_sibling(n, sibling); }

/** Globals **/
ast_node_t* ast_root;
bool has_error = false;
%}

/** Extensions **/

%locations

/** Start Rule **/

%start program

/** Type Definition **/

%union {
    symbol_table_entry_t* symbol;
    int                   integer;
    char*                 string;
    ast_node_t*           ast_node;
}

/** Identifier **/

%token <symbol> ID

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

%left <integer> OP_LOGICAL_OR
%left <integer> OP_LOGICAL_AND

%left <integer> OP_BINARY_AND OP_BINARY_OR

%left <integer> OP_NOT

%nonassoc <integer> OP_EQUAL_TO OP_NOT_EQUAL_TO
                    OP_GREATER_THAN OP_LESS_THAN
                    OP_GREATER_THAN_OR_EQUAL_TO OP_LESS_THAN_OR_EQUAL_TO

%left <integer> OP_ADDITION OP_SUBTRACTION
%left <integer> OP_MULTIPLICATION OP_DIVISION OP_REMAINDER
%right <integer> OP_EXPONENTIATION

%token <integer> OP_ASSIGNMENT

%token <integer> OP_ADDITION_ASSIGNMENT
%token <integer> OP_SUBTRACTION_ASSIGNMENT
%token <integer> OP_MULTIPLICATION_ASSIGNMENT
%token <integer> OP_DIVISION_ASSIGNMENT

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
%token KW_READ
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

/** Type Declarations **/

%type <symbol> id

%type <ast_node> program
%type <ast_node> id_eval
%type <ast_node> func_def
%type <ast_node> func_args
%type <ast_node> func_arg_list
%type <ast_node> func_arg
%type <ast_node> func_body
%type <ast_node> const_dec
%type <ast_node> var_dec
%type <ast_node> stmt
%type <ast_node> stmt_optional
%type <ast_node> assign_stmt
%type <ast_node> array_assign_stmt
%type <ast_node> func_invo_stmt
%type <ast_node> func_invo_args
%type <ast_node> func_invo_arg_list
%type <ast_node> func_invo_arg
%type <ast_node> print_stmt
%type <ast_node> println_stmt
%type <ast_node> read_stmt
%type <ast_node> return_stmt
%type <ast_node> expr
%type <ast_node> block
%type <ast_node> block_body
%type <ast_node> cond
%type <ast_node> cond_body
%type <ast_node> for_loop
%type <ast_node> loop_body
%type <ast_node> literals
%type <ast_node> integer_literal
%type <ast_node> real_literal
%type <ast_node> string_literal

%%

/** Program **/

program : program var_dec { ich($$, $2); }
        | program const_dec { ich($$, $2); }
        | program func_def { ich($$, $2); }
        | { $$ = n(ast_program, @$); ast_root = $$; }
        ;

/** Identifier **/

id : ID ;

id_eval : ID { $$ = n(ast_id, @$); vsym($$, $1); } ;

/** Types **/

type : KW_BOOL
     | KW_INT
     | KW_REAL
     | KW_STRING
     ;

type_including_void : type
                    | KW_VOID
                    ;

type_optional : type_including_void
              |
              ;

/** Functions **/

func_def :
    KW_FUNC type_including_void ID LEFT_PARENTHESIS func_args RIGHT_PARENTHESIS LEFT_BRACKET func_body RIGHT_BRACKET {
        $$ = n(ast_func_def, @$);
        vsym($$, $3);
        ich($$, $5);
        ich($$, $8);
        // TODO: Deal with the type
    }
|
    KW_FUNC ID LEFT_PARENTHESIS func_args RIGHT_PARENTHESIS LEFT_BRACKET func_body RIGHT_BRACKET {
        $$ = n(ast_func_def, @$);
        vsym($$, $2);
        ich($$, $4);
        ich($$, $7);
        // TODO: Set type to void
    }
;

func_args : func_arg_list { $$ = n(ast_func_args, @$); ich($$, $1); }
          | { $$ = n(ast_func_args, @$); }
          ;

func_arg_list : func_arg
              | func_arg_list COMMA func_arg { isb($$, $3); }
              ;

func_arg : id type {
    $$ = n(ast_func_arg, @$);
    vsym($$, $1);
    // TODO: Deal with the type
} ;

func_body : func_body var_dec { ich($$, $2); }
          | func_body const_dec { ich($$, $2); }
          | func_body stmt { ich($$, $2); }
          | { $$ = n(ast_func_body, @$); }
          ;

/** Constant Declarations **/

const_dec : KW_CONST id OP_ASSIGNMENT expr {
    $$ = n(ast_const_dec, @$);
    vsym($$, $2);
    ich($$, $4);
    // TODO: Deal with the type
} ;

/** Variable Declarations **/

var_dec :
    KW_VAR id type {
        $$ = n(ast_var_dec, @$);
        vsym($$, $2);
        // TODO: Deal with the type
    }
|
    KW_VAR id type OP_ASSIGNMENT expr {
        $$ = n(ast_var_dec, @$);
        vsym($$, $2);
        ich($$, $5);
        // TODO: Deal with the type
    }
|
    KW_VAR id LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET type {
        $$ = n(ast_arr_dec, @$);
        vsym($$, $2);
        ich($$, $4);
        // TODO: Deal with the type
    }
;

/** Statements **/

stmt : assign_stmt
     | array_assign_stmt
     | func_invo_stmt
     | print_stmt
     | println_stmt
     | read_stmt
     | return_stmt
     | cond
     | for_loop
     ;

stmt_optional : stmt
              | { $$ = n(ast_null, @$); }
              ;

assign_stmt :
    id OP_ASSIGNMENT expr {
        $$ = n(ast_assign, @$);
        vsym($$, $1);
        ich($$, $3);
    }
;

array_assign_stmt :
    id LEFT_SQUARE_BRACKET expr RIGHT_SQUARE_BRACKET OP_ASSIGNMENT expr {
        $$ = n(ast_arr_assign, @$);
        vsym($$, $1);
        ich($$, $3);
        ich($$, $6);
    }
;

func_invo_stmt :
    id LEFT_PARENTHESIS func_invo_args RIGHT_PARENTHESIS {
        $$ = n(ast_func_invo, @$);
        vsym($$, $1);
        ich($$, $3);
    }
;

func_invo_args : func_invo_arg_list { $$ = n(ast_func_invo_args, @$); ich($$, $1); }
               | { $$ = n(ast_func_invo_args, @$); }
               ;

func_invo_arg_list : func_invo_arg
                   | func_invo_arg_list COMMA func_invo_arg { isb($$, $3); }
                   ;

func_invo_arg : expr
              ;

print_stmt : KW_PRINT expr { $$ = n(ast_print, @$); ich($$, $2); } ;

println_stmt : KW_PRINTLN expr { $$ = n(ast_println, @$); ich($$, $2); } ;

read_stmt : KW_READ id { $$ = n(ast_read, @$); vsym($$, $2); } ;

return_stmt : KW_RETURN { $$ = n(ast_return, @$); }
            | KW_RETURN expr { $$ = n(ast_return, @$); ich($$, $2); }
            ;

/** Expressions **/

expr : LEFT_PARENTHESIS expr RIGHT_PARENTHESIS { $$ = $2; }
     | OP_SUBTRACTION expr { $$ = n(ast_operation, @$); vopt($$, $1); ich($$, $2); }
     | OP_NOT expr { $$ = n(ast_operation, @$); vopt($$, $1); ich($$, $2); }
     | expr OP_EXPONENTIATION expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_MULTIPLICATION expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_DIVISION expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_REMAINDER expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_ADDITION expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_SUBTRACTION expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_EQUAL_TO expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_NOT_EQUAL_TO expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_GREATER_THAN expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_LESS_THAN expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_GREATER_THAN_OR_EQUAL_TO expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_LESS_THAN_OR_EQUAL_TO expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_BINARY_AND expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_BINARY_OR expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_LOGICAL_AND expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | expr OP_LOGICAL_OR expr { $$ = n(ast_operation, @$); vopt($$, $2); ich($$, $1); ich($$, $3); }
     | assign_stmt
     | array_assign_stmt
     | func_invo_stmt
     | print_stmt
     | println_stmt
     | read_stmt
     | id_eval
     | literals
     ;

/** Block **/

block : LEFT_BRACKET block_body RIGHT_BRACKET { $$ = $2; }
      ;

block_body : block_body var_dec { ich($$, $2); }
           | block_body const_dec { ich($$, $2); }
           | block_body stmt { ich($$, $2); }
           | { $$ = n(ast_block, @$); }
           ;

/** Conditional **/

cond :
    KW_IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS cond_body {
        $$ = n(ast_condition, @$);
        ich($$, $3);
        ich($$, $5);
    }
|
    KW_IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS cond_body KW_ELSE cond_body {
        $$ = n(ast_condition, @$);
        ich($$, $3);
        ich($$, $5);
        ich($$, $7);
    }
;

cond_body : stmt
          | block
          ;

/** Loop **/

for_loop :
    KW_FOR LEFT_PARENTHESIS stmt_optional SEMICOLON expr SEMICOLON stmt_optional RIGHT_PARENTHESIS loop_body {
        $$ = n(ast_for_loop, @$);
        ich($$, $3);
        ich($$, $5);
        ich($$, $7);
        ich($$, $9);
    }
;

loop_body : stmt
          | block
          ;

/** Procedure Invocation **/

// TODO

/** Literals **/

literals : integer_literal
         | real_literal
         | string_literal
         ;

integer_literal : INTEGER_LITERAL { $$ = n(ast_integer, @$); vint($$, $1); } ;
real_literal :    REAL_LITERAL    { $$ = n(ast_real, @$);    vstr($$, $1); } ;
string_literal :  STRING_LITERAL  { $$ = n(ast_string, @$);  vstr($$, $1); } ;

%%

int yyerror(char *msg) {
    fprintf(stderr, "%s around line %d, cloumn %d\n", msg, yylloc.first_line, yylloc.first_column);
    has_error = true;
    return 0;
}
