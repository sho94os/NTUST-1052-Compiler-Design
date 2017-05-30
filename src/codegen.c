/*
 * codegen.c
 * Implementation of functions to generate LLVM IR for the AST.
 */

#include "codegen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokens.h"

#define CODEGEN_MAX_FUNCTION_PARAMS_COUNT 16

LLVMValueRef get_printf_function(LLVMModuleRef module) {
    LLVMValueRef func = LLVMGetNamedFunction(module, "printf");
    if (func) return func;
    LLVMTypeRef param_types[1] = { LLVMPointerType(LLVMInt8Type(), 0) };
    LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), param_types, 1, true);
    func = LLVMAddFunction(module, "printf", func_type);
    return func;
}

LLVMValueRef get_print_i32_function(LLVMModuleRef module) {
    LLVMValueRef func = LLVMGetNamedFunction(module, "__print_i32");
    if (func) return func;
    LLVMTypeRef param_types[1] = { LLVMInt32Type() };
    LLVMTypeRef func_type = LLVMFunctionType(LLVMVoidType(), param_types, 1, false);
    func = LLVMAddFunction(module, "__print_i32", func_type);
    LLVMBasicBlockRef block = LLVMAppendBasicBlock(func, "entry");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, block);
    LLVMValueRef printf_func = get_printf_function(module);
    LLVMValueRef printf_str_const = LLVMConstString("%d", 2, false);
    LLVMValueRef printf_str = LLVMAddGlobal(module, LLVMArrayType(LLVMInt8Type(), 3), "__print_i32_str");
    LLVMSetInitializer(printf_str, printf_str_const);
    LLVMValueRef gep_printf_str_indices[2] = { LLVMConstInt(LLVMInt32Type(), 0, false), LLVMConstInt(LLVMInt32Type(), 0, false) };
    LLVMValueRef gep_printf_str = LLVMBuildInBoundsGEP(builder, printf_str, gep_printf_str_indices, 2, "");
    LLVMValueRef printf_func_args[2] = { gep_printf_str, LLVMGetParam(func, 0) };
    LLVMBuildCall(builder, printf_func, printf_func_args, 2, "");
    LLVMBuildRetVoid(builder);
    return func;
}

LLVMValueRef get_println_i32_function(LLVMModuleRef module) {
    LLVMValueRef func = LLVMGetNamedFunction(module, "__println_i32");
    if (func) return func;
    LLVMTypeRef param_types[1] = { LLVMInt32Type() };
    LLVMTypeRef func_type = LLVMFunctionType(LLVMVoidType(), param_types, 1, false);
    func = LLVMAddFunction(module, "__println_i32", func_type);
    LLVMBasicBlockRef block = LLVMAppendBasicBlock(func, "entry");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, block);
    LLVMValueRef printf_func = get_printf_function(module);
    LLVMValueRef printf_str_const = LLVMConstString("%d\n", 3, false);
    LLVMValueRef printf_str = LLVMAddGlobal(module, LLVMArrayType(LLVMInt8Type(), 4), "__println_i32_str");
    LLVMSetInitializer(printf_str, printf_str_const);
    LLVMValueRef gep_printf_str_indices[2] = { LLVMConstInt(LLVMInt32Type(), 0, false), LLVMConstInt(LLVMInt32Type(), 0, false) };
    LLVMValueRef gep_printf_str = LLVMBuildInBoundsGEP(builder, printf_str, gep_printf_str_indices, 2, "");
    LLVMValueRef printf_func_args[2] = { gep_printf_str, LLVMGetParam(func, 0) };
    LLVMBuildCall(builder, printf_func, printf_func_args, 2, "");
    LLVMBuildRetVoid(builder);
    return func;
}

