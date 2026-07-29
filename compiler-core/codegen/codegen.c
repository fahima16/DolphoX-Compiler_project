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

// === C Code Generator ===
void generate_c_code(ASTNode *node, FILE *out, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "#include <stdio.h>\n\nint main() {\n");
            // If body exists use it, otherwise traverse directly from node->left or current node
            generate_c_code(node->body ? node->body : node->left, out, table);
            fprintf(out, "    return 0;\n}\n");
            return; // NODE_PROGRAM handles its children

        case NODE_READ:
            fprintf(out, "    scanf(\"%%d\", &");
            generate_c_code(node->left, out, table);
            fprintf(out, ");\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_DECLARATION:
            fprintf(out, "    int %s;\n", node->sval ? node->sval : "var");
            if (table && node->sval) {
                insert_symbol(table, node->sval, TYPE_INT);
            }
            break;

        case NODE_ASSIGN:
            fprintf(out, "    ");
            generate_c_code(node->left, out, table);
            fprintf(out, " = ");
            generate_c_code(node->right, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            fprintf(out, "    if (");
            generate_c_code(node->cond, out, table);
            fprintf(out, ") ");
            generate_c_code(node->left ? node->left : node->body, out, table);
            if (node->right) {
                fprintf(out, " else ");
                generate_c_code(node->right, out, table);
            }
            break;

        case NODE_WHILE:
            fprintf(out, "    while (");
            generate_c_code(node->cond, out, table);
            fprintf(out, ") ");
            generate_c_code(node->body ? node->body : node->left, out, table);
            break;

        case NODE_FOR:
            fprintf(out, "    for (");
            if (node->init) {
                generate_c_code(node->init->left, out, table);
                fprintf(out, " = ");
                generate_c_code(node->init->right, out, table);
            }
            fprintf(out, "; ");
            generate_c_code(node->cond, out, table);
            fprintf(out, "; ");
            generate_c_code(node->incr, out, table);
            fprintf(out, ") ");
            generate_c_code(node->body, out, table);
            break;

        case NODE_PRINT:
            fprintf(out, "    printf(\"%%d\\n\", ");
            generate_c_code(node->left, out, table);
            fprintf(out, ");\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            generate_c_code(node->body ? node->body : node->left, out, table);
            fprintf(out, "    }\n");
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_c_code(node->left, out, table);
                fprintf(out, " %s ", node->op ? node->op : "+");
                generate_c_code(node->right, out, table);
            } else {
                generate_c_code(node->left, out, table);
                if (node->op) fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval ? node->sval : "var");
            break;

        default:
            break;
    }

    // Traverse next statement
    if (node->type != NODE_PROGRAM) {
        generate_c_code(node->next, out, table);
    }
}

// === C++ Code Generator ===
void generate_cpp_code(ASTNode *node, FILE *out, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "#include <iostream>\nusing namespace std;\n\nint main() {\n");
            generate_cpp_code(node->body ? node->body : node->left, out, table);
            fprintf(out, "    return 0;\n}\n");
            return;

        case NODE_READ:
            fprintf(out, "    cin >> ");
            generate_cpp_code(node->left, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_DECLARATION:
            fprintf(out, "    int %s;\n", node->sval ? node->sval : "var");
            if (table && node->sval) {
                insert_symbol(table, node->sval, TYPE_INT);
            }
            break;

        case NODE_ASSIGN:
            fprintf(out, "    ");
            generate_cpp_code(node->left, out, table);
            fprintf(out, " = ");
            generate_cpp_code(node->right, out, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            fprintf(out, "    if (");
            generate_cpp_code(node->cond, out, table);
            fprintf(out, ") ");
            generate_cpp_code(node->left ? node->left : node->body, out, table);
            if (node->right) {
                fprintf(out, " else ");
                generate_cpp_code(node->right, out, table);
            }
            break;

        case NODE_WHILE:
            fprintf(out, "    while (");
            generate_cpp_code(node->cond, out, table);
            fprintf(out, ") ");
            generate_cpp_code(node->body ? node->body : node->left, out, table);
            break;

        case NODE_FOR:
            fprintf(out, "    for (");
            if (node->init) {
                generate_cpp_code(node->init->left, out, table);
                fprintf(out, " = ");
                generate_cpp_code(node->init->right, out, table);
            }
            fprintf(out, "; ");
            generate_cpp_code(node->cond, out, table);
            fprintf(out, "; ");
            generate_cpp_code(node->incr, out, table);
            fprintf(out, ") ");
            generate_cpp_code(node->body, out, table);
            break;

        case NODE_PRINT:
            fprintf(out, "    cout << ");
            generate_cpp_code(node->left, out, table);
            fprintf(out, " << endl;\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            generate_cpp_code(node->body ? node->body : node->left, out, table);
            fprintf(out, "    }\n");
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_cpp_code(node->left, out, table);
                fprintf(out, " %s ", node->op ? node->op : "+");
                generate_cpp_code(node->right, out, table);
            } else {
                generate_cpp_code(node->left, out, table);
                if (node->op) fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval ? node->sval : "var");
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM) {
        generate_cpp_code(node->next, out, table);
    }
}

