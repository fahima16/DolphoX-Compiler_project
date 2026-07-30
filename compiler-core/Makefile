CC = gcc
CFLAGS = -Wall -I. -Iast -Isymbol_table -Icodegen -Iparser -Iintermediate -Ioptimizer

TARGET = mycompiler

all: $(TARGET)

# Generate Bison files
parser/parser.tab.c parser/parser.tab.h: parser/parser.y
	bison -d -o parser/parser.tab.c parser/parser.y

# Generate Flex files
lexer/lex.yy.c: lexer/lexer.l parser/parser.tab.h
	flex -o lexer/lex.yy.c lexer/lexer.l

# Build executable including intermediate and optimizer modules
$(TARGET): lexer/lex.yy.c parser/parser.tab.c ast/ast.c symbol_table/symbol_table.c symbol_table/semantic.c intermediate/tac.c optimizer/optimizer.c codegen/codegen.c main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c ast/ast.c symbol_table/symbol_table.c symbol_table/semantic.c intermediate/tac.c optimizer/optimizer.c codegen/codegen.c lexer/lex.yy.c parser/parser.tab.c


clean:
	rm -f lexer/lex.yy.c parser/parser.tab.* parser/parser.output $(TARGET) $(TARGET).exe output.c output.cpp output.py Output.java
	