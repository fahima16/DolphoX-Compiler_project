#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

static int semantic_errors = 0;

void analyze_semantics(ASTNode *node, SymbolTable *table) {
    if (!node || !table) return;

    switch (node->type) {
        case NODE_PROGRAM:
            analyze_semantics(node->body ? node->body : node->left, table);
            break;

        case NODE_DECLARATION:
            if (node->sval) {
                // Check if symbol is already declared in current scope
                if (lookup_symbol_current_scope(table, node->sval) != NULL) {
                    fprintf(stderr, "[Semantic Error] Variable '%s' is already declared in this scope!\n", node->sval);
                    semantic_errors++;
                } else {
                    insert_symbol(table, node->sval, TYPE_INT);
                }
            }
            break;

        case NODE_VAR:
            if (node->sval) {
                Symbol *sym = lookup_symbol(table, node->sval);
                if (!sym) {
                    fprintf(stderr, "[Semantic Error] Variable '%s' used without declaration!\n", node->sval);
                    semantic_errors++;
                }
            }
            break;

        case NODE_ASSIGN:
            // Check right-hand expression first
            if (node->right) {
                analyze_semantics(node->right, table);
            }

            // Check left-hand variable
            if (node->left) {
                if (node->left->type == NODE_VAR && node->left->sval) {
                    Symbol *sym = lookup_symbol(table, node->left->sval);
                    if (!sym) {
                        fprintf(stderr, "[Semantic Error] Cannot assign to undeclared variable '%s'!\n", node->left->sval);
                        semantic_errors++;
                    } else {
                        sym->is_initialized = 1;
                    }
                } else {
                    analyze_semantics(node->left, table);
                }
            }
            break;

        case NODE_READ:
            if (node->left && node->left->sval) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (!sym) {
                    fprintf(stderr, "[Semantic Error] Cannot read into undeclared variable '%s'!\n", node->left->sval);
                    semantic_errors++;
                } else {
                    sym->is_initialized = 1;
                }
            }
            break;

        case NODE_PRINT:
            if (node->left) {
                analyze_semantics(node->left, table);
            }
            break;

        case NODE_IF:
            if (node->cond) analyze_semantics(node->cond, table);
            
            enter_scope(table);
            if (node->left) analyze_semantics(node->left, table);
            else if (node->body) analyze_semantics(node->body, table);
            exit_scope(table);

            if (node->right) {
                enter_scope(table);
                analyze_semantics(node->right, table);
                exit_scope(table);
            }
            break;

        case NODE_WHILE:
            if (node->cond) analyze_semantics(node->cond, table);
            
            enter_scope(table);
            analyze_semantics(node->body ? node->body : node->left, table);
            exit_scope(table);
            break;

        case NODE_BLOCK:
            enter_scope(table);
            analyze_semantics(node->body ? node->body : node->left, table);
            exit_scope(table);
            break;

        case NODE_BINARY_OP:
            if (node->left) analyze_semantics(node->left, table);
            if (node->right) analyze_semantics(node->right, table);
            break;

        default:
            break;
    }

    // Traverse next statement in sequence
    if (node->type != NODE_PROGRAM && node->next) {
        analyze_semantics(node->next, table);
    }
}

int get_semantic_errors(void) {
    return semantic_errors;
}