%{
#include "lex.yy.c"
#include "symbol_table.h"
#include "ast.h"

#ifdef STANDALONE_PARSER
#else
#endif

ast_node_t* ann(ast_node_type_t type, YYLTYPE loc) { return new_ast_node(type, loc.first_line, loc.first_column); }
void vsym(ast_node_t *node, symbol_table_entry_t *v) { ast_node_set_value_symbol(node, v); }
void vint(ast_node_t *node, int v) { ast_node_set_value_integer(node, v); }
void vstr(ast_node_t *node, char *v) { ast_node_set_value_string(node, v); }
void ich(ast_node_t *node, ast_node_t *child) { ast_node_insert_child(node, child); }

ast_node_t* ast_root;
bool has_error = false;
%}

%locations

%start program

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

%type <ast_node> program
%type <symbol> identifier
%type <ast_node> function_def
%type <ast_node> function_body
%type <ast_node> statement
%type <ast_node> println_statement
%type <ast_node> expression
%type <ast_node> string_constant

%%

/** Program **/

program : program function_def { $$ = $1; ich($$, $2); }
        | { $$ = ann(program, @$); ast_root = $$; }
        ;

/** Identifier **/

identifier : ID { $$ = $1; } ;

/** Functions **/

function_def : KW_FUNC identifier LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET function_body RIGHT_BRACKET { $$ = ann(function_def, @$); vsym($$, $2); ich($$, $6); } ;

function_body : function_body statement { $$ = $1; ich($$, $2); }
              | { $$ = ann(function_body, @$); }
              ;

/** Statements **/

statement : println_statement
          ;

println_statement : KW_PRINTLN expression { $$ = ann(println_statement, @$); ich($$, $2); }
                  | KW_PRINTLN LEFT_PARENTHESIS expression RIGHT_PARENTHESIS { $$ = ann(println_statement, @$); ich($$, $3); }
                  ;

/** Expressions **/

expression : string_constant { $$ = ann(expression, @$); ich($$, $1); }
           ;

/** Constants **/

string_constant : STRING_LITERAL { $$ = ann(string_constant, @$); vstr($$, yylval.string); } ;

%%

int yyerror(char *msg) {
    fprintf(stderr, "%s around line %d, cloumn %d\n", msg, yylloc.first_line, yylloc.first_column);
    has_error = true;
    return 0;
}
