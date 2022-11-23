CC=gcc
EXE=./bin/a.out
MAIN=./src/main.c
LCHECK=valgrind
.SILENT:



default: clean compile run

clean:
	../clean.sh

compile:
	$(CC) -o $(EXE) $(MAIN)

run:
	$(EXE)

resource_leak_check: clean compile
	$(LCHECK) --leak-check=full $(EXE)

