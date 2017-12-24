#ifndef CHESS_HEAD
#define CHESS_HEAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For memset
#include <unistd.h>
#include <sys/wait.h>

typedef enum {
    NONE,
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
} ID;

typedef enum { BLACK, WHITE } Color;

typedef struct PIECE {
    ID id;
    Color color;
} Piece;

typedef struct CELL {
    char id;
    char color;
    Piece piece;
} Cell;

#endif /* CHESS_HEAD */
