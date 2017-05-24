#include <stdio.h>
#define STANDALONE_SCANNER
#include "lex.yy.c"

int main(int argc, char **argv) {
    init_symtab();
    yylex();

    printf("\nSymbol Table:\n");
    printf("%s", symtab_dump_str(symtab));

    exit(0);
}
