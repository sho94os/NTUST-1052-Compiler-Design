TESTS = tokens-check symbol_table-check ast-check scanner-test

.SECONDARY:
.PHONY: clean test

CFLAGS += -std=c99

all: bin/parser bin/scanner

test: $(TESTS)

clean:
	rm -f */*.o bin/parser bin/scanner src/y.output src/y.tab.h src/y.tab.c src/lex.yy.c tests/*-check tests/*-check.c

bin/parser: src/standalone_parser.o src/tokens.o src/symbol_table.o src/ast.o
	gcc $(CFLAGS) -o $@ $^ -ll

bin/scanner: src/standalone_scanner.o src/tokens.o src/symbol_table.o
	gcc $(CFLAGS) -o $@ $^ -ll

src/standalone_parser.o: src/standalone_parser.c src/y.tab.c
	gcc $(CFLAGS) -o $@ -c $<

src/standalone_scanner.o: src/standalone_scanner.c src/lex.yy.c
	gcc $(CFLAGS) -o $@ -c $<

src/lex.yy.c: src/scanner.l
	lex -o $@ $<

src/y.tab.h src/y.tab.c: src/parser.y src/lex.yy.c
	yacc src/parser.y --output=src/y.tab.c --defines=src/y.tab.h --verbose

src/tokens.o: src/tokens.c src/tokens.h src/y.tab.h
	gcc $(CFLAGS) -o $@ -c $<

src/%.o: src/%.c src/%.h
	gcc $(CFLAGS) -o $@ -c $<

%-check: tests/%-check
	$<

scanner-test: bin/scanner
	tests/scanner-test.bats

tests/%-check: src/%.o tests/%-check.o
	gcc $(CFLAGS) $^ -o $@ `pkg-config --cflags --libs check`

tests/%-check.o: %-check.c
	gcc $(CFLAGS) -c $< -o $@

tests/%-check.c: tests/%-test.check
	checkmk $< > $@
