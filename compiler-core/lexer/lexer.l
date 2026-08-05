%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.tab.h"

extern int yylineno;
int lexer_debug = 1;
%}

%option noyywrap yylineno

%%

[ \t\r]+                   ;
\n                          ;
"//".*                      ;
"/*"([^*]|\*+[^/*])*\*+"/" ;

"int"       { if (lexer_debug) printf("TOKEN int -> %s\n", yytext); return INT; }
"float"     { if (lexer_debug) printf("TOKEN float -> %s\n", yytext); return FLOAT; }
"double"    { if (lexer_debug) printf("TOKEN double -> %s\n", yytext); return DOUBLE; }
"char"      { if (lexer_debug) printf("TOKEN char -> %s\n", yytext); return CHAR; }
"string"    { if (lexer_debug) printf("TOKEN string -> %s\n", yytext); return STRING; }
"bool"      { if (lexer_debug) printf("TOKEN bool -> %s\n", yytext); return BOOL; }
"if"        { if (lexer_debug) printf("TOKEN if -> %s\n", yytext); return IF; }
"else"      { if (lexer_debug) printf("TOKEN else -> %s\n", yytext); return ELSE; }
"while"     { if (lexer_debug) printf("TOKEN while -> %s\n", yytext); return WHILE; }
"for"       { if (lexer_debug) printf("TOKEN for -> %s\n", yytext); return FOR; }
"print"     { if (lexer_debug) printf("TOKEN print -> %s\n", yytext); return PRINT; }
"read"      { if (lexer_debug) printf("TOKEN read -> %s\n", yytext); return READ; }
"function"  { if (lexer_debug) printf("TOKEN function -> %s\n", yytext); return FUNCTION; }
"return"    { if (lexer_debug) printf("TOKEN return -> %s\n", yytext); return RETURN; }
"true"      { if (lexer_debug) printf("TOKEN true -> %s\n", yytext); yylval.bval = 1; return TRUE; }
"false"     { if (lexer_debug) printf("TOKEN false -> %s\n", yytext); yylval.bval = 0; return FALSE; }
"&&"        { if (lexer_debug) printf("TOKEN && -> %s\n", yytext); return AND; }
"||"        { if (lexer_debug) printf("TOKEN || -> %s\n", yytext); return OR; }
"=="        { if (lexer_debug) printf("TOKEN == -> %s\n", yytext); return EQ; }
"!="        { if (lexer_debug) printf("TOKEN != -> %s\n", yytext); return NE; }
"<="        { if (lexer_debug) printf("TOKEN <= -> %s\n", yytext); return LE; }
">="        { if (lexer_debug) printf("TOKEN >= -> %s\n", yytext); return GE; }
"++"        { if (lexer_debug) printf("TOKEN ++ -> %s\n", yytext); return INC; }
"--"        { if (lexer_debug) printf("TOKEN -- -> %s\n", yytext); return DEC; }
"+="        { if (lexer_debug) printf("TOKEN += -> %s\n", yytext); return ADD_ASSIGN; }
"-="        { if (lexer_debug) printf("TOKEN -= -> %s\n", yytext); return SUB_ASSIGN; }
"*="        { if (lexer_debug) printf("TOKEN *= -> %s\n", yytext); return MUL_ASSIGN; }
"/="        { if (lexer_debug) printf("TOKEN /= -> %s\n", yytext); return DIV_ASSIGN; }
"="         { if (lexer_debug) printf("TOKEN = -> %s\n", yytext); return '='; }
"+"         { if (lexer_debug) printf("TOKEN + -> %s\n", yytext); return '+'; }
"-"         { if (lexer_debug) printf("TOKEN - -> %s\n", yytext); return '-'; }
"*"         { if (lexer_debug) printf("TOKEN * -> %s\n", yytext); return '*'; }
"/"         { if (lexer_debug) printf("TOKEN / -> %s\n", yytext); return '/'; }
"%"         { if (lexer_debug) printf("TOKEN %% -> %s\n", yytext); return '%'; }
";"         { if (lexer_debug) printf("TOKEN ; -> %s\n", yytext); return ';'; }
","         { if (lexer_debug) printf("TOKEN , -> %s\n", yytext); return ','; }
":"         { if (lexer_debug) printf("TOKEN : -> %s\n", yytext); return ':'; }
"."         { if (lexer_debug) printf("TOKEN . -> %s\n", yytext); return '.'; }
"("         { if (lexer_debug) printf("TOKEN ( -> %s\n", yytext); return '('; }
")"         { if (lexer_debug) printf("TOKEN ) -> %s\n", yytext); return ')'; }
"{"         { if (lexer_debug) printf("TOKEN { -> %s\n", yytext); return '{'; }
"}"         { if (lexer_debug) printf("TOKEN } -> %s\n", yytext); return '}'; }
"["         { if (lexer_debug) printf("TOKEN [ -> %s\n", yytext); return '['; }
"]"         { if (lexer_debug) printf("TOKEN ] -> %s\n", yytext); return ']'; }
"<"         { if (lexer_debug) printf("TOKEN < -> %s\n", yytext); return '<'; }
">"         { if (lexer_debug) printf("TOKEN > -> %s\n", yytext); return '>'; }

[0-9]+                      { if (lexer_debug) printf("TOKEN INT_LIT -> %s\n", yytext); yylval.ival = atoi(yytext); return INT_LIT; }
[0-9]+"."[0-9]+            { if (lexer_debug) printf("TOKEN FLOAT_LIT -> %s\n", yytext); yylval.fval = atof(yytext); return FLOAT_LIT; }
"\""([^"\\]|\\.)*"\"" { if (lexer_debug) printf("TOKEN STRING_LIT -> %s\n", yytext); yylval.sval = strdup(yytext); return STRING_LIT; }
"'"([^'\\]|\\.)*"'"     { if (lexer_debug) printf("TOKEN CHAR_LIT -> %s\n", yytext); yylval.cval = yytext[1]; return CHAR_LIT; }
[a-zA-Z_][a-zA-Z0-9_]*     { if (lexer_debug) printf("TOKEN ID -> %s\n", yytext); yylval.sval = strdup(yytext); return ID; }

.                           { if (lexer_debug) printf("TOKEN UNKNOWN -> %s\n", yytext); return yytext[0]; }

%%