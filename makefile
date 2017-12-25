.PHONY: all
all: chess.c chess.h
	gcc -pedantic -Wall -std=c99 -Wno-unused-variable -o chess $<

.PHONY: backup
backup:
	rm -f ./backup/*;
	cp ./* ./backup

.PHONY: clean
clean:
	rm -f *.o
