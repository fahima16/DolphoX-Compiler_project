#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ast.h"
#include "symbol_table.h"

void analyze_semantics(ASTNode *node, SymbolTable *table);
int get_semantic_errors(void);

#endif