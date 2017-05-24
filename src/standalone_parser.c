#include <stdio.h>
#define STANDALONE_PARSER
#include "y.tab.c"

int main(int argc, char **argv) {
    init_symtab();
    init_idtab();
    yyparse();

    int format = 0;

    for (int i = 0; i < argc; ++i) {
        char *arg = argv[i];
        if (strcmp(arg, "--graphviz") == 0) format = 1;
    }

    switch (format) {
        case 0:
            printf("{\n  \"ast\": ");
            printf("%s", ast_dump_str_with_options(ast_root, 1) + 2);
            printf(",\n  \"ids\": ");
            printf("%s", idtab_dump_str_with_options(idtab, true, 1));
            printf("\n}\n");
            break;
        case 1:
            printf("%s", ast_dump_graphviz(ast_root));
            break;
    }

    if (has_error) {
        exit(1);
    } else {
        exit(0);
    }
}
