NTUST Compiler Design Project
=============================

This project is a simple compiler implementation of a Golang-like
programming language.


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

```bash
$ make test
```
