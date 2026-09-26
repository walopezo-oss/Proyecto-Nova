CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = nova

all: $(TARGET)

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

main.o: main.c ast.h symbol_table.h parser.tab.h
	$(CC) $(CFLAGS) -c main.c

$(TARGET): parser.tab.c lex.yy.c ast.o symbol_table.o main.o
	$(CC) $(CFLAGS) parser.tab.c lex.yy.c ast.o symbol_table.o main.o -o $(TARGET)

clean:
	rm -f $(TARGET) *.o lex.yy.c parser.tab.c parser.tab.h
