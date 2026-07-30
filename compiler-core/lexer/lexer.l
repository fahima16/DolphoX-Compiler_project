%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../parser/parser.tab.h"

void yyerror(const char *s);
%}

%option noyywrap
%option yylineno

%%

"int"           { return INT; }
"float"         { return FLOAT; }
"double"        { return DOUBLE; }
"char"          { return CHAR; }
"string"        { return STRING; }
"bool"          { return BOOL; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"print"         { return PRINT; }
"function"      { return FUNCTION; }
"return"        { return RETURN; }
"true"          { yylval.bval = true; return TRUE; }
"false"         { yylval.bval = false; return FALSE; }
"read"          { return READ; }

[0-9]+\.[0-9]+[fF]  { yylval.fval = (float)atof(yytext); return FLOAT_LIT; }
[0-9]+\.[0-9]+      { yylval.dval = atof(yytext); return DOUBLE_LIT; }
[0-9]+              { yylval.ival = atoi(yytext); return INT_LIT; }

\'\\.\'             {
                        if (yytext[2] == 'n') yylval.cval = '\n';
                        else if (yytext[2] == 't') yylval.cval = '\t';
                        else if (yytext[2] == '0') yylval.cval = '\0';
                        else yylval.cval = yytext[2];
                        return CHAR_LIT;
                    }

\'[^\']\'           { yylval.cval = yytext[1]; return CHAR_LIT; }

\"[^\"]*\"          { 
                        yytext[strlen(yytext)-1] = '\0'; 
                        yylval.sval = strdup(yytext + 1); 
                        return STRING_LIT; 
                    }

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
"/*"([^*]|\*+[^/*])*\*+"/" ;
[ \t\r\n]+      ;

.               { printf("Lexical Error at line %d: Unrecognized token '%s'\n", yylineno, yytext); }

%%