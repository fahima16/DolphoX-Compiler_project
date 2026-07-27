#include "codegen.h"

// === C Code Generator ===
void generate_c_code(ASTNode *node, FILE *out) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "#include <stdio.h>\n\nint main() {\n");
            generate_c_code(node->body, out);
            fprintf(out, "    return 0;\n}\n");
            break;

        case NODE_READ:
            fprintf(out, "    scanf(\"%%d\", &");
            generate_c_code(node->left, out);
            fprintf(out, ");\n");
            break;

        case NODE_DECLARATION:
            fprintf(out, "    int %s;\n", node->sval);
            break;

        case NODE_ASSIGN:
            fprintf(out, "    ");
            generate_c_code(node->left, out);
            fprintf(out, " = ");
            generate_c_code(node->right, out);
            fprintf(out, ";\n");
            break;

        case NODE_FOR:
            fprintf(out, "    for (");
            if (node->init && node->init->type == NODE_ASSIGN) {
                generate_c_code(node->init->left, out);
                fprintf(out, " = ");
                generate_c_code(node->init->right, out);
            }
            fprintf(out, "; ");
            generate_c_code(node->cond, out);
            fprintf(out, "; ");
            generate_c_code(node->incr, out);
            fprintf(out, ") ");
            generate_c_code(node->body, out);
            break;

        case NODE_PRINT:
            fprintf(out, "    printf(\"%%d\\n\", ");
            generate_c_code(node->left, out);
            fprintf(out, ");\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            generate_c_code(node->body, out);
            fprintf(out, "    }\n");
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_c_code(node->left, out);
                fprintf(out, " %s ", node->op);
                generate_c_code(node->right, out);
            } else {
                generate_c_code(node->left, out);
                fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval);
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM && node->type != NODE_FOR && node->type != NODE_BLOCK) {
        generate_c_code(node->next, out);
    }
}

// === C++ Code Generator ===
void generate_cpp_code(ASTNode *node, FILE *out) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "#include <iostream>\nusing namespace std;\n\nint main() {\n");
            generate_cpp_code(node->body, out);
            fprintf(out, "    return 0;\n}\n");
            break;
            
        case NODE_READ:
            fprintf(out, "    cin >> ");
            generate_cpp_code(node->left, out);
            fprintf(out, ";\n");
            break;

        case NODE_DECLARATION:
            fprintf(out, "    int %s;\n", node->sval);
            break;

        case NODE_ASSIGN:
            fprintf(out, "    ");
            generate_cpp_code(node->left, out);
            fprintf(out, " = ");
            generate_cpp_code(node->right, out);
            fprintf(out, ";\n");
            break;

        case NODE_FOR:
            fprintf(out, "    for (");
            if (node->init && node->init->type == NODE_ASSIGN) {
                generate_cpp_code(node->init->left, out);
                fprintf(out, " = ");
                generate_cpp_code(node->init->right, out);
            }
            fprintf(out, "; ");
            generate_cpp_code(node->cond, out);
            fprintf(out, "; ");
            generate_cpp_code(node->incr, out);
            fprintf(out, ") ");
            generate_cpp_code(node->body, out);
            break;

        case NODE_PRINT:
            fprintf(out, "    cout << ");
            generate_cpp_code(node->left, out);
            fprintf(out, " << endl;\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            generate_cpp_code(node->body, out);
            fprintf(out, "    }\n");
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_cpp_code(node->left, out);
                fprintf(out, " %s ", node->op);
                generate_cpp_code(node->right, out);
            } else {
                generate_cpp_code(node->left, out);
                fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval);
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM && node->type != NODE_FOR && node->type != NODE_BLOCK) {
        generate_cpp_code(node->next, out);
    }
}

// === Python Code Generator ===
void generate_python_code(ASTNode *node, FILE *out, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) fprintf(out, "    ");

    switch (node->type) {
        case NODE_PROGRAM:
            generate_python_code(node->body, out, 0);
            break;

        case NODE_READ:
            generate_python_code(node->left, out, 0);
            fprintf(out, " = int(input())\n");
            break;

        case NODE_DECLARATION:
            fprintf(out, "%s = 0\n", node->sval);
            break;

        case NODE_ASSIGN:
            generate_python_code(node->left, out, 0);
            fprintf(out, " = ");
            generate_python_code(node->right, out, 0);
            fprintf(out, "\n");
            break;

        case NODE_FOR:
            fprintf(out, "for ");
            if (node->init && node->init->type == NODE_ASSIGN) {
                generate_python_code(node->init->left, out, 0);
            }
            fprintf(out, " in range(0, 10):\n");
            generate_python_code(node->body, out, indent + 1);
            break;

        case NODE_PRINT:
            fprintf(out, "print(");
            generate_python_code(node->left, out, 0);
            fprintf(out, ")\n");
            break;

        case NODE_BLOCK:
            generate_python_code(node->body, out, indent);
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval);
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM && node->type != NODE_FOR && node->type != NODE_BLOCK) {
        generate_python_code(node->next, out, indent);
    }
}

// === Java Code Generator ===
void generate_java_code(ASTNode *node, FILE *out, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) fprintf(out, "    ");

    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(out, "import java.util.Scanner;\n\npublic class Output {\n");
            fprintf(out, "    public static void main(String[] args) {\n");
            fprintf(out, "        Scanner scanner = new Scanner(System.in);\n");
            generate_java_code(node->body, out, 2);
            fprintf(out, "        scanner.close();\n");
            fprintf(out, "    }\n}\n");
            break;

        case NODE_READ:
            generate_java_code(node->left, out, 0);
            fprintf(out, " = scanner.nextInt();\n");
            break;

        case NODE_DECLARATION:
            fprintf(out, "int %s;\n", node->sval);
            break;

        case NODE_ASSIGN:
            generate_java_code(node->left, out, 0);
            fprintf(out, " = ");
            generate_java_code(node->right, out, 0);
            fprintf(out, ";\n");
            break;

        case NODE_FOR:
            fprintf(out, "for (");
            if (node->init && node->init->type == NODE_ASSIGN) {
                generate_java_code(node->init->left, out, 0);
                fprintf(out, " = ");
                generate_java_code(node->init->right, out, 0);
            }
            fprintf(out, "; ");
            generate_java_code(node->cond, out, 0);
            fprintf(out, "; ");
            generate_java_code(node->incr, out, 0);
            fprintf(out, ") ");
            generate_java_code(node->body, out, indent);
            break;

        case NODE_PRINT:
            fprintf(out, "System.out.println(");
            generate_java_code(node->left, out, 0);
            fprintf(out, ");\n");
            break;

        case NODE_BLOCK:
            fprintf(out, "{\n");
            generate_java_code(node->body, out, indent + 1);
            for (int i = 0; i < indent; i++) fprintf(out, "    ");
            fprintf(out, "}\n");
            break;

        case NODE_BINARY_OP:
            if (node->right) {
                generate_java_code(node->left, out, 0);
                fprintf(out, " %s ", node->op);
                generate_java_code(node->right, out, 0);
            } else {
                generate_java_code(node->left, out, 0);
                fprintf(out, "%s", node->op);
            }
            break;

        case NODE_INT_LIT:
            fprintf(out, "%d", node->ival);
            break;

        case NODE_VAR:
            fprintf(out, "%s", node->sval);
            break;

        default:
            break;
    }

    if (node->type != NODE_PROGRAM && node->type != NODE_FOR && node->type != NODE_BLOCK) {
        generate_java_code(node->next, out, indent);
    }
}