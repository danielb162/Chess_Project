#include "chess.h"

static const char* BLK = "\033[0;30m";
static const char* RED = "\033[0;31m";
static const char* GRN = "\033[0;32m";
static const char* ORG = "\033[0;33m";
static const char* BLU = "\033[0;34m";
static const char* PRP = "\033[0;35m";
static const char* CYN = "\033[0;36m";
static const char* LGR = "\033[0;37m";

static const char* DGR = "\033[1;30m";
static const char* LRD = "\033[1;31m";
static const char* LGN = "\033[1;32m";
static const char* YLW = "\033[1;33m";
static const char* LBL = "\033[1;34m";
static const char* LPR = "\033[1;35m";
static const char* LCY = "\033[1;36m";
static const char* WHT = "\033[1;37m";

Cell board[8][8];

void initializeBoard() {
    Piece black_pawn = { .id = PAWN, .color = BLACK };
    Piece white_pawn = { .id = PAWN, .color = WHITE };
    Cell white_cell = { .id = 'P', .color = 'B', .piece = black_pawn };
    Cell black_cell = { .id = 'P', .color = 'W', .piece = white_pawn };

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = ((i+j)%2 == 0) ? white_cell : black_cell;
        }
    }
}

// TO DO: Change this so it prints out the colors of the board appropriately with DGREY for black pieces and WHITE for white pieces
int printBoard() {
    // Top padding:
    printf("%s-------------------------\n", YLW);
    for (char row = 'A'; row <= 'H'; row++) { // Row counter, i.e. A - H
        for (char col = '1'; col <= '8'; col++) { // Col counter, i.e. 1 - 8
            char temp[2] = {row, col};
            if (board[row-'A'][col-'1'].piece.color == BLACK)
                printf("%s|%s%c%c", YLW, DGR, row, col);
            else if (board[row-'A'][col-'1'].piece.color == WHITE)
                printf("%s|%s%c%c", YLW, WHT, row, col);
            else printf("%s|%s%c%c", RED, BLU, row, col);
        }
        printf("%s|\n", YLW);
    }
    // Bottom padding:
    printf("%s-------------------------\n", YLW);

    return 0;
}


/* Bash color codes (https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux)

Black        0;30     Dark Gray     1;30
Red          0;31     Light Red     1;31
Green        0;32     Light Green   1;32
Brown/Orange 0;33     Yellow        1;33
Blue         0;34     Light Blue    1;34
Purple       0;35     Light Purple  1;35
Cyan         0;36     Light Cyan    1;36
Light Gray   0;37     White         1;37
And then use them like this in your script ('\033' is the escape character for '<Esc>'):

    RED='\033[0;31m'
    NC='\033[0m' # No Color
    printf "I ${RED}love${NC} Stack Overflow\n"
    echo -e "I ${RED}love${NC} Stack Overflow"

*/

int main() {
    // Uses genCells.c to create a clean board state
    // #include "clean_board"
 
    /* Sanity check for clean_board:
    printf("A8's id is: \033[1;37m%c\033[0m\nD7's id is: \033[1;30m%c\033[0m\n", A8.id, D7.id);
    printf("A1's id is %c, it's color is %c\n", row1[0].id, row1[0].color);*/

    initializeBoard();
    printBoard();



    // No errors encountered
    return 0;
}