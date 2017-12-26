#include "chess.h"

// Escape codes for colors, in-terminal
static const char* LGR = "\033[0;37m";
static const char* DGR = "\033[1;30m";
static const char* YLW = "\033[1;33m"; // Acts as black for color reasons
static const char* WHT = "\033[1;37m";
static const char* ORA = "\033[0;33m";
static const char* LGN = "\033[1;32m"; // Acts as white for color reasons
static const char* RED = "\033[0;31m";
static const char* BLU = "\033[0;34m";
static const char* BBG = "\033[40m";
static const char* WBG = "\033[107m";
static const char* DBG = "\033[49m";
//static const char* EDGE = "\033[1;30m|"; // Edge between cells

// Maybe use char constants for black and white piece char instead
static const char B = 'B';
static const char W = 'W';

// [Row][Column], i.e. [0][0] -> A1 & [4][3] -> D5
Cell board[8][8];

// Initiliaze an empty board:
void initializeBoard() {
    for (int r = 0; r <= 7; r++) {
        for (int c = 0; c <= 7; c++) {
            if (r == 0) {
                board[r][c].color = W;
            }
            else if (r == 1) {
                board[r][c].id = 'P';
                board[r][c].color = W;
            }
            else if (r == 6) {
                board[r][c].id = 'P';
                board[r][c].color = B;
            }
            else if (r == 7) {
                board[r][c].color = B;
            }
            else {
                board[r][c].id = ' ';
                board[r][c].color = ' ';
            }
        }
    }

    // Initializing the heavy pieces (white & black):
    board[0][0].id = 'R';
    board[0][1].id = 'N';
    board[0][2].id = 'B';
    board[0][3].id = 'Q';
    board[0][4].id = 'K';
    board[0][5].id = 'B';
    board[0][6].id = 'N';
    board[0][7].id = 'R';

    board[7][0].id = 'R';
    board[7][1].id = 'N';
    board[7][2].id = 'B';
    board[7][3].id = 'Q';
    board[7][4].id = 'K';
    board[7][5].id = 'B';
    board[7][6].id = 'N';
    board[7][7].id = 'R';

}

//  Recall [0][0] -> A1 & [4][3] -> D5
void printBoard() {
    // Top padding:
    printf("%s_________________\n", WHT);
    for (int row = 7; row >= 0; row--) { // Row counter, i.e. 0 - 7 -> A - H
        for (int col = 0; col <= 7; col++) {
            if (board[row][col].color == B)
                printf("%s|%s%c", WHT, YLW, board[row][col].id);
            else if (board[row][col].color == W)
                printf("%s|%s%c", WHT, LGN, board[row][col].id);
            else printf("%s| ", WHT);
            /* simz089s's printing w/ background printing implemented -might be useful later
            if ((row+col)%2 == 0)
                printf("%s%s|%s%s%c", DBG, DGR, board[row][col].color=='B'?RED:BLU, BBG, board[row][col].id);
            else
                printf("%s%s|%s%s%c", DBG, DGR, board[row][col].color=='W'?BLU:RED, WBG, board[row][col].id);
            */
        }
        printf("%s|\n", WHT);
    }
    // Bottom padding:
    printf("%s¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯%s\n", YLW, LGR);
}



int main() {
 
    /* Sanity check for clean_board:
    printf("A8's id is: \033[1;37m%c\033[0m\nD7's id is: \033[1;30m%c\033[0m\n", A8.id, D7.id);
    printf("A1's id is %c, it's color is %c\n", row1[0].id, row1[0].color);
    printf("Size is: %d\n", sizeof(board[6][0].id)); 
    printf("A7's id is %c, it's color is %c\n", board[6][0].id, board[6][0].color);*/

    // Setting up an empty board:
    initializeBoard();

    // Printing the current board state:
    printBoard();

    // No errors encountered
    return 0;
}