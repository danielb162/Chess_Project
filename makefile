all: genCells.c chess.h chess.c
    gcc -o genC genCells.c;
    gcc chess.c

gen:
    genC

backup:
    rm -f ./backup/*;
    cp ./* ./backup