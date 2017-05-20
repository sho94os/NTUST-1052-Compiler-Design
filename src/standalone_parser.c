#include <stdio.h>
#define STANDALONE_PARSER
#include "y.tab.c"

int main(int argc, char **argv) {
    init_symbol_table();
    yyparse();

    int format = 0;

    for (int i = 0; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "--graphviz") == 0) format = 1;
    }

    switch (format) {
        case 0:
            printf("%s", ast_dump_str(ast_root));
            break;
        case 1:
            printf("%s", ast_dump_graphviz(ast_root));
            break;
    }

    exit(0);
}
