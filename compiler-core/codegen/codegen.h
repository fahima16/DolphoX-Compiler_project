#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../ast/ast.h"
#include "../symbol_table/symbol_table.h"

/* Main Code Generation Functions for Target Languages */
void generate_c_code(ASTNode *node, FILE *out, SymbolTable *table);
void generate_cpp_code(ASTNode *node, FILE *out, SymbolTable *table);
void generate_python_code(ASTNode *node, FILE *out, int indent, SymbolTable *table);
void generate_java_code(ASTNode *node, FILE *out, int indent, SymbolTable *table);

/* Utility Helper Function to print indentation for Python & Java */
void print_indentation(FILE *out, int indent);

#endif /* CODEGEN_H */