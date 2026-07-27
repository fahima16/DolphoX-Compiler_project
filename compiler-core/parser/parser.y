%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

ASTNode *root = NULL;
%}

%union {
    int ival;
    float fval;
    char* sval;
    struct ASTNode* node;
}

%token <sval> ID
%token <ival> INT_LIT
%token <fval> FLOAT_LIT
%token INT FLOAT BOOL IF ELSE WHILE FOR PRINT READ TRUE FALSE
%token EQ NE LE GE AND OR INC DEC
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN

%type <node> program statement_list statement declaration_stmt assignment_stmt read_stmt print_stmt if_stmt while_stmt for_stmt block_stmt expr

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!' INC DEC

%%

program:
    statement_list { root = create_node(NODE_PROGRAM); root->body = $1; }
    ;

statement_list:
    statement_list statement {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            ASTNode *curr = $1;
            while (curr->next != NULL) curr = curr->next;
            curr->next = $2;
            $$ = $1;
        }
    }
    | /* empty */ { $$ = NULL; }
    ;

statement:
    declaration_stmt ';' { $$ = $1; }
    | assignment_stmt ';' { $$ = $1; }
    | read_stmt ';'       { $$ = $1; }
    | print_stmt ';'      { $$ = $1; }
    | if_stmt             { $$ = $1; }
    | while_stmt          { $$ = $1; }
    | for_stmt            { $$ = $1; }
    | block_stmt          { $$ = $1; }
    ;

declaration_stmt:
    INT ID { $$ = create_node(NODE_DECLARATION); $$->sval = strdup($2); }
    | FLOAT ID { $$ = create_node(NODE_DECLARATION); $$->sval = strdup($2); }
    | BOOL ID { $$ = create_node(NODE_DECLARATION); $$->sval = strdup($2); }
    | INT ID '[' INT_LIT ']' { $$ = create_node(NODE_ARRAY_DECL); $$->sval = strdup($2); $$->ival = $4; }
    ;

assignment_stmt:
    ID '=' expr            { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = $3; }
    | ID ADD_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("+", create_id_node($1), $3); }
    | ID SUB_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("-", create_id_node($1), $3); }
    | ID MUL_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("*", create_id_node($1), $3); }
    | ID DIV_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("/", create_id_node($1), $3); }
    | ID '[' expr ']' '=' expr { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->left->left = $3; $$->right = $6; }
    ;

read_stmt:
    READ ID           { $$ = create_node(NODE_READ); $$->left = create_id_node($2); }
    | READ '(' ID ')' { $$ = create_node(NODE_READ); $$->left = create_id_node($3); }
    ;

print_stmt:
    PRINT expr         { $$ = create_node(NODE_PRINT); $$->left = $2; }
    | PRINT '('expr')' { $$ = create_node(NODE_PRINT); $$->left = $3; }
    ;

if_stmt:
    IF '(' expr ')' statement %prec LOWER_THAN_ELSE { $$ = create_node(NODE_IF); $$->cond = $3; $$->body = $5; }
    | IF '(' expr ')' statement ELSE statement { $$ = create_node(NODE_IF); $$->cond = $3; $$->body = $5; $$->else_body = $7; }
    ;

while_stmt:
    WHILE '(' expr ')' statement { $$ = create_node(NODE_WHILE); $$->cond = $3; $$->body = $5; }
    ;

for_stmt:
    FOR '(' assignment_stmt ';' expr ';' expr ')' statement {
        $$ = create_node(NODE_FOR);
        $$->init = $3;
        $$->cond = $5;
        $$->incr = $7;
        $$->body = $9;
    }
    | FOR '(' assignment_stmt ';' expr ';' assignment_stmt ')' statement {
        $$ = create_node(NODE_FOR);
        $$->init = $3;
        $$->cond = $5;
        $$->incr = $7;
        $$->body = $9;
    }
    ;

block_stmt:
    '{' statement_list '}' { $$ = create_node(NODE_BLOCK); $$->body = $2; }
    ;

expr:
    INT_LIT                  { $$ = create_int_node($1); }
    | FLOAT_LIT              { $$ = create_float_node($1); }
    | ID                     { $$ = create_id_node($1); }
    | ID INC                 { $$ = create_node(NODE_BINARY_OP); $$->op = strdup("++"); $$->left = create_id_node($1); }
    | ID DEC                 { $$ = create_node(NODE_BINARY_OP); $$->op = strdup("--"); $$->left = create_id_node($1); }
    | ID '[' expr ']'        { $$ = create_node(NODE_ARRAY_ACCESS); $$->sval = strdup($1); $$->left = $3; }
    | expr '+' expr          { $$ = create_bin_op("+", $1, $3); }
    | expr '-' expr          { $$ = create_bin_op("-", $1, $3); }
    | expr '*' expr          { $$ = create_bin_op("*", $1, $3); }
    | expr '/' expr          { $$ = create_bin_op("/", $1, $3); }
    | expr '%' expr          { $$ = create_bin_op("%", $1, $3); }
    | expr EQ expr           { $$ = create_bin_op("==", $1, $3); }
    | expr NE expr           { $$ = create_bin_op("!=", $1, $3); }
    | expr LE expr           { $$ = create_bin_op("<=", $1, $3); }
    | expr GE expr           { $$ = create_bin_op(">=", $1, $3); }
    | expr '<' expr          { $$ = create_bin_op("<", $1, $3); }
    | expr '>' expr          { $$ = create_bin_op(">", $1, $3); }
    | '(' expr ')'           { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
}