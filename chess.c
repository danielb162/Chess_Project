#include "chess.h"

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

// [Row][Column], i.e. [0][0] -> A1 & [5][3] -> D6
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
    printf("%s¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯%s\n\n", YLW, LGR);
}

// Call-by-reference function to assign values to the int arrays appropriately
void parseInput(char* pre, int* num1, int* num2) {
    char temp = *pre;
    //*num1 = atoi(temp); // Will transform the char into a 0 - 7 int
    //*num2 = atoi(*( pre + 1 )) - 1; // Ditto
}

// Need to sort out later - TEMPORARILY from pieceRules.c:

        // Function to turn given cell, board[x][y], to a 'blank' cell
        void blank(int x, int y) {
            board[y][x].id = ' ';
            board[y][x].color = ' ';
        }

        /*  Function to be called whenever a piece moves successfully to it's destination;
            will replace the dest. cell with info @ source cell and 'wipe' source cell */
        void moveSuccess(int x1, int y1, int x2, int y2) {
            board[y2][x2] = board[y1][x1];
            blank(x1, y1); // Set board[x1][y1] to a 'blank cell'
        }

        // Function to check if (x1, y1) can capture a piece at (x2, y2)
        int canCapture(int x1, int y1, int x2, int y2) { 
            return ( board[y1][x1].color == B && board[y2][x2].color == W ) ||
                ( board[y1][x1].color == W && board[y2][x2].color == B );
        }

        // Function to return the 2-dimensional Euclidian distance
        int distance(int x1, int y1, int x2, int y2) {
            int xDiff = ( x1 - x2 );
            int yDiff = ( y1 - y2 );
            int xSq = xDiff * xDiff;
            int ySq = yDiff * yDiff;
            return sqrt( xSq + ySq );
        }

        /* SUGGESTION: Return bool instead of int? */
        // Returns -1 if for ANY reason move is invalid
        int movePawn(int x1, int y1, int x2, int y2) {
            // Pawns can only ever move up/down one row so these act as general checks:
            if ( ( board[y1][x1].color == W && y2 != (y1 + 1) ) ||
                ( board[y1][x1].color == B && y2 != (y1 - 1) ) ) return -1;
            // Without capture pawn can only move (progressively) within it's rank:
            else if ( x1 == x2 && board[y2][x2].id == ' ') {
                moveSuccess(x1,y1, x2, y2);
            }
            // Check if capture is possible and capture if so:
            else if ( (x2 == (x1 + 1) || x2 == (x1 - 1) ) ) {
                if ( canCapture(x1, y1, x2, y2) ) {
                    moveSuccess(x1, y1, x2, y2);
                }
                else return -1;
            }
            else return -1;

            // No errors were found while the move was processed
            /* No pieces were harmed in the making of this program.
            * This is a personal project. Any ressemblance to real pieces is purely coincidental.
            * Please do not attempt any of the invalid moves at /home/. */
            return 0;
        }

        /*  Bishops can move diagonally but, mathematically, their four directions have unique
            properties for correctness. These four direction are marked Q1-Q4 below: */
        int moveBishop(int x1, int y1, int x2, int y2) {
            if ( x1 == x2 || y1 == y2 ) return -1;
            else if ( x2 > x1 ) {
                // Q1: ( x2 > x1 ) && ( y2 > y1 )
                if ( y2 > y1 ) {
                    if ( x2 == x1 + (y2 - y1) ) {
                        // Need to check if there are any pieces 'in the way':
                        int j = y1 + 1;
                        int i = x1 + 1;
                        for ( ; i < x2 && j < y2 ; i++, j++ ) {
                            if ( board[j][i].id != ' ' ) return -1;
                            // i++;
                            // j++;
                        }
                        // Complete succes if next guard is passed:
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -1;
                    }
                    else return -1;
                }
                // Q2: ( x2 > x1 ) && ( y1 > y2 )
                else {
                    if ( x2 == x1 + (y1 - y2) ) {
                        // Ditto as with Q1 but now we decrement j:
                        int j = y1 - 1;
                        int i = x1 + 1;
                        for ( ; i < x2 && j > y2 ; i++, j-- ) {
                            if ( board[j][i].id != ' ' ) return -1;
                            // i++;
                            // j--;
                        }
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -1;
                    }
                    else return -1;
                }
            }
            else {
                // Q3: ( x1 > x2 ) && ( y2 > y1 )
                if ( y2 > y1 ) {
                    if ( x1 == x2 + (y2 - y1) ) {
                        // Now we decrement i & not j:
                        int j = y1 + 1;
                        int i = x1 - 1;
                        for ( ; i > x2 && j < y2 ; i--, j++ ) {
                            if ( board[j][i].id != ' ' ) return -1;
                            // i--;
                            // j++;
                        }
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -1;
                    }
                    else return -1;
                }
                // Q4: ( x1 > x2 ) && ( y1 > y2 )
                else {
                    if ( x1 == x2 + (y1 - y2) ) {
                        // Decrement both now:
                        int j = y1 - 1;
                        int i = x1 - 1;
                        for ( ; i > x2 && j > y2 ; i--, j-- ) {
                            if ( board[j][i].id != ' ' ) return -1;
                            // i--;
                            // j--;
                        }
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -1;
                    }
                    else return -1;
                }
            }

            // No errors were found while the move was processed
            return 0;
        }

        int moveRook(int x1, int y1, int x2, int y2) {
            // Either x1 == x2 or y1 == y2 when a rook moves thus:
            if (x1 != x2 && y1 != y2 ) return -1;

            // Rook is moving vertically
            if ( x1 == x2 ) {
                // Like the bishop, we need to check if there are any pieces 'in the way':
                if ( y2 > y1 ) {
                    int j = y1 + 1;
                    for ( ; j < y2 ; j++ ) {
                        if ( board[j][x1].id != ' ' ) return -1;
                        // j++;
                    }
                }
                else {
                    int j = y1 - 1;
                    for ( ; j > y2 ; j-- ) {
                        if ( board[j][x1].id != ' ' ) return -1;
                        // j--;
                    }
                }
                if ( board[y2][x2].id == ' ' ||
                    canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            // Rook is moving horizontally
            else {
                if ( x2 > x1 ) {
                    int i = x1 + 1;
                    for ( ; i < x2 ; i++ ) {
                        if ( board[y1][i].id != ' ' ) return -1;
                        // i++;
                    }
                }
                else {
                    int i = x1 - 1;
                    for ( ; i > x2 ; i-- ) {
                        if ( board[y1][i].id != ' ' ) return -1;
                        // i--;
                    }
                }
                if ( board[y2][x2].id == ' ' ||
                    canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }

            // No errors were found while the move was processed
            return 0;
        }

        /*  Queens move as either Bishops or Rooks and since both those pieces have
        *  distinct requirements for their moves to be valid, and due to the nature
        *  of moveSuccess, we can simply call the requisite function once we
        *  determine how the Queen is going to be moved. */
        int moveQueen(int x1, int y1, int x2, int y2) {
            if ( x1 == x2 || y1 == y2 ) return moveRook(x1, y1, x2, y2);
            else return moveBishop(x1, y1, x2, y2); 
        }

        // Kings will move like Queens (i.e. like Bishops OR Rooks, but only 1 tile at a time. 
        int moveKing(int x1, int y1, int x2, int y2) {
            int move = distance(x1, y1, x2, y2);
            /* If the King moves as a Rook then the
            distance is simple: it'll be 1. However if it movs as a Bishop
            then the distance will be sqrt(2). Thus: */
            if ( move == sqrt(2) || move == 1 ) {
                if ( board[y2][x2].id == ' ' ||
                    canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            else return -1;

            return 0;
        }

        int moveKnight(int x1, int y1, int x2, int y2) {
            if ( x1 == x2 || y1 == y2 ) return -1;
            /* Knights will always move in an 'L-shape' which means that the Euclidean
             * distance should be 5 ^ 0.5. However to avoid problems with floating point
             * values, we'll be comparing the squares (instead of the square roots): */
            int xDistSq = ( x2 - x1 ) * ( x2 - x1 );
            int yDistSq = ( y2 - y1 ) * ( y2 - y1 );
            if ( ( xDistSq == 1 && yDistSq == 4 ) ||
                 ( xDistSq == 4 && yDistSq == 1 ) ) {
                if ( board[y2][x2].id == ' ' ||
                     canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            else return -1;

            return 0;
        }

        /* Format: (x1, y1) is the current position while (x2, y2) is the requested destination;
        * nb: x <--> columns/letters, y <--> rows/numbers */
        int movePiece(int x1, int y1, int x2, int y2) {
            // Check if dest. is invalid (due to the board's dimensions):
            if ( ( y2 >= 8 || x2 >= 8 || y2 < 0 || x2 < 0 ) ||
                ( x1 == x2 && y1 == y2 ) ) return -1;
            // Check if source is invalid:
            else if ( board[y1][x1].id == ' ' ) {
                puts("There is no piece on that tile.");
                return -1;
            }
            
            // Do not refactor redundancy as there may be work to do depending on success or fail
            // UPDATE feedback from calling all move functions
            if ( board[y1][x1].id == 'P') {
                // Success:
                if ( movePawn(x1, y1, x2, y2) == 0 ) return 0;
                // Failure:
                else return -1;
            }
            else if ( board[y1][x1].id == 'R') {
                // Success:
                if ( moveRook(x1, y1, x2, y2) == 0 ) return 0;
                // Failure:
                else return -1;
            }
            else if ( board[y1][x1].id == 'B') {
                // Success:
                if ( moveBishop(x1, y1, x2, y2) == 0 ) return 0;
                // Failure:
                else return -1;
            }
            else if ( board[y1][x1].id == 'Q') {
                // Success:
                if ( moveQueen(x1, y1, x2, y2) == 0 ) return 0;
                // Failure:
                else return -1;
            }
            else if ( board[y1][x1].id == 'K') {
                // Success:
                if ( moveKing(x1, y1, x2, y2) == 0 ) return 0;
                // Failure:
                else return -1;
            }
            else if ( board[y1][x1].id == 'N') {
                // Success:
                if ( moveKnight(x1, y1, x2, y2) == 0 ) return 0;
                // Failure:
                else return -1;
            }
            else return -1;
        }

// End of code from pieceRules.c

int main(void) {
 
    /* Sanity check for clean_board:
    printf("A8's id is: \033[1;37m%c\033[0m\nD7's id is: \033[1;30m%c\033[0m\n", A8.id, D7.id);
    printf("A1's id is %c, it's color is %c\n", row1[0].id, row1[0].color);
    printf("Size is: %d\n", sizeof(board[6][0].id)); 
    printf("A7's id is %c, it's color is %c\n", board[6][0].id, board[6][0].color);*/

    // Setting up an empty board:
    initializeBoard();

    // Integer to store the menu of options
    int choice = -1;

    // Bool to escape while loop later
    bool play = true;

    // Char to store turn order, W == White's turn, B == Black's turn
    char turn = W;

    // String containing the user's request; format for user input string is: "A1,A5"
    char target[6];
    /*  Note that x-coordinates are used in the second dimension, while
     *  while y-coordinates are used in the first. I.e. D8 is board[7][3]
     *  Board looks like this:
     *  { y0={ x0, ..., xn },
     *    y1={ x0, ..., xn },
     *    y2={ x0, ..., xn } } */
    int x1 = -1;
    int y1 = -1;
    int x2 = -1;
    int y2 = -1;


    /* BUGS/CRASHES (1 - 3 have seemed to stop happening?):
        1. A6 was attempted as a valid move by a rook as the first move
        2. A6 was attempted as a valid move by a pawn as the fourth move
        3. A6 was attempted as a valid move by a bishop as the second move
        4. King works with floating points but Knight doesn't, moveKnight changed to account for this
    */

    while ( play ) {
        printBoard();
        puts("\n\nPlease select one of the following options:");
        puts("\t1. Print the board");
        puts("\t2. Make a move");
        puts("\t3. Concede");
        scanf("%d", &choice);
        puts("");
        switch ( choice ) {
            case 1 :
                printBoard();
                break;

            case 2 :
                printf("It is %s's turn right now. ", ( turn == W ? "White" : "Black" ) );
                puts("Please enter a move & follow this format 'A5,B8':");
                scanf("%5s", target);
                target[5] = '\0';
                x1 = *target - 'A'; // Normalizes a char 'A' to an int 0
                y1 = *(target + 1) - '1'; // Normalizes a char '1' to an int 0
                x2 = *(target + 3) - 'A';
                y2 = *(target + 4) - '1';
                /*printf("#1 as numbers is: [%d][%d]\n", y1, x1);
                printf("#2 as numbers is: [%d][%d]\n", y2, x2);*/
                if ( turn == board[y1][x1].color ) {
                    if ( movePiece(x1, y1, x2, y2) == -1 )
                        printf("There was a problem, please try again!\n\n");
                    else {
                        // Switch turns:
                        if ( turn == W ) turn = B;
                        else turn = W;
                    }
                }
                else printf("It is %s's turn right now so that piece can't move yet.\n\n", ( turn == W ? "White" : "Black" ) );
                break;

            case 3 :
                puts("Game over! Board state:");
                printBoard();
                puts("");
                play = false;
                break;
        }
        printf("\n\n\n\n\n\n\n");
    }

    // No errors encountered
    return EXIT_SUCCESS;
}