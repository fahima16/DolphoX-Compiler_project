#include "ast.h"

ASTNode* create_node(NodeType type) {
    ASTNode *node = (ASTNode*)calloc(1, sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed for ASTNode!\n");
        exit(1);
    }
    node->type = type;
    return node;
}

ASTNode* create_int_node(int val) {
    ASTNode *node = create_node(NODE_INT_LIT);
    node->ival = val;
    return node;
}

ASTNode* create_float_node(float val) {
    ASTNode *node = create_node(NODE_FLOAT_LIT);
    node->fval = val;
    return node;
}

ASTNode* create_double_node(double val) {
    ASTNode *node = create_node(NODE_DOUBLE_LIT);
    node->dval = val;
    return node;
}

ASTNode* create_char_node(char val) {
    ASTNode *node = create_node(NODE_CHAR_LIT);
    node->cval = val;
    return node;
}

ASTNode* create_string_node(char *val) {
    ASTNode *node = create_node(NODE_STRING_LIT);
    node->sval = val ? strdup(val) : NULL;
    return node;
}

ASTNode* create_bool_node(bool val) {
    ASTNode *node = create_node(NODE_BOOL_LIT);
    node->bval = val;
    return node;
}

ASTNode* create_id_node(char *name) {
    ASTNode *node = create_node(NODE_VAR);
    node->sval = name ? strdup(name) : NULL;
    return node;
}

ASTNode* create_bin_op(char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(NODE_BINARY_OP);
    node->op = strdup(op);
    node->left = left;
    node->right = right;
    return node;
}

void print_indent(int indent) {
    for (int i = 0; i < indent; i++) printf("  ");
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    print_indent(indent);

    switch (node->type) {
        case NODE_PROGRAM: printf("Program\n"); break;
        case NODE_DECLARATION: printf("Declaration: %s\n", node->sval ? node->sval : "unknown"); break;
        case NODE_ASSIGN: printf("Assignment (=)\n"); break;
        case NODE_PRINT: printf("Print Statement\n"); break;
        case NODE_READ: printf("Read Statement\n"); break;
        case NODE_IF: printf("If Statement\n"); break;
        case NODE_WHILE: printf("While Loop\n"); break;
        case NODE_FOR: printf("For Loop\n"); break;
        case NODE_BLOCK: printf("Block {}\n"); break;
        case NODE_BINARY_OP: printf("BinaryOp (%s)\n", node->op ? node->op : "?"); break;
        case NODE_FUNCTION_DEF: printf("Function Def: %s\n", node->sval ? node->sval : "unknown"); break;
        case NODE_FUNCTION_CALL: printf("Function Call: %s\n", node->sval ? node->sval : "unknown"); break;
        case NODE_RETURN: printf("Return\n"); break;
        case NODE_VAR: printf("Var (%s)\n", node->sval ? node->sval : "unknown"); break;
        case NODE_INT_LIT: printf("Int (%d)\n", node->ival); break;
        case NODE_FLOAT_LIT: printf("Float (%f)\n", node->fval); break;
        case NODE_DOUBLE_LIT: printf("Double (%lf)\n", node->dval); break;
        case NODE_CHAR_LIT: printf("Char ('%c')\n", node->cval); break;
        case NODE_STRING_LIT: printf("String (\"%s\")\n", node->sval ? node->sval : ""); break;
        case NODE_BOOL_LIT: printf("Bool (%s)\n", node->bval ? "true" : "false"); break;
        case NODE_ARRAY_DECL: printf("Array Declaration: %s[%d]\n", node->sval ? node->sval : "unknown", node->ival); break;
        case NODE_ARRAY_ACCESS: printf("Array Access: %s[]\n", node->sval ? node->sval : "unknown"); break;
        default: printf("Unknown Node\n"); break;
    }

    // Print Left and Right Children
    if (node->left) print_ast(node->left, indent + 1);
    if (node->right) print_ast(node->right, indent + 1);

    // Print Special Control Flow Subtrees with proper visual indent
    if (node->cond) {
        print_indent(indent + 1); printf("[Condition]:\n");
        print_ast(node->cond, indent + 2);
    }
    if (node->init) {
        print_indent(indent + 1); printf("[Init]:\n");
        print_ast(node->init, indent + 2);
    }
    if (node->incr) {
        print_indent(indent + 1); printf("[Incr]:\n");
        print_ast(node->incr, indent + 2);
    }
    if (node->body) {
        print_indent(indent + 1); printf("[Body]:\n");
        print_ast(node->body, indent + 2);
    }
    if (node->else_body) {
        print_indent(indent + 1); printf("[Else]:\n");
        print_ast(node->else_body, indent + 2);
    }

    // Print Linked Statement Nodes (Statements in a block/program)
    if (node->next) print_ast(node->next, indent);
}