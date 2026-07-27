#include "ast.h"

ASTNode* create_node(NodeType type) {
    ASTNode *node = (ASTNode*)calloc(1, sizeof(ASTNode));
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

ASTNode* create_id_node(char *name) {
    ASTNode *node = create_node(NODE_VAR);
    node->sval = strdup(name);
    return node;
}

ASTNode* create_bin_op(char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = create_node(NODE_BINARY_OP);
    node->op = strdup(op);
    node->left = left;
    node->right = right;
    return node;
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NODE_PROGRAM: printf("Program\n"); break;
        case NODE_DECLARATION: printf("Declaration: %s\n", node->sval); break;
        case NODE_ASSIGN: printf("Assignment (=)\n"); break;
        case NODE_PRINT: printf("Print Statement\n"); break;
        case NODE_IF: printf("If Statement\n"); break;
        case NODE_WHILE: printf("While Loop\n"); break;
        case NODE_FOR: printf("For Loop\n"); break;
        case NODE_BLOCK: printf("Block {}\n"); break;
        case NODE_BINARY_OP: printf("BinaryOp (%s)\n", node->op); break;
        case NODE_VAR: printf("Var (%s)\n", node->sval); break;
        case NODE_INT_LIT: printf("Int (%d)\n", node->ival); break;
        case NODE_FLOAT_LIT: printf("Float (%f)\n", node->fval); break;
        case NODE_ARRAY_DECL: printf("Array Declaration: %s[%d]\n", node->sval, node->ival); break;
        case NODE_ARRAY_ACCESS: printf("Array Access: %s[]\n", node->sval); break;
        default: printf("Unknown Node\n"); break;
    }

    if (node->left) print_ast(node->left, indent + 1);
    if (node->right) print_ast(node->right, indent + 1);
    if (node->cond) { printf("Condition:\n"); print_ast(node->cond, indent + 1); }
    if (node->init) { printf("Init:\n"); print_ast(node->init, indent + 1); }
    if (node->incr) { printf("Incr:\n"); print_ast(node->incr, indent + 1); }
    if (node->body) { printf("Body:\n"); print_ast(node->body, indent + 1); }
    if (node->else_body) { printf("Else:\n"); print_ast(node->else_body, indent + 1); }
    if (node->next) print_ast(node->next, indent);
}