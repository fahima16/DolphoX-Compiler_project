%{
#include "../parser/parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
%}

%option noyywrap
%option yylineno

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"bool"          { return BOOL; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"print"         { return PRINT; }
"true"          { return TRUE; }
"false"         { return FALSE; }
"read"          { return READ; }


[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT_LIT; }
[0-9]+          { yylval.ival = atoi(yytext); return INT_LIT; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return ID; }

"+="            { return ADD_ASSIGN; }
"-="            { return SUB_ASSIGN; }
"*="            { return MUL_ASSIGN; }
"/="            { return DIV_ASSIGN; }

"=="            { return EQ; }
"!="            { return NE; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return AND; }
"||"            { return OR; }
"++"            { return INC; }
"--"            { return DEC; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
"="             { return '='; }
"<"             { return '<'; }
">"             { return '>'; }
"!"             { return '!'; }

"{"             { return '{'; }
"}"             { return '}'; }
"("             { return '('; }
")"             { return ')'; }
"["             { return '['; }
"]"             { return ']'; }
";"             { return ';'; }
","             { return ','; }

"//".*          ;
[ \t\r\n]+      ;

.               { printf("Lexical Error at line %d: Unrecognized token '%s'\n", yylineno, yytext); }

%%