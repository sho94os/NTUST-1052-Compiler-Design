all: scanner

clean:
	rm *.o lex.yy.c scanner

scanner: scanner.o tokens.o
	gcc $^ -ll -o $@

scanner.o: lex.yy.c
	gcc -c lex.yy.c -o scanner.o

lex.yy.c: scanner.l
	lex scanner.l

%.o: %.cpp
	gcc -c $< -o %@
