#ifndef CHESS_HEAD
    #define CHESS_HEAD
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h> // For memset (?)
    #include <math.h> // For square root

    typedef struct CELL {
        char id;
        char color;
    } Cell;

    void initializeBoard();
    void printBoard();
    //void parseInput(char* pre, int* x1, int* y1, int* x2, int* y2);
    
#endif
