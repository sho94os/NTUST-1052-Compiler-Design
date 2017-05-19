TESTS = tokens-check symbol_table-check scanner-test

.SECONDARY:
.PHONY: clean test

all: bin/scanner

test: $(TESTS)

clean:
	rm -f */*.o bin/scanner src/lex.yy.c tests/*-check tests/*-check.c

bin/scanner: src/scanner.o src/tokens.o src/symbol_table.o
	gcc -o $@ $^ -ll

src/scanner.o: src/lex.yy.c
	gcc -o $@ -c $^

src/lex.yy.c: src/scanner.l
	lex -o $@ $<

src/%.o: src/%.c src/%.h
	gcc -o $@ -c $<

%-check: tests/%-check
	$<

scanner-test: bin/scanner
	tests/scanner_test.bats

tests/%-check: src/%.o tests/%-check.o
	gcc -lcheck $^ -o $@

tests/%-check.o: %-check.c
	gcc -c $< -o $@

tests/%-check.c: tests/%-test.check
	checkmk $< > $@