LLVMValueRef get_print_str_function(LLVMModuleRef module) {
    LLVMValueRef func = LLVMGetNamedFunction(module, "__print_str");
    if (func) return func;
    LLVMTypeRef param_types[1] = { LLVMPointerType(LLVMInt8Type(), 0) };
    LLVMTypeRef func_type = LLVMFunctionType(LLVMVoidType(), param_types, 1, false);
    func = LLVMAddFunction(module, "__print_str", func_type);
    LLVMBasicBlockRef block = LLVMAppendBasicBlock(func, "entry");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, block);
    LLVMValueRef printf_func = get_printf_function(module);
    LLVMValueRef printf_func_args[1] = { LLVMGetParam(func, 0) };
    LLVMBuildCall(builder, printf_func, printf_func_args, 1, "");
    LLVMBuildRetVoid(builder);
    return func;
}

LLVMValueRef get_println_str_function(LLVMModuleRef module) {
    LLVMValueRef func = LLVMGetNamedFunction(module, "__println_str");
    if (func) return func;
    LLVMTypeRef param_types[1] = { LLVMPointerType(LLVMInt8Type(), 0) };
    LLVMTypeRef func_type = LLVMFunctionType(LLVMVoidType(), param_types, 1, false);
    func = LLVMAddFunction(module, "__println_str", func_type);
    LLVMBasicBlockRef block = LLVMAppendBasicBlock(func, "entry");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, block);
    LLVMValueRef printf_func = get_printf_function(module);
    LLVMValueRef printf_func_args[1] = { LLVMGetParam(func, 0) };
    LLVMBuildCall(builder, printf_func, printf_func_args, 1, "");

    // Print '\n'
    LLVMValueRef printf_nl_str_const = LLVMConstString("\n", 3, false);
    LLVMValueRef printf_nl_str = LLVMAddGlobal(module, LLVMArrayType(LLVMInt8Type(), 4), "__println_str_nl_str");
    LLVMSetInitializer(printf_nl_str, printf_nl_str_const);
    LLVMValueRef gep_printf_nl_str_indices[2] = { LLVMConstInt(LLVMInt32Type(), 0, false), LLVMConstInt(LLVMInt32Type(), 0, false) };
    LLVMValueRef gep_printf_nl_str = LLVMBuildInBoundsGEP(builder, printf_nl_str, gep_printf_nl_str_indices, 2, "");
    LLVMValueRef printf_nl_func_args[1] = { gep_printf_nl_str };
    LLVMBuildCall(builder, printf_func, printf_nl_func_args, 1, "");

    LLVMBuildRetVoid(builder);
    return func;
}

LLVMTypeRef get_llvm_type_for_identifier(const idtab_entry_t *idtab_entry) {
    switch (idtab_entry->value_type) {
        case void_value_type:
            return LLVMVoidType();
            break;
        case bool_value_type:
            return LLVMInt32Type();
            break;
        case int_value_type:
            return LLVMInt32Type();
            break;
        case real_value_type:
            return LLVMInt32Type();
            break;
        case string_value_type:
            return LLVMInt32Type();
            break;
        case unknown_value_type:
            return LLVMVoidType();
            break;
    }
}

LLVMValueRef codegen_program(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    // Declare all global variables
    for (int i = 0; i < IDTAB_HASHTAB_SIZE; ++i) {
        idtab_entry_t *entry = idtab->entries[i];

        while (entry) {
            LLVMValueRef glob;
            switch (entry->value_type) {
                case integer:
                    glob = LLVMAddGlobal(module, LLVMInt32Type(), "glob_int");
                    entry->payload = (void*)glob;

                    // LLVM global must be initlized
                    LLVMSetInitializer(glob, LLVMConstInt(LLVMInt32Type(), 0, false));
                    break;
            }
            entry = entry->next;
        }
    }

    // Generate code for each child
    ast_node_t *current_child = ast_node->child;

    while (current_child) {
        codegen(current_child, idtab, module, builder);
        current_child = current_child->sibling;
    }

    return NULL;
}

