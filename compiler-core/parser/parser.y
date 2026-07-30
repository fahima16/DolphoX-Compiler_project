%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../ast/ast.h"

extern int yylex();
extern int yylineno;
void yyerror(const char *s);

ASTNode *root = NULL;
%}

%union {
    char cval;
    int ival;
    float fval;
    double dval;
    bool bval;
    char* sval;
    struct ASTNode* node;
}

%token <sval> ID STRING_LIT
%token <cval> CHAR_LIT
%token <ival> INT_LIT
%token <fval> FLOAT_LIT
%token <dval> DOUBLE_LIT
%token <bval> TRUE FALSE
%token INT FLOAT DOUBLE CHAR STRING BOOL IF ELSE WHILE FOR PRINT READ FUNCTION RETURN
%token EQ NE LE GE AND OR INC DEC
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN

%type <node> program statement_list statement declaration_stmt id_list declarator assignment_stmt read_stmt print_stmt if_stmt while_stmt for_stmt block_stmt function_def return_stmt param_list param expr arg_list
%type <ival> type

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
    statement_list { 
        root = create_node(NODE_PROGRAM); 
        root->left = $1; 
    }
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
    | function_def        { $$ = $1; }
    | return_stmt         { $$ = $1; }
    ;

function_def:
    FUNCTION type ID '(' ')' block_stmt {
        $$ = create_node(NODE_FUNCTION_DEF);
        $$->sval = strdup($3);
        $$->ival = $2;
        $$->left = NULL;
        $$->right = $6;
    }
    | FUNCTION type ID '(' param_list ')' block_stmt {
        $$ = create_node(NODE_FUNCTION_DEF);
        $$->sval = strdup($3);
        $$->ival = $2;
        $$->left = $5;
        $$->right = $7;
    }
    ;

return_stmt:
    RETURN expr ';' {
        $$ = create_node(NODE_RETURN);
        $$->left = $2;
    }
    | RETURN ';' {
        $$ = create_node(NODE_RETURN);
    }
    ;

param_list:
    param { $$ = $1; }
    | param_list ',' param {
        ASTNode *curr = $1;
        while (curr->next != NULL) curr = curr->next;
        curr->next = $3;
        $$ = $1;
    }
    ;

param:
    type ID {
        $$ = create_node(NODE_DECLARATION);
        $$->sval = strdup($2);
        $$->left = create_int_node($1);
        $$->is_parameter = 1;
    }
    ;

declaration_stmt:
    type id_list {
        ASTNode *curr = $2;
        while (curr != NULL) {
            if (curr->type == NODE_DECLARATION || curr->type == NODE_ARRAY_DECL) {
                curr->left = create_int_node($1);
            }
            curr = curr->next;
        }
        $$ = $2;
    }
    ;

type:
      INT    { $$ = INT; }
    | FLOAT  { $$ = FLOAT; }
    | DOUBLE { $$ = DOUBLE; }
    | CHAR   { $$ = CHAR; }
    | STRING { $$ = STRING; }
    | BOOL   { $$ = BOOL; }
    ;

id_list:
    id_list ',' declarator {
        ASTNode *curr = $1;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = $3;
        $$ = $1;
    }
    | declarator {
        $$ = $1;
    }
    ;

declarator:
      ID {
        $$ = create_node(NODE_DECLARATION);
        $$->sval = strdup($1);
    }
    | ID '=' expr {
        ASTNode *decl = create_node(NODE_DECLARATION);
        decl->sval = strdup($1);

        ASTNode *assign = create_node(NODE_ASSIGN);
        assign->left = create_id_node($1);
        assign->right = $3;

        decl->next = assign;
        $$ = decl;
    }
    | ID '[' INT_LIT ']' {
        $$ = create_node(NODE_ARRAY_DECL);
        $$->sval = strdup($1);
        $$->ival = $3;
    }
    ;

