/*
 * codegen.h
 * Declarations of functions to generate LLVM IR for the AST.
 */

#ifndef CODEGEN_H
#define CODEGEN_H

#include <llvm-c/Core.h>

#include "ast.h"

/* Recursively generates LLVM objects for an AST node. */
LLVMValueRef codegen(ast_node_t*, idtab_t*, LLVMModuleRef module, LLVMBuilderRef builder);

#endif


