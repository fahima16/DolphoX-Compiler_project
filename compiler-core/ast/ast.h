#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_PROGRAM,
    NODE_DECLARATION,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_READ,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_BLOCK,
    NODE_BINARY_OP,
    NODE_VAR,
    NODE_INT_LIT,
    NODE_FLOAT_LIT,
    NODE_ARRAY_DECL,
    NODE_ARRAY_ACCESS
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char *sval;
    int ival;
    float fval;
    char *op;
    
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
    struct ASTNode *cond;
    struct ASTNode *init;
    struct ASTNode *incr;
    struct ASTNode *body;
    struct ASTNode *else_body;
} ASTNode;

ASTNode* create_node(NodeType type);
ASTNode* create_int_node(int val);
ASTNode* create_float_node(float val);
ASTNode* create_id_node(char *name);
ASTNode* create_bin_op(char *op, ASTNode *left, ASTNode *right);

void print_ast(ASTNode *node, int indent);

#endif