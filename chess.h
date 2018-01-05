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

    // Escape codes for colors, in-terminal
    static const char* LGR = "\033[0;37m";
    static const char* DGR = "\033[1;30m";
    static const char* YLW = "\033[1;33m"; // Acts as black for color reasons
    static const char* LGN = "\033[1;32m"; // Acts as white for color reasons
    static const char* WHT = "\033[1;37m";
    static const char* ORA = "\033[0;33m";
    static const char* RED = "\033[0;31m";
    static const char* BLU = "\033[0;34m";
    static const char* BBG = "\033[40m";
    static const char* WBG = "\033[107m";
    static const char* DBG = "\033[49m";
    //static const char* EDGE = "\033[1;30m|"; // Edge between cells

    // Maybe use char constants for black and white piece char instead
    static const char B = 'B';
    static const char W = 'W';

    // Function prototypes:
    void initializeBoard();
    void printBoard();
    bool validInput(char input[5]);
    void parseInput(char* pre, int* num1, int* num2, int* num3, int* num4);
    void blank(int x, int y);
    void moveSuccess(int x1, int y1, int x2, int y2);
    int canCapture(int x1, int y1, int x2, int y2);
    int distance(int x1, int y1, int x2, int y2);
    void pawnPromote(int x1, int y1);
    int movePawn(int x1, int y1, int x2, int y2);
    int moveBishop(int x1, int y1, int x2, int y2);
    int moveRook(int x1, int y1, int x2, int y2);
    int moveQueen(int x1, int y1, int x2, int y2);
    int moveKing(int x1, int y1, int x2, int y2);
    int moveKnight(int x1, int y1, int x2, int y2);
    int movePiece(int x1, int y1, int x2, int y2);
    int rebuildBoard(const char * path, char* turn, int* tCounter);
    
#endif
