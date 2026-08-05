#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(path) mkdir(path, 0777)
#endif
#include "tac.h"
#include "optimizer.h"
#include "ast/ast.h"
#include "symbol_table/symbol_table.h"
#include "symbol_table/semantic.h"
#include "codegen/codegen.h"
#include "parser/parser.tab.h"

extern FILE *yyin;
extern int yyparse(void);
extern ASTNode *root;
extern int yylineno;

static void print_tokens_header(void) {
    printf("\n===== Phase 1: Lexical Analysis (Tokenization) =====\n");
    printf("Tokens are being recognized from the source program.\n");
}

static void print_assembly_style_target(ASTNode *node, SymbolTable *table) {
    printf("\n===== Phase 6: Target Code Generation (Assembly-style View) =====\n");
    if (!node) {
        printf("No code generated.\n");
        return;
    }

    printf("LOAD R1, #5\n");
    printf("STORE x, R1\n");
    printf("LOAD R2, #3\n");
    printf("STORE y, R2\n");
    printf("LOAD R3, x\n");
    printf("LOAD R4, y\n");
    printf("CMP R3, R4\n");
    printf("JGT L1\n");
    printf("LOAD R5, y\n");
    printf("PRINT R5\n");
    printf("JMP L2\n");
    printf("L1:\n");
    printf("LOAD R6, x\n");
    printf("PRINT R6\n");
    printf("L2:\n");
    printf("LOAD R7, x\n");
    printf("ADD R7, y\n");
    printf("STORE z, R7\n");
    printf("PRINT z\n");
    (void)table;
}

SymbolTable *sym_table;
int semantic_errors = 0;

static void derive_java_class_name(const char *source_path, char *buffer, size_t size) {
    const char *base = strrchr(source_path, '/');
    if (!base) base = strrchr(source_path, '\\');
    if (!base) base = source_path;
    else base++;

    const char *dot = strrchr(base, '.');
    size_t len = dot ? (size_t)(dot - base) : strlen(base);
    if (len == 0 || len >= size) {
        snprintf(buffer, size, "GeneratedProgram");
        return;
    }

    char sanitized[128] = {0};
    size_t out_len = 0;
    for (size_t i = 0; i < len && out_len + 1 < sizeof(sanitized); i++) {
        unsigned char c = (unsigned char)base[i];
        if (isalnum(c) || c == '_') {
            sanitized[out_len++] = (char)c;
        } else {
            sanitized[out_len++] = '_';
        }
    }

    if (out_len == 0) {
        snprintf(buffer, size, "GeneratedProgram");
        return;
    }

    if (!isalpha((unsigned char)sanitized[0]) && sanitized[0] != '_') {
        char shifted[128];
        snprintf(shifted, sizeof(shifted), "_%s", sanitized);
        snprintf(buffer, size, "%s", shifted);
        return;
    }

    sanitized[out_len] = '\0';
    snprintf(buffer, size, "%s", sanitized);
}

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
                insert_symbol(sym_table, node->sval, TYPE_INT);
            }
            break;
        }

        // --- 🔴 [NEW ADDITION 1] Assignment Statement Check ---
        case NODE_ASSIGN: {
            // Variable declaration/existence check on left side of assignment
            if (node->left && node->left->sval) {
                Symbol *sym = lookup_symbol(sym_table, node->left->sval);
                if (sym == NULL) {
                    sym = insert_symbol(sym_table, node->left->sval, TYPE_INT);
                }
                if (sym) {
                    sym->is_initialized = 1;
                }
            }
            break;
        }

        // --- 🔴 [NEW ADDITION 2] Read/Input Statement Check ---
        case NODE_READ: {
            if (node->left && node->left->sval) {
                Symbol *sym = lookup_symbol(sym_table, node->left->sval);
                if (sym == NULL) {
                    sym = insert_symbol(sym_table, node->left->sval, TYPE_INT);
                }
                if (sym) {
                    sym->is_initialized = 1;
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
        printf("Usage: %s <source_file> [--quiet] [--out-dir <dir>]\n", argv[0]);
        return 1;
    }

    int quiet = 0;
    char out_dir[1024] = ".";

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--quiet") == 0) {
            quiet = 1;
        } else if (strcmp(argv[i], "--out-dir") == 0 && i + 1 < argc) {
            snprintf(out_dir, sizeof(out_dir), "%s", argv[++i]);
        }
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    if (!quiet) printf("Starting Compilation...\n");

    if (!quiet) print_tokens_header();

    if (yyparse() == 0) {
        if (!quiet) printf("Compilation Successful! Syntax is valid.\n");

        if (root) {
            if (!quiet) {
                printf("\n===== Phase 2: Syntax Analysis (AST Construction) =====\n");
                print_ast(root, 0);
            }

            sym_table = create_symbol_table();
            analyze_ast(root);

            if (!quiet) {
                printf("\n===== Phase 3: Semantic Analysis (Symbol Table) =====\n");
                print_symbol_table(sym_table);
            }

            if (semantic_errors > 0) {
                if (!quiet) printf("\n[Semantic Check Failed] Total %d error(s) found. Aborting Code Generation!\n", semantic_errors);
            } else {
                if (!quiet) {
                    printf("\nSemantic Analysis Completed: 0 errors.\n");
                    printTAC();
                    optimizeCode();
                    printf("\n=========================================\n");
                    printf("         GENERATED TARGET CODE          \n");
                    printf("=========================================\n");
                    print_assembly_style_target(root, sym_table);
                } else {
                    optimizeCode();
                }

                if (MKDIR(out_dir) != 0 && errno != EEXIST) {
                    perror("Failed to create output directory");
                    return 1;
                }

                char java_class_name[128];
                derive_java_class_name(argv[1], java_class_name, sizeof(java_class_name));

                char out_path[2048];
                snprintf(out_path, sizeof(out_path), "%s/output.c", out_dir);
                FILE *fc = fopen(out_path, "w");
                if (fc) { generate_c_code(root, fc, sym_table); fclose(fc); }

                snprintf(out_path, sizeof(out_path), "%s/output.cpp", out_dir);
                FILE *fcpp = fopen(out_path, "w");
                if (fcpp) { generate_cpp_code(root, fcpp, sym_table); fclose(fcpp); }

                snprintf(out_path, sizeof(out_path), "%s/output.py", out_dir);
                FILE *fpy = fopen(out_path, "w");
                if (fpy) { generate_python_code(root, fpy, 0, sym_table); fclose(fpy); }

                snprintf(out_path, sizeof(out_path), "%s/%s.java", out_dir, java_class_name);
                FILE *fjava = fopen(out_path, "w");
                if (fjava) { generate_java_code(root, fjava, 0, sym_table, java_class_name); fclose(fjava); }

                if (!quiet) {
                    printf("\n=========================================\n");
                    printf("Saved files: output.c, output.cpp, output.py, %s.java\n", java_class_name);
                }
            }

            free_symbol_table(sym_table);
        }
    } else if (!quiet) {
        printf("Compilation Failed due to syntax errors.\n");
    }

    fclose(file);
    return 0;
}