#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"
#include "symbol_table/symbol_table.h"
#include "symbol_table/semantic.h" // <<< NEW: Semantic module Include
#include "codegen/codegen.h"
#include "parser/parser.tab.h"

extern FILE *yyin;
extern int yyparse(void);
extern ASTNode *root;

SymbolTable *sym_table;
int semantic_errors = 0;

// Traverses AST to populate Symbol Table & run semantic checks
void analyze_ast(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        // --- [SAME AS BEFORE] Variable Declaration ---
        case NODE_DECLARATION: {
            DataType type = TYPE_UNKNOWN;
            if (node->left) {
                type = token_to_data_type(node->left->ival);
            }
            if (insert_symbol(sym_table, node->sval, type) == NULL) {
                printf("Semantic Error: Redeclaration of variable '%s'\n", node->sval);
                semantic_errors++;
            }
            break;
        }

        // --- [SAME AS BEFORE] Array Declaration ---
        case NODE_ARRAY_DECL: {
            DataType type = TYPE_UNKNOWN;
            if (node->left) {
                type = token_to_data_type(node->left->ival);
            }
            if (insert_array_symbol(sym_table, node->sval, type, node->ival) == NULL) {
                printf("Semantic Error: Redeclaration of array '%s'\n", node->sval);
                semantic_errors++;
            }
            break;
        }

        // --- [SAME AS BEFORE] Variable Use Check ---
        case NODE_VAR: {
            if (lookup_symbol(sym_table, node->sval) == NULL) {
                printf("Semantic Error: Variable '%s' used before declaration\n", node->sval);
                semantic_errors++;
            }
            break;
        }

        // --- 🔴 [NEW ADDITION 1] Assignment Statement Check ---
        case NODE_ASSIGN: {
            // Variable declaration/existence check on left side of assignment
            if (node->left && node->left->sval) {
                Symbol *sym = lookup_symbol(sym_table, node->left->sval);
                if (sym == NULL) {
                    printf("Semantic Error: Assignment to undeclared variable '%s'\n", node->left->sval);
                    semantic_errors++;
                } else {
                    sym->is_initialized = 1; // <<< NEW: Mark variable as initialized
                }
            }
            break;
        }

        // --- 🔴 [NEW ADDITION 2] Read/Input Statement Check ---
        case NODE_READ: {
            if (node->left && node->left->sval) {
                Symbol *sym = lookup_symbol(sym_table, node->left->sval);
                if (sym == NULL) {
                    printf("Semantic Error: Read target '%s' is not declared\n", node->left->sval);
                    semantic_errors++;
                } else {
                    sym->is_initialized = 1; // <<< NEW: Mark variable as initialized after read
                }
            }
            break;
        }

        default:
            break;
    }

    /* Traversal: Don't visit 'left' on declarations since 'left' holds the data type token */
    if (node->type != NODE_DECLARATION && node->type != NODE_ARRAY_DECL) {
        analyze_ast(node->left);
    }

    /* Standard AST traversal using valid structure members */
    analyze_ast(node->right);
    analyze_ast(node->next);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    printf("Starting Compilation...\n");

    if (yyparse() == 0) {
        printf("Compilation Successful! Syntax is valid.\n");

        if (root) {
            printf("\n=== Abstract Syntax Tree (AST) ===\n");
            print_ast(root, 0);

            // Initialize and populate Symbol Table
            sym_table = create_symbol_table();
            analyze_ast(root);

            printf("\n=== Symbol Table ===\n");
            print_symbol_table(sym_table);

            // -----------------------------------------------------------------
            // 🔴 [NEW ADDITION 3] Code Generation Guard
            // If semantic_errors > 0, stop and do not generate target codes.
            // -----------------------------------------------------------------
            if (semantic_errors > 0) {
                printf("\n[Semantic Check Failed] Total %d error(s) found. Aborting Code Generation!\n", semantic_errors);
            } else {
                printf("\nSemantic Analysis Completed: 0 errors.\n");

                // --- Terminal Output for All Target Languages ---
                printf("\n=========================================\n");
                printf("         GENERATED TARGET CODE          \n");
                printf("=========================================\n");

                printf("\n--- Generated C Code ---\n");
                generate_c_code(root, stdout, sym_table);

                printf("\n--- Generated C++ Code ---\n");
                generate_cpp_code(root, stdout, sym_table);

                printf("\n--- Generated Python Code ---\n");
                generate_python_code(root, stdout, 0, sym_table);

                printf("\n--- Generated Java Code ---\n");
                generate_java_code(root, stdout, 0, sym_table);

                // --- Save Target Code to File Outputs ---
                FILE *fc = fopen("output.c", "w");
                if (fc) { generate_c_code(root, fc, sym_table); fclose(fc); }

                FILE *fcpp = fopen("output.cpp", "w");
                if (fcpp) { generate_cpp_code(root, fcpp, sym_table); fclose(fcpp); }

                FILE *fpy = fopen("output.py", "w");
                if (fpy) { generate_python_code(root, fpy, 0, sym_table); fclose(fpy); }

                FILE *fjava = fopen("Output.java", "w");
                if (fjava) { generate_java_code(root, fjava, 0, sym_table); fclose(fjava); }

                printf("\n=========================================\n");
                printf("Saved files: output.c, output.cpp, output.py, Output.java\n");
            }

            // Cleanup
            free_symbol_table(sym_table);
        }
    } else {
        printf("Compilation Failed due to syntax errors.\n");
    }

    fclose(file);
    return 0;
}