LLVMValueRef codegen_func_def(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder)
{
    idtab_entry_t *idtab_entry = ast_node->value.identifier;
    // Param types
    LLVMTypeRef param_types[CODEGEN_MAX_FUNCTION_PARAMS_COUNT];
    int params_count = 0;
    ast_node_t *current_arg_node = ast_node->child->child;
    while (current_arg_node) {
        param_types[params_count] = get_llvm_type_for_identifier(current_arg_node->value.identifier);
        current_arg_node = current_arg_node->sibling;
        ++params_count;
    }

    // Create function type
    LLVMTypeRef funcType = LLVMFunctionType(get_llvm_type_for_identifier(idtab_entry), param_types, params_count, false);

    // Create function
    LLVMValueRef func = LLVMAddFunction(module, idtab_entry->identifier, funcType);
    idtab_entry->payload = (void*)func;

    // Create basic block for the function
    LLVMBasicBlockRef block = LLVMAppendBasicBlock(func, "entry");
    LLVMPositionBuilderAtEnd(builder, block);

    // Declare all local variables
    for (int i = 0; i < IDTAB_HASHTAB_SIZE; ++i) {
        idtab_entry_t *entry = idtab_entry->scoped_idtab->entries[i];

        while (entry) {
            if (entry->serial < LLVMCountParams(func)) {
                // Param
                LLVMValueRef param = LLVMGetParam(func, entry->serial);
                entry->payload = (void*)param;
            } else {
                // Local var
                switch (entry->value_type) {
                    case integer:
                        entry->payload = (void*)LLVMBuildAlloca(builder, LLVMInt32Type(), "var");
                        break;
                }
            }
            entry = entry->next;
        }
    }

    // Generate body
    codegen(ast_node_get_child(ast_node, 2), idtab_entry->scoped_idtab, module, builder);

    // Insert a return void instruction at the end of the function block
    if (idtab_entry->value_type == void_value_type) {
        LLVMBuildRetVoid(builder);
    } else {
        LLVMBuildRet(builder, LLVMGetUndef(get_llvm_type_for_identifier(idtab_entry)));
    }

    return func;
}

LLVMValueRef codegen_func_body(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    ast_node_t *current_child = ast_node->child;

    // Generate code for each child
    while (current_child) {
        codegen(current_child, idtab, module, builder);
        current_child = current_child->sibling;
    }

    return NULL;
}

LLVMValueRef codegen_var_dec(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    if (idtab->scope) {
        // Init local var
        if (ast_node->child) {
            LLVMValueRef val = codegen(ast_node->child, idtab, module, builder);
            LLVMValueRef var = (LLVMValueRef)ast_node->value.identifier->payload;

            return LLVMBuildStore(builder, val, var);
        }
    } else {
        // Init global var
        if (ast_node->child) {
            LLVMValueRef val = codegen(ast_node->child, idtab, module, builder);
            LLVMValueRef var = (LLVMValueRef)ast_node->value.identifier->payload;

            LLVMSetInitializer(var, val);
            return NULL;
        }
    }

    return NULL;
}

LLVMValueRef codegen_id(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMValueRef val = (LLVMValueRef)ast_node->value.identifier->payload;
    if (LLVMGetTypeKind(LLVMTypeOf(val)) == LLVMPointerTypeKind) {
        return LLVMBuildLoad(builder, val, "load_id");
    } else {
        return val;
    }
}

LLVMValueRef codegen_assign(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMValueRef var = (LLVMValueRef)ast_node->value.identifier->payload;
    LLVMValueRef val = codegen(ast_node->child, idtab, module, builder);
    return LLVMBuildStore(builder, val, var);
}

LLVMValueRef codegen_func_invo(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    ast_node_t *func_invo_args = ast_node_get_child(ast_node, 1);

    ast_node_t *current_func_invo_arg = ast_node_get_child(func_invo_args, 1);
    unsigned int func_invo_arg_count = 0;
    LLVMValueRef args[128];

    while (current_func_invo_arg) {
        args[func_invo_arg_count] = codegen(current_func_invo_arg, idtab, module, builder);
        ++func_invo_arg_count;
        current_func_invo_arg = current_func_invo_arg->sibling;
    }

    LLVMValueRef func = (LLVMValueRef)ast_node->value.identifier->payload;
    return LLVMBuildCall(builder, func, args, func_invo_arg_count, "");
}

