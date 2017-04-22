all: bin/scanner

clean:
	rm -f bin/scanner src/*.o src/lex.yy.c

bin/scanner: src/scanner.o src/tokens.o
	gcc -o $@ $^ -ll

src/scanner.o: src/lex.yy.c
	gcc -o $@ -c $^

src/lex.yy.c: src/scanner.l
	lex -o $@ $<

src/%.o: src/%.c src/%.h
	gcc -o $@ -c $<
