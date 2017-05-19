TESTS = tokens-check symbol_table-check scanner-test

.SECONDARY:
.PHONY: clean test

all: bin/parser bin/scanner

test: $(TESTS)

clean:
	rm -f */*.o bin/parser bin/scanner src/y.output src/y.tab.h src/y.tab.c src/lex.yy.c tests/*-check tests/*-check.c

bin/parser: src/y.tab.o src/tokens.o src/symbol_table.o
	gcc -o $@ $^ -ll

bin/scanner: src/standalone_scanner.c src/tokens.o src/symbol_table.o
	gcc -o $@ $^ -ll

src/y.tab.o: src/y.tab.c src/lex.yy.c
	gcc -o $@ -c $<

src/lex.yy.o: src/lex.yy.c src/y.tab.h
	gcc -o $@ -c $<

src/lex.yy.c: src/scanner.l
	lex -o $@ $<

src/y.tab.h src/y.tab.c: src/parser.y
	yacc src/parser.y --output=src/y.tab.c --defines=src/y.tab.h --verbose

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
