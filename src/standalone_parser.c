#include <stdio.h>
#define STANDALONE_PARSER
#include "y.tab.c"

int main(int argc, char **argv) {
    init_symbol_table();
    yyparse();

    printf("\nAST:\n");
    printf("%s\n", ast_dump_str(ast_root));

    printf("\nAST Graphviz Diagram:\n");
    printf("%s\n", ast_dump_graphviz(ast_root));

    exit(0);
}
