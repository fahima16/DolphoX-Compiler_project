#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include "../ast/ast.h"

// Generate C code from AST
void generate_c_code(ASTNode *node, FILE *out);
void generate_cpp_code(ASTNode *node, FILE *out);
void generate_python_code(ASTNode *node, FILE *out, int indent);
void generate_java_code(ASTNode *node, FILE *out, int indent);

#endif