LLVMValueRef codegen_print(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMValueRef func;

    LLVMValueRef args[1] = { codegen(ast_node_get_child(ast_node, 1), idtab, module, builder) };

    switch (LLVMGetTypeKind(LLVMTypeOf(args[0]))) {
        case LLVMIntegerTypeKind:
            func = get_print_i32_function(module);
            break;
        case LLVMPointerTypeKind:
            func = get_print_str_function(module);
            break;
    }

    return LLVMBuildCall(builder, func, args, 1, "");
}

LLVMValueRef codegen_println(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMValueRef func;

    LLVMValueRef args[1] = { codegen(ast_node_get_child(ast_node, 1), idtab, module, builder) };

    switch (LLVMGetTypeKind(LLVMTypeOf(args[0]))) {
        case LLVMIntegerTypeKind:
            func = get_println_i32_function(module);
            break;
        case LLVMPointerTypeKind:
            func = get_println_str_function(module);
            break;
    }

    return LLVMBuildCall(builder, func, args, 1, "");
}

LLVMValueRef codegen_return(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {

    if (ast_node->child) {
        // Generate return with value
        return LLVMBuildRet(builder, codegen(ast_node->child, idtab, module, builder));
    } else {
        // Generate return void
        return LLVMBuildRetVoid(builder);
    }
}

LLVMValueRef codegen_operation(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMValueRef lhs, rhs;

    switch (ast_node->value.operatr) {
        case operatr_unary:
            rhs = codegen(ast_node_get_child(ast_node, 1), idtab, module, builder);
            return LLVMBuildNeg(builder, rhs, "op");
            break;
        case operatr_not:
            break;
        case operatr_exponent:
            break;
        case operatr_multiply:
            lhs = codegen(ast_node_get_child(ast_node, 1), idtab, module, builder);
            rhs = codegen(ast_node_get_child(ast_node, 2), idtab, module, builder);
            return LLVMBuildMul(builder, lhs, rhs, "op");
            break;
        case operatr_divide:
            break;
        case operatr_remainder:
            break;
        case operatr_add:
            lhs = codegen(ast_node_get_child(ast_node, 1), idtab, module, builder);
            rhs = codegen(ast_node_get_child(ast_node, 2), idtab, module, builder);
            return LLVMBuildAdd(builder, lhs, rhs, "op");
            break;
        case operatr_subtract:
            lhs = codegen(ast_node_get_child(ast_node, 1), idtab, module, builder);
            rhs = codegen(ast_node_get_child(ast_node, 2), idtab, module, builder);
            return LLVMBuildSub(builder, lhs, rhs, "op");
            break;
        case operatr_equal_to:
            break;
        case operatr_not_equal_to:
            break;
        case operatr_greater_than:
            lhs = codegen(ast_node_get_child(ast_node, 1), idtab, module, builder);
            rhs = codegen(ast_node_get_child(ast_node, 2), idtab, module, builder);
            return LLVMBuildICmp(builder, LLVMIntSGT, lhs, rhs, "cmp");
            break;
        case operatr_less_than:
            break;
        case operatr_greater_than_or_equal_to:
            break;
        case operatr_less_than_or_equal_to:
            break;
        case operatr_binary_and:
            break;
        case operatr_binary_or:
            break;
        case operatr_logical_and:
            break;
        case operatr_logical_or:
            break;
    }

    return NULL;
}

LLVMValueRef codegen_condition(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    // Get elements
    LLVMValueRef current_func = (LLVMValueRef)idtab->scope->payload;
    LLVMValueRef cond = codegen(ast_node_get_child(ast_node, 1), idtab, module, builder);
    ast_node_t *ast_if_node, *ast_else_node;
    bool has_else = !!ast_node_get_child(ast_node, 3);
    ast_if_node = ast_node_get_child(ast_node, 2);
    if (has_else) ast_else_node = ast_node_get_child(ast_node, 2);

    // Prepare blocks
    LLVMBasicBlockRef if_block = LLVMAppendBasicBlock(current_func, "if");
    LLVMBasicBlockRef cont_block = LLVMAppendBasicBlock(current_func, "cont");
    LLVMBasicBlockRef else_block;

    if (has_else) {
        else_block = LLVMAppendBasicBlock(current_func, "else");
    } else {
        else_block = cont_block;
    }

    // Generate condition br
    LLVMValueRef cond_br = LLVMBuildCondBr(builder, cond, if_block, else_block);

    // Fill the if block
    LLVMPositionBuilderAtEnd(builder, if_block);
    codegen(ast_if_node, idtab, module, builder);
    LLVMBuildBr(builder, cont_block);

    // Fill the else block
    if (has_else) {
        LLVMPositionBuilderAtEnd(builder, else_block);
        codegen(ast_else_node, idtab, module, builder);
        LLVMBuildBr(builder, cont_block);
    }

    // Position the builder to the continuing block
    LLVMPositionBuilderAtEnd(builder, cont_block);

    return cond_br;
}

LLVMValueRef codegen_block(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    ast_node_t *current_child = ast_node->child;

    // Generate code for each child
    while (current_child) {
        codegen(current_child, idtab, module, builder);
        current_child = current_child->sibling;
    }

    return NULL;
}

LLVMValueRef codegen_integer_literal(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    return LLVMConstInt(LLVMInt32Type(), ast_node->value.integer, false);
}

LLVMValueRef codegen_string_literal(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    const char *str = ast_node->value.string;
    int str_length = strlen(str);
    LLVMValueRef str_glob = LLVMAddGlobal(module, LLVMArrayType(LLVMInt8Type(), str_length + 1), "string_literal");
    LLVMValueRef str_const = LLVMConstString(str, str_length, false);
    LLVMSetInitializer(str_glob, str_const);
    LLVMValueRef str_ptr_indices[2] = { LLVMConstInt(LLVMInt32Type(), 0, false), LLVMConstInt(LLVMInt32Type(), 0, false) };
    LLVMValueRef str_ptr = LLVMBuildInBoundsGEP(builder, str_glob, str_ptr_indices, 2, "");
    return str_ptr;
}

LLVMValueRef codegen(ast_node_t *ast_node, idtab_t *idtab, LLVMModuleRef module, LLVMBuilderRef builder) {
    switch (ast_node->type) {
        case ast_program:
            return codegen_program(ast_node, idtab, module, builder);
            break;
        case ast_func_def:
            return codegen_func_def(ast_node, idtab, module, builder);
            break;
        case ast_func_args:
            break;
        case ast_func_arg:
            break;
        case ast_func_body:
            return codegen_func_body(ast_node, idtab, module, builder);
            break;
        case ast_const_dec:
            break;
        case ast_var_dec:
            return codegen_var_dec(ast_node, idtab, module, builder);
            break;
        case ast_arr_dec:
            break;
        case ast_id:
            return codegen_id(ast_node, idtab, module, builder);
            break;
        case ast_assign:
            return codegen_assign(ast_node, idtab, module, builder);
            break;
        case ast_func_invo:
            return codegen_func_invo(ast_node, idtab, module, builder);
            break;
        case ast_func_invo_args:
            break;
        case ast_arr_assign:
            break;
        case ast_print:
            return codegen_print(ast_node, idtab, module, builder);
            break;
        case ast_println:
            return codegen_println(ast_node, idtab, module, builder);
            break;
        case ast_read:
            break;
        case ast_return:
            return codegen_return(ast_node, idtab, module, builder);
            break;
        case ast_operation:
            return codegen_operation(ast_node, idtab, module, builder);
            break;
        case ast_condition:
            return codegen_condition(ast_node, idtab, module, builder);
            break;
        case ast_for_loop:
            break;
        case ast_block:
            return codegen_block(ast_node, idtab, module, builder);
            break;
        case ast_integer_literal:
            return codegen_integer_literal(ast_node, idtab, module, builder);
            break;
        case ast_real_literal:
            break;
        case ast_string_literal:
            return codegen_string_literal(ast_node, idtab, module, builder);
            break;
        case ast_null:
        case ast_things:
        case ast_thing:
            break;
    }

    return NULL;
}
