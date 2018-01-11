#ifndef CHESS_HEAD
    #define CHESS_HEAD

    //  General libraries
    #include <stdio.h>
    #include <stdlib.h>
    //  Library to utilize boolean logic
    #include <stdbool.h>
    //  Used for strncmp
    #include <string.h>
    //  Used for sqrt()
    #include <math.h>

    //  Struct used for, relatively speaking, atomic information
    typedef struct CELL {
        char id;
        char color;
    } Cell;

    // Escape codes for in-terminal text printing
    static const char* LGR = "\033[0;37m"; //  Standard terminal color
    static const char* WHT = "\033[1;37m"; //  Color of the 'lines'/tile seperators
    static const char* YLW = "\033[1;33m"; //  Acts as black for color reasons
    static const char* LGN = "\033[1;32m"; //  Acts as white for color reasons
    static const char* ULN = "\033[4m";    //  Changes text to be underlined
    static const char* NULN = "\033[24m";  //  Changes text to not be underlined

    // Char constants for the id field of the Cell struct
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
    int rebuildBoard(const char* path, char* turn, int* tCounter);
    
#endif