assignment_stmt:
      ID '=' expr             { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = $3; }
    | ID ADD_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("+", create_id_node($1), $3); }
    | ID SUB_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("-", create_id_node($1), $3); }
    | ID MUL_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("*", create_id_node($1), $3); }
    | ID DIV_ASSIGN expr   { $$ = create_node(NODE_ASSIGN); $$->left = create_id_node($1); $$->right = create_bin_op("/", create_id_node($1), $3); }
    | ID '[' expr ']' '=' expr { 
        $$ = create_node(NODE_ASSIGN); 
        ASTNode *arr = create_node(NODE_ARRAY_ACCESS);
        arr->sval = strdup($1);
        arr->left = $3;
        $$->left = arr; 
        $$->right = $6; 
    }
    ;

read_stmt:
      READ ID           { $$ = create_node(NODE_READ); $$->left = create_id_node($2); }
    | READ '(' ID ')'   { $$ = create_node(NODE_READ); $$->left = create_id_node($3); }
    ;

print_stmt:
      PRINT expr         { $$ = create_node(NODE_PRINT); $$->left = $2; }
    | PRINT '(' expr ')' { $$ = create_node(NODE_PRINT); $$->left = $3; }
    ;

if_stmt:
      IF '(' expr ')' statement %prec LOWER_THAN_ELSE { 
        $$ = create_node(NODE_IF); 
        $$->cond = $3;
        $$->body = $5;
    }
    | IF '(' expr ')' statement ELSE statement { 
        $$ = create_node(NODE_IF); 
        $$->cond = $3;
        $$->body = $5;
        $$->else_body = $7;
    }
    ;

while_stmt:
    WHILE '(' expr ')' statement { 
        $$ = create_node(NODE_WHILE); 
        $$->cond = $3;
        $$->body = $5;
    }
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
    '{' statement_list '}' { 
        $$ = create_node(NODE_BLOCK); 
        $$->left = $2; 
    }
    ;

expr:
      INT_LIT                 { $$ = create_int_node($1); }
    | FLOAT_LIT               { $$ = create_float_node($1); }
    | DOUBLE_LIT              { $$ = create_double_node($1); }
    | CHAR_LIT                { $$ = create_char_node($1); }
    | STRING_LIT              { $$ = create_string_node($1); }
    | TRUE                    { $$ = create_bool_node(true); }
    | FALSE                   { $$ = create_bool_node(false); }
    | ID                      { $$ = create_id_node($1); }
    | ID INC                  { $$ = create_node(NODE_BINARY_OP); $$->op = strdup("++"); $$->left = create_id_node($1); }
    | ID DEC                  { $$ = create_node(NODE_BINARY_OP); $$->op = strdup("--"); $$->left = create_id_node($1); }
    | ID '[' expr ']'         { $$ = create_node(NODE_ARRAY_ACCESS); $$->sval = strdup($1); $$->left = $3; }
    | ID '(' ')'              { $$ = create_node(NODE_FUNCTION_CALL); $$->sval = strdup($1); $$->left = NULL; }
    | ID '(' arg_list ')'     { $$ = create_node(NODE_FUNCTION_CALL); $$->sval = strdup($1); $$->left = $3; }
    | expr '+' expr           { $$ = create_bin_op("+", $1, $3); }
    | expr '-' expr           { $$ = create_bin_op("-", $1, $3); }
    | expr '*' expr           { $$ = create_bin_op("*", $1, $3); }
    | expr '/' expr           { $$ = create_bin_op("/", $1, $3); }
    | expr '%' expr           { $$ = create_bin_op("%", $1, $3); }
    | expr EQ expr            { $$ = create_bin_op("==", $1, $3); }
    | expr NE expr            { $$ = create_bin_op("!=", $1, $3); }
    | expr LE expr            { $$ = create_bin_op("<=", $1, $3); }
    | expr GE expr            { $$ = create_bin_op(">=", $1, $3); }
    | expr AND expr           { $$ = create_bin_op("&&", $1, $3); }
    | expr OR expr            { $$ = create_bin_op("||", $1, $3); }
    | expr '<' expr           { $$ = create_bin_op("<", $1, $3); }
    | expr '>' expr           { $$ = create_bin_op(">", $1, $3); }
    | '(' expr ')'            { $$ = $2; }
    ;

arg_list:
    expr { $$ = $1; }
    | arg_list ',' expr {
        ASTNode *curr = $1;
        while (curr->next != NULL) curr = curr->next;
        curr->next = $3;
        $$ = $1;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error at line %d: %s\n", yylineno, s);
}