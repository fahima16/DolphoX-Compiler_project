CC = gcc
CFLAGS = -O2 -Wall -I.

all: mycompiler

parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison -d -o parser/parser.tab.c parser/parser.y

lexer/lex.yy.c: lexer/lexer.l parser/parser.tab.h
	flex -o lexer/lex.yy.c lexer/lexer.l

mycompiler: lexer/lex.yy.c parser/parser.tab.c ast/ast.c symbol_table/symbol_table.c codegen/codegen.c main.c
	$(CC) $(CFLAGS) -o mycompiler main.c ast/ast.c symbol_table/symbol_table.c codegen/codegen.c lexer/lex.yy.c parser/parser.tab.c

clean:
	rm -f lexer/lex.yy.c parser/parser.tab.* parser/parser.output mycompiler mycompiler.exe output.c output.cpp output.py output.java