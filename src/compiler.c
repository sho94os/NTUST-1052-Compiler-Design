#include <stdlib.h>
#include <stdio.h>

#include <llvm-c/Transforms/Scalar.h>

#include "y.tab.c"
#include "ast.h"
#include "codegen.h"

#include "support/make_executable_from_ll.c"

int main(int argc, char **argv) {
    /* Process arguments. */
    int mode = 0;
    char *output_file_name = (char*)"a.out";
    char *input_file_name = NULL;

    int next_arg_type = 0;
    for (int i = 1; i < argc; ++i) {
        char *arg = argv[i];

        if (strcmp(arg, "--llvm") == 0) {
            mode = 1;
        } else if (strcmp(arg, "-o") == 0) {
            next_arg_type = 1;
        } else if (next_arg_type == 1) {
            output_file_name = arg;
        } else {
            input_file_name = arg;
        }
    }

    if (input_file_name) {
        yyin = fopen(input_file_name, "r");
        if (!yyin) {
            fprintf(stderr, "Error: Cannot open file: %s\n", input_file_name);
            exit(-1);
        }
    } else {
        yyin = stdin;
    }

    /* Create LLVM module and builder. */
    LLVMModuleRef module = LLVMModuleCreateWithName("go");
    LLVMBuilderRef builder = LLVMCreateBuilder();

    /* Setup optimizations. */
    LLVMPassManagerRef pass_manager =  LLVMCreateFunctionPassManagerForModule(module);
    LLVMAddPromoteMemoryToRegisterPass(pass_manager);

    /* Start parser. */
    init_symtab();
    init_idtab();
    yyparse();

    /* Generate code. */
    codegen(ast_root, idtab, module, builder);

    /* Do output. */
    if (mode == 1) {
        char *ir = LLVMPrintModuleToString(module);
        printf("%s", ir);
    } else {
        const char *tmp_ll_file_path = "/tmp/__tmp.ll";
        FILE *ll_tmp_f = fopen(tmp_ll_file_path, "w");
        if (!ll_tmp_f) {
            fprintf(stderr, "Error: Cannot open temporary file: %s\n", tmp_ll_file_path);
            exit(-1);
        }
        char *ir = LLVMPrintModuleToString(module);
        fprintf(ll_tmp_f, "%s", ir);

        fclose(ll_tmp_f);

        make_executable_from_ll(tmp_ll_file_path, output_file_name);
        remove(tmp_ll_file_path);
    }

    /* Dispose. */
    LLVMDisposePassManager(pass_manager);
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);

    return 0;
}

