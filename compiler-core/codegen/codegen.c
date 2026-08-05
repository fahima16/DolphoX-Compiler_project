#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

// Helper function to handle indentation
static void print_indent(FILE *out, int indent) {
    for (int i = 0; i < indent; i++) {
        fprintf(out, "    ");
    }
}

// Forward declarations
static void gen_expr_c(ASTNode *node, FILE *out, SymbolTable *table);
static void gen_expr_cpp(ASTNode *node, FILE *out, SymbolTable *table);
static void gen_expr_python(ASTNode *node, FILE *out, SymbolTable *table);
static void gen_expr_java(ASTNode *node, FILE *out, SymbolTable *table);

// Helper functions for expression generation without trailing newlines/semicolons

static void gen_expr_c(ASTNode *node, FILE *out, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;
        case NODE_VAR:
            fprintf(out, "%s", node->sval ? node->sval : "var");
            break;
        case NODE_BINARY_OP:
            gen_expr_c(node->left, out, table);
            fprintf(out, " %s ", node->op ? node->op : "+");
            gen_expr_c(node->right, out, table);
            break;
        case NODE_FUNCTION_CALL:
            fprintf(out, "%s(", node->sval ? node->sval : "func");
            {
                ASTNode *arg = node->left;
                while (arg) {
                    gen_expr_c(arg, out, table);
                    if (arg->next) fprintf(out, ", ");
                    arg = arg->next;
                }
            }
            fprintf(out, ")");
            break;
        case NODE_ASSIGN:
            gen_expr_c(node->left, out, table);
            fprintf(out, " = ");
            gen_expr_c(node->right, out, table);
            break;
        default:
            break;
    }
}

static void gen_expr_cpp(ASTNode *node, FILE *out, SymbolTable *table) {
    gen_expr_c(node, out, table);
}

static void gen_expr_python(ASTNode *node, FILE *out, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;
        case NODE_VAR:
            fprintf(out, "%s", node->sval ? node->sval : "var");
            break;
        case NODE_BINARY_OP:
            gen_expr_python(node->left, out, table);
            fprintf(out, " %s ", node->op ? node->op : "+");
            gen_expr_python(node->right, out, table);
            break;
        case NODE_FUNCTION_CALL:
            fprintf(out, "%s(", node->sval ? node->sval : "func");
            {
                ASTNode *arg = node->left;
                while (arg) {
                    gen_expr_python(arg, out, table);
                    if (arg->next) fprintf(out, ", ");
                    arg = arg->next;
                }
            }
            fprintf(out, ")");
            break;
        case NODE_ASSIGN:
            gen_expr_python(node->left, out, table);
            fprintf(out, " = ");
            gen_expr_python(node->right, out, table);
            break;
        default:
            break;
    }
}

static void gen_expr_java(ASTNode *node, FILE *out, SymbolTable *table) {
    gen_expr_c(node, out, table);
}

