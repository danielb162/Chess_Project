.PHONY: all
all: chess.c chess.h pieceRules.c
	gcc -pedantic -Wall -std=c99 -Wno-unused-variable -o chess $< -lm

.PHONY: backup
backup:
	rm -f ./backup/*;
	cp ./* ./backup

.PHONY: clean
clean:
	rm -f *.o
