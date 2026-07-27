#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"
#include "symbol_table/symbol_table.h"
#include "codegen/codegen.h"

extern FILE *yyin;
extern int yyparse();
extern ASTNode *root;

SymbolTable *sym_table;
int semantic_errors = 0;

// Traverses AST to populate Symbol Table & run semantic checks
void analyze_ast(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_DECLARATION:
            if (insert_symbol(sym_table, node->sval, TYPE_INT) == NULL) {
                printf("Semantic Error: Redeclaration of variable '%s'\n", node->sval);
                semantic_errors++;
            }
            break;

        case NODE_VAR:
            if (lookup_symbol(sym_table, node->sval) == NULL) {
                printf("Semantic Error: Variable '%s' used before declaration\n", node->sval);
                semantic_errors++;
            }
            break;

        case NODE_ARRAY_DECL:
            if (insert_symbol(sym_table, node->sval, TYPE_INT) == NULL) {
                printf("Semantic Error: Redeclaration of array '%s'\n", node->sval);
                semantic_errors++;
            } else {
                Symbol *sym = lookup_symbol(sym_table, node->sval);
                if (sym) sym->is_array = 1;
            }
            break;

        default:
            break;
    }

    // Recursively check children and siblings
    analyze_ast(node->left);
    analyze_ast(node->right);
    analyze_ast(node->cond);
    analyze_ast(node->init);
    analyze_ast(node->incr);
    analyze_ast(node->body);
    analyze_ast(node->else_body);
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

            if (semantic_errors > 0) {
                printf("\nSemantic Analysis Failed with %d error(s).\n", semantic_errors);
            } else {
                printf("\nSemantic Analysis Completed: 0 errors.\n");

                // --- Terminal Output for All Target Languages ---
                printf("\n=========================================\n");
                printf("        GENERATED TARGET CODE            \n");
                printf("=========================================\n");

                printf("\n--- Generated C Code ---\n");
                generate_c_code(root, stdout);

                printf("\n--- Generated C++ Code ---\n");
                generate_cpp_code(root, stdout);

                printf("\n--- Generated Python Code ---\n");
                generate_python_code(root, stdout, 0);

                printf("\n--- Generated Java Code ---\n");
                generate_java_code(root, stdout, 0);

                // --- Save Target Code to File Outputs ---
                FILE *fc = fopen("output.c", "w");
                if (fc) { generate_c_code(root, fc); fclose(fc); }

                FILE *fcpp = fopen("output.cpp", "w");
                if (fcpp) { generate_cpp_code(root, fcpp); fclose(fcpp); }

                FILE *fpy = fopen("output.py", "w");
                if (fpy) { generate_python_code(root, fpy, 0); fclose(fpy); }

                FILE *fjava = fopen("Output.java", "w");
                if (fjava) { generate_java_code(root, fjava, 0); fclose(fjava); }

                printf("\n=========================================\n");
                printf("Saved files: output.c, output.cpp, output.py, Output.java\n");
            }
        }
    } else {
        printf("Compilation Failed due to syntax errors.\n");
    }

    fclose(file);
    return 0;
}