NTUST Compiler Design Project
=============================

[![Build Status](https://travis-ci.org/zetavg/NTUST-1052-Compiler-Design.svg?branch=master)](https://travis-ci.org/zetavg/NTUST-1052-Compiler-Design)

This project is a lex/yacc parser implementation of Go¯:
a simple Go programming language.

Usage
-----

Example usage of the parser:

```bash
$ bin/parser < tests/fixtures/example.go
```

To get an Graphviz diagram of the AST, use the `--graphviz` option:

```bash
$ bin/parser --graphviz < tests/fixtures/example.go
```

Example usage of the scanner:

```bash
$ bin/scanner < tests/fixtures/example.go
```


Building
--------

`make`, `gcc` and `lex` are required to build this project:

```bash
$ make
```

the compiled executable will be placed under `bin/` in the project directory.

To clean the project directory, run:

```bash
$ make clean
```


Testing
-------

To run C unit tests, `check` and `checkmk` are needed.
For execution result tests, you'll need `bats`.

```bash
$ make test
```


Contributors
------------

This work contains contributed code that are not originally written by myself (@zetavg). The link to their PRs are listed below.

- @Inndy - [#1](https://github.com/zetavg/NTUST-1052-Compiler-Design/pull/1)