// === Python Code Generator ===
void generate_python_code(ASTNode *node, FILE *out, int indent, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            generate_python_code(node->body ? node->body : node->left, out, indent, table);
            return;

        case NODE_READ:
            print_indent(out, indent);
            generate_python_code(node->left, out, 0, table);
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
            generate_python_code(node->left, out, 0, table);
            fprintf(out, " = ");
            generate_python_code(node->right, out, 0, table);
            fprintf(out, "\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            print_indent(out, indent);
            fprintf(out, "if ");
            generate_python_code(node->cond, out, 0, table);
            fprintf(out, ":\n");
            generate_python_code(node->left ? node->left : node->body, out, indent + 1, table);
            if (node->right) {
                print_indent(out, indent);
                fprintf(out, "else:\n");
                generate_python_code(node->right, out, indent + 1, table);
            }
            break;

        case NODE_WHILE:
            print_indent(out, indent);
            fprintf(out, "while ");
            generate_python_code(node->cond, out, 0, table);
            fprintf(out, ":\n");
            generate_python_code(node->body ? node->body : node->left, out, indent + 1, table);
            break;

        case NODE_FOR:
            print_indent(out, indent);
            fprintf(out, "for ");
            if (node->init) {
                generate_python_code(node->init->left, out, 0, table);
            } else {
                fprintf(out, "i");
            }
            fprintf(out, " in range(");
            if (node->init) {
                generate_python_code(node->init->right, out, 0, table);
            } else {
                fprintf(out, "0");
            }
            fprintf(out, ", ");
            if (node->cond) {
                generate_python_code(node->cond, out, 0, table);
            } else {
                fprintf(out, "10");
            }
            fprintf(out, "):\n");
            generate_python_code(node->body, out, indent + 1, table);
            break;

        case NODE_PRINT:
            print_indent(out, indent);
            fprintf(out, "print(");
            generate_python_code(node->left, out, 0, table);
            fprintf(out, ")\n");
            break;

        case NODE_BLOCK:
            generate_python_code(node->body ? node->body : node->left, out, indent, table);
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_python_code(node->left, out, 0, table);
                fprintf(out, " %s ", node->op ? node->op : "+");
                generate_python_code(node->right, out, 0, table);
            } else {
                generate_python_code(node->left, out, 0, table);
                if (node->op) fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval ? node->sval : "var");
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM) {
        generate_python_code(node->next, out, indent, table);
    }
}

// === Java Code Generator ===
void generate_java_code(ASTNode *node, FILE *out, int indent, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "import java.util.Scanner;\n\npublic class Output {\n");
            fprintf(out, "    public static void main(String[] args) {\n");
            fprintf(out, "        Scanner scanner = new Scanner(System.in);\n");
            generate_java_code(node->body ? node->body : node->left, out, 2, table);
            fprintf(out, "        scanner.close();\n");
            fprintf(out, "    }\n}\n");
            return;

        case NODE_READ:
            print_indent(out, indent);
            generate_java_code(node->left, out, 0, table);
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
            generate_java_code(node->left, out, 0, table);
            fprintf(out, " = ");
            generate_java_code(node->right, out, 0, table);
            fprintf(out, ";\n");
            if (node->left && node->left->sval && table) {
                Symbol *sym = lookup_symbol(table, node->left->sval);
                if (sym) sym->is_initialized = 1;
            }
            break;

        case NODE_IF:
            print_indent(out, indent);
            fprintf(out, "if (");
            generate_java_code(node->cond, out, 0, table);
            fprintf(out, ") ");
            generate_java_code(node->left ? node->left : node->body, out, indent, table);
            if (node->right) {
                fprintf(out, " else ");
                generate_java_code(node->right, out, indent, table);
            }
            break;

        case NODE_WHILE:
            print_indent(out, indent);
            fprintf(out, "while (");
            generate_java_code(node->cond, out, 0, table);
            fprintf(out, ") ");
            generate_java_code(node->body ? node->body : node->left, out, indent, table);
            break;

        case NODE_FOR:
            print_indent(out, indent);
            fprintf(out, "for (");
            if (node->init) {
                generate_java_code(node->init->left, out, 0, table);
                fprintf(out, " = ");
                generate_java_code(node->init->right, out, 0, table);
            }
            fprintf(out, "; ");
            generate_java_code(node->cond, out, 0, table);
            fprintf(out, "; ");
            generate_java_code(node->incr, out, 0, table);
            fprintf(out, ") ");
            generate_java_code(node->body, out, indent, table);
            break;

        case NODE_PRINT:
            print_indent(out, indent);
            fprintf(out, "System.out.println(");
            generate_java_code(node->left, out, 0, table);
            fprintf(out, ");\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            generate_java_code(node->body ? node->body : node->left, out, indent + 1, table);
            print_indent(out, indent);
            fprintf(out, "}\n");
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_java_code(node->left, out, 0, table);
                fprintf(out, " %s ", node->op ? node->op : "+");
                generate_java_code(node->right, out, 0, table);
            } else {
                generate_java_code(node->left, out, 0, table);
                if (node->op) fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval ? node->sval : "var");
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM) {
        generate_java_code(node->next, out, indent, table);
    }
}