all: genCells.c chess.h chess.c
	gcc -pedantic -Wall -std=c99 -Wno-unused-variable -o genC genCells.c;
	gcc -pedantic -Wall -std=c99 -Wno-unused-variable chess.c

gen:
	genC

backup:
	rm -f ./backup/*;
	cp ./* ./backup

.PHONY: clean
clean:
	rm -f *.o
