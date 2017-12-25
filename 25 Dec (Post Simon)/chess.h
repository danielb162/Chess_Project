#ifndef CHESS_HEAD
    #define CHESS_HEAD
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> // For memset
    #include <unistd.h>
    #include <sys/wait.h>

    typedef struct CELL {
        char id;
        char color;
    } Cell;

#endif