// === C Code Generator ===
void generate_c_code_indent(ASTNode *node, FILE *out, int indent, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM: {
            fprintf(out, "#include <stdio.h>\n\n");
            
            // First pass: generate functions outside main
            ASTNode *curr = node->body ? node->body : node->left;
            while (curr) {
                if (curr->type == NODE_FUNCTION_DEF) {
                    generate_c_code_indent(curr, out, 0, table);
                    fprintf(out, "\n");
                }
                curr = curr->next;
            }

            // Second pass: generate main function content
            fprintf(out, "int main() {\n");
            curr = node->body ? node->body : node->left;
            while (curr) {
                if (curr->type != NODE_FUNCTION_DEF) {
                    generate_c_code_indent(curr, out, 1, table);
                }
                curr = curr->next;
            }
            fprintf(out, "    return 0;\n}\n");
            return;
        }

        case NODE_READ:
            print_indent(out, indent);
            fprintf(out, "scanf(\"%%d\", &");
            gen_expr_c(node->left, out, table);
            fprintf(out, ");\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_DECLARATION:
            print_indent(out, indent);
            fprintf(out, "int %s;\n", node->sval ? node->sval : "var");
            if (table && node->sval) {
                insert_symbol(table, node->sval, TYPE_INT);
            }
            break;

        case NODE_ASSIGN:
            print_indent(out, indent);
            gen_expr_c(node->left, out, table);
            fprintf(out, " = ");
            gen_expr_c(node->right, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            print_indent(out, indent);
            fprintf(out, "if (");
            gen_expr_c(node->cond, out, table);
            fprintf(out, ") ");
            generate_c_code_indent(node->body, out, indent, table);
            if (node->else_body) {
                print_indent(out, indent);
                fprintf(out, "else ");
                generate_c_code_indent(node->else_body, out, indent, table);
            }
            break;

        case NODE_WHILE:
            print_indent(out, indent);
            fprintf(out, "while (");
            gen_expr_c(node->cond, out, table);
            fprintf(out, ") ");
            generate_c_code_indent(node->body, out, indent, table);
            break;

        case NODE_FOR:
            print_indent(out, indent);
            fprintf(out, "for (");
            if (node->init) gen_expr_c(node->init, out, table);
            fprintf(out, "; ");
            if (node->cond) gen_expr_c(node->cond, out, table);
            fprintf(out, "; ");
            if (node->incr) gen_expr_c(node->incr, out, table);
            fprintf(out, ") ");
            generate_c_code_indent(node->body, out, indent, table);
            break;

        case NODE_PRINT:
            print_indent(out, indent);
            fprintf(out, "printf(\"%%d\\n\", ");
            gen_expr_c(node->left, out, table);
            fprintf(out, ");\n");
            break;

        case NODE_FUNCTION_DEF:
            print_indent(out, indent);
            fprintf(out, "int %s(", node->sval ? node->sval : "func");
            if (node->left) {
                ASTNode *param = node->left;
                while (param) {
                    fprintf(out, "int %s", param->sval ? param->sval : "p");
                    if (param->next) fprintf(out, ", ");
                    param = param->next;
                }
            }
            fprintf(out, ") {\n");
            generate_c_code_indent(node->right, out, indent + 1, table);
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        case NODE_FUNCTION_CALL:
            print_indent(out, indent);
            gen_expr_c(node, out, table);
            fprintf(out, ";\n");
            break;

        case NODE_RETURN:
            print_indent(out, indent);
            fprintf(out, "return");
            if (node->left) {
                fprintf(out, " ");
                gen_expr_c(node->left, out, table);
            }
            fprintf(out, ";\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            {
                ASTNode *stmt = node->body ? node->body : node->left;
                while (stmt) {
                    generate_c_code_indent(stmt, out, indent + 1, table);
                    stmt = stmt->next;
                }
            }
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        default:
            break;
    }
}

void generate_c_code(ASTNode *node, FILE *out, SymbolTable *table) {
    generate_c_code_indent(node, out, 0, table);
}

// === C++ Code Generator ===
void generate_cpp_code_indent(ASTNode *node, FILE *out, int indent, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM: {
            fprintf(out, "#include <iostream>\nusing namespace std;\n\n");
            
            ASTNode *curr = node->body ? node->body : node->left;
            while (curr) {
                if (curr->type == NODE_FUNCTION_DEF) {
                    generate_cpp_code_indent(curr, out, 0, table);
                    fprintf(out, "\n");
                }
                curr = curr->next;
            }

            fprintf(out, "int main() {\n");
            curr = node->body ? node->body : node->left;
            while (curr) {
                if (curr->type != NODE_FUNCTION_DEF) {
                    generate_cpp_code_indent(curr, out, 1, table);
                }
                curr = curr->next;
            }
            fprintf(out, "    return 0;\n}\n");
            return;
        }

        case NODE_READ:
            print_indent(out, indent);
            fprintf(out, "cin >> ");
            gen_expr_cpp(node->left, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_DECLARATION:
            print_indent(out, indent);
            fprintf(out, "int %s;\n", node->sval ? node->sval : "var");
            if (table && node->sval) {
                insert_symbol(table, node->sval, TYPE_INT);
            }
            break;

        case NODE_ASSIGN:
            print_indent(out, indent);
            gen_expr_cpp(node->left, out, table);
            fprintf(out, " = ");
            gen_expr_cpp(node->right, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            print_indent(out, indent);
            fprintf(out, "if (");
            gen_expr_cpp(node->cond, out, table);
            fprintf(out, ") ");
            generate_cpp_code_indent(node->body, out, indent, table);
            if (node->else_body) {
                print_indent(out, indent);
                fprintf(out, "else ");
                generate_cpp_code_indent(node->else_body, out, indent, table);
            }
            break;

        case NODE_WHILE:
            print_indent(out, indent);
            fprintf(out, "while (");
            gen_expr_cpp(node->cond, out, table);
            fprintf(out, ") ");
            generate_cpp_code_indent(node->body, out, indent, table);
            break;

        case NODE_FOR:
            print_indent(out, indent);
            fprintf(out, "for (");
            if (node->init) gen_expr_cpp(node->init, out, table);
            fprintf(out, "; ");
            if (node->cond) gen_expr_cpp(node->cond, out, table);
            fprintf(out, "; ");
            if (node->incr) gen_expr_cpp(node->incr, out, table);
            fprintf(out, ") ");
            generate_cpp_code_indent(node->body, out, indent, table);
            break;

        case NODE_PRINT:
            print_indent(out, indent);
            fprintf(out, "cout << ");
            gen_expr_cpp(node->left, out, table);
            fprintf(out, " << endl;\n");
            break;

        case NODE_FUNCTION_DEF:
            print_indent(out, indent);
            fprintf(out, "int %s(", node->sval ? node->sval : "func");
            if (node->left) {
                ASTNode *param = node->left;
                while (param) {
                    fprintf(out, "int %s", param->sval ? param->sval : "p");
                    if (param->next) fprintf(out, ", ");
                    param = param->next;
                }
            }
            fprintf(out, ") {\n");
            generate_cpp_code_indent(node->right, out, indent + 1, table);
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        case NODE_FUNCTION_CALL:
            print_indent(out, indent);
            gen_expr_cpp(node, out, table);
            fprintf(out, ";\n");
            break;

        case NODE_RETURN:
            print_indent(out, indent);
            fprintf(out, "return");
            if (node->left) {
                fprintf(out, " ");
                gen_expr_cpp(node->left, out, table);
            }
            fprintf(out, ";\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            {
                ASTNode *stmt = node->body ? node->body : node->left;
                while (stmt) {
                    generate_cpp_code_indent(stmt, out, indent + 1, table);
                    stmt = stmt->next;
                }
            }
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        default:
            break;
    }
}

void generate_cpp_code(ASTNode *node, FILE *out, SymbolTable *table) {
    generate_cpp_code_indent(node, out, 0, table);
}

// === Python Code Generator ===
void generate_python_code(ASTNode *node, FILE *out, int indent, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM: {
            ASTNode *curr = node->body ? node->body : node->left;
            while (curr) {
                generate_python_code(curr, out, indent, table);
                curr = curr->next;
            }
            return;
        }

        case NODE_READ:
            print_indent(out, indent);
            gen_expr_python(node->left, out, table);
            fprintf(out, " = int(input())\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_DECLARATION:
            print_indent(out, indent);
            fprintf(out, "%s = 0\n", node->sval ? node->sval : "var");
            if (table && node->sval) {
                insert_symbol(table, node->sval, TYPE_INT);
            }
            break;

        case NODE_ASSIGN:
            print_indent(out, indent);
            gen_expr_python(node->left, out, table);
            fprintf(out, " = ");
            gen_expr_python(node->right, out, table);
            fprintf(out, "\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            print_indent(out, indent);
            fprintf(out, "if ");
            gen_expr_python(node->cond, out, table);
            fprintf(out, ":\n");
            generate_python_code(node->body, out, indent + 1, table);
            if (node->else_body) {
                print_indent(out, indent);
                fprintf(out, "else:\n");
                generate_python_code(node->else_body, out, indent + 1, table);
            }
            break;

        case NODE_WHILE:
            print_indent(out, indent);
            fprintf(out, "while ");
            gen_expr_python(node->cond, out, table);
            fprintf(out, ":\n");
            generate_python_code(node->body, out, indent + 1, table);
            break;

        case NODE_FOR:
            print_indent(out, indent);
            fprintf(out, "for ");
            if (node->init && node->init->left) {
                gen_expr_python(node->init->left, out, table);
            } else {
                fprintf(out, "i");
            }
            fprintf(out, " in range(");
            if (node->init && node->init->right) {
                gen_expr_python(node->init->right, out, table);
            } else {
                fprintf(out, "0");
            }
            fprintf(out, ", ");
            if (node->cond) {
                // If cond is a binary op like `i < 10`, extract the right operand
                if (node->cond->type == NODE_BINARY_OP && node->cond->right) {
                    gen_expr_python(node->cond->right, out, table);
                } else {
                    gen_expr_python(node->cond, out, table);
                }
            } else {
                fprintf(out, "10");
            }
            fprintf(out, "):\n");
            generate_python_code(node->body, out, indent + 1, table);
            break;

        case NODE_PRINT:
            print_indent(out, indent);
            fprintf(out, "print(");
            gen_expr_python(node->left, out, table);
            fprintf(out, ")\n");
            break;

        case NODE_FUNCTION_DEF:
            print_indent(out, indent);
            fprintf(out, "def %s(", node->sval ? node->sval : "func");
            if (node->left) {
                ASTNode *param = node->left;
                while (param) {
                    if (param->sval) fprintf(out, "%s", param->sval);
                    if (param->next) fprintf(out, ", ");
                    param = param->next;
                }
            }
            fprintf(out, "):\n");
            generate_python_code(node->right, out, indent + 1, table);
            break;

        case NODE_FUNCTION_CALL:
            print_indent(out, indent);
            gen_expr_python(node, out, table);
            fprintf(out, "\n");
            break;

        case NODE_RETURN:
            print_indent(out, indent);
            fprintf(out, "return");
            if (node->left) {
                fprintf(out, " ");
                gen_expr_python(node->left, out, table);
            }
            fprintf(out, "\n");
            break;

        case NODE_BLOCK: {
            ASTNode *stmt = node->body ? node->body : node->left;
            while (stmt) {
                generate_python_code(stmt, out, indent, table);
                stmt = stmt->next;
            }
            break;
        }

        default:
            break;
    }
}

// === Java Code Generator ===
void generate_java_code(ASTNode *node, FILE *out, int indent, SymbolTable *table, const char *class_name) {
    if (!node) return;

    const char *java_class_name = class_name && class_name[0] ? class_name : "GeneratedProgram";

    switch (node->type) {
        case NODE_PROGRAM: {
            fprintf(out, "import java.util.Scanner;\n\npublic class %s {\n", java_class_name);
            
            // First pass: generate static methods outside main
            ASTNode *curr = node->body ? node->body : node->left;
            while (curr) {
                if (curr->type == NODE_FUNCTION_DEF) {
                    generate_java_code(curr, out, 1, table, java_class_name);
                    fprintf(out, "\n");
                }
                curr = curr->next;
            }

            // Second pass: generate main method
            fprintf(out, "    public static void main(String[] args) {\n");
            fprintf(out, "        Scanner scanner = new Scanner(System.in);\n");
            
            curr = node->body ? node->body : node->left;
            while (curr) {
                if (curr->type != NODE_FUNCTION_DEF) {
                    generate_java_code(curr, out, 2, table, java_class_name);
                }
                curr = curr->next;
            }
            
            fprintf(out, "        scanner.close();\n");
            fprintf(out, "    }\n}\n");
            return;
        }

        case NODE_READ:
            print_indent(out, indent);
            gen_expr_java(node->left, out, table);
            fprintf(out, " = scanner.nextInt();\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_DECLARATION:
            print_indent(out, indent);
            fprintf(out, "int %s;\n", node->sval ? node->sval : "var");
            if (table && node->sval) {
                insert_symbol(table, node->sval, TYPE_INT);
            }
            break;

        case NODE_ASSIGN:
            print_indent(out, indent);
            gen_expr_java(node->left, out, table);
            fprintf(out, " = ");
            gen_expr_java(node->right, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            print_indent(out, indent);
            fprintf(out, "if (");
            gen_expr_java(node->cond, out, table);
            fprintf(out, ") ");
            generate_java_code(node->body, out, indent, table, java_class_name);
            if (node->else_body) {
                print_indent(out, indent);
                fprintf(out, "else ");
                generate_java_code(node->else_body, out, indent, table, java_class_name);
            }
            break;

        case NODE_WHILE:
            print_indent(out, indent);
            fprintf(out, "while (");
            gen_expr_java(node->cond, out, table);
            fprintf(out, ") ");
            generate_java_code(node->body, out, indent, table, java_class_name);
            break;

        case NODE_FOR:
            print_indent(out, indent);
            fprintf(out, "for (");
            if (node->init) gen_expr_java(node->init, out, table);
            fprintf(out, "; ");
            if (node->cond) gen_expr_java(node->cond, out, table);
            fprintf(out, "; ");
            if (node->incr) gen_expr_java(node->incr, out, table);
            fprintf(out, ") ");
            generate_java_code(node->body, out, indent, table, java_class_name);
            break;

        case NODE_PRINT:
            print_indent(out, indent);
            fprintf(out, "System.out.println(");
            gen_expr_java(node->left, out, table);
            fprintf(out, ");\n");
            break;

        case NODE_FUNCTION_DEF:
            print_indent(out, indent);
            fprintf(out, "public static int %s(", node->sval ? node->sval : "func");
            if (node->left) {
                ASTNode *param = node->left;
                while (param) {
                    fprintf(out, "int %s", param->sval ? param->sval : "p");
                    if (param->next) fprintf(out, ", ");
                    param = param->next;
                }
            }
            fprintf(out, ") {\n");
            generate_java_code(node->right, out, indent + 1, table, java_class_name);
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        case NODE_FUNCTION_CALL:
            print_indent(out, indent);
            gen_expr_java(node, out, table);
            fprintf(out, ";\n");
            break;

        case NODE_RETURN:
            print_indent(out, indent);
            fprintf(out, "return");
            if (node->left) {
                fprintf(out, " ");
                gen_expr_java(node->left, out, table);
            }
            fprintf(out, ";\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            {
                ASTNode *stmt = node->body ? node->body : node->left;
                while (stmt) {
                    generate_java_code(stmt, out, indent + 1, table, java_class_name);
                    stmt = stmt->next;
                }
            }
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        default:
            break;
    }
}