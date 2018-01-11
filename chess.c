/*  Bash terminal chess program
 *  Made by Daniel Busuttil and Simon Zheng, 2017
 *  Most recent update: 10, Jan '18 */

/*  TO DO (10 Jan):
 *  1. Distinguish between different invalid move types (change error codes to not JUST be -1)
 *  2. Implement a feature to allow for multiple 'saved' game states to choose between 
 *  3. Have students test the application and survey for potential feedback
 *  4. Implement network capability to allow for 'truly' multiplayer game
*/

//  Header file containing all the pertinent declarations and include statements
#include "chess.h"

/*  A 2D array which will capture the board state.
 *  Format is as follows: [Row][Column], i.e. [0][0] -> A1 & [5][3] -> D6 */
Cell board[8][8];

//  Initiliaze an empty board-state:
void initializeBoard() {
    //  Initializing the color of all tiles and the id of the pawns:
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

    // Initializing white's heavy pieces:
    board[0][0].id = 'R';
    board[0][1].id = 'N';
    board[0][2].id = 'B';
    board[0][3].id = 'Q';
    board[0][4].id = 'K';
    board[0][5].id = 'B';
    board[0][6].id = 'N';
    board[0][7].id = 'R';

    //  Initializing black's heavy pieces:
    board[7][0].id = 'R';
    board[7][1].id = 'N';
    board[7][2].id = 'B';
    board[7][3].id = 'Q';
    board[7][4].id = 'K';
    board[7][5].id = 'B';
    board[7][6].id = 'N';
    board[7][7].id = 'R';
}

/*  Function that will print the current board state, using yellow to represent 
 *  the black pieces and lime to represent the white pieces. Note, we decided
 *  on this color scheme as our terminal background is black and it would be
 *  hard to make out the pieces with the traditional color scheme. */
void printBoard() {
    puts("Board state:\n");
    //  Top 'padding':
    printf("%s   _________________\n", WHT);
    for (int row = 7; row >= 0; row--) { //  Row counter, i.e. 0 - 7 -> A - H
    printf("%s%d  %s", LGR, ( row + 1 ), WHT ); //  Print the rank 'markers'
        for (int col = 0; col <= 7; col++) {
            if ( board[row][col].color == B )
                printf( "%s|%s%c", WHT, YLW, board[row][col].id );
            else if ( board[row][col].color == W )
                printf( "%s|%s%c", WHT, LGN, board[row][col].id );
            else printf( "%s| ", WHT );
        }
        printf("%s|\n", WHT);
    }
    //  Bottom padding:
    printf("%s   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯%s\n", YLW, LGR);
    puts("    A B C D E F G H \n"); //  Print the file 'markers'
}

//  Check if input is in format "A1,B2"
bool validInput(char input[5]) {
    if ( input[0] >= 'A' && input[0] <= 'H' &&
         input[1] >= '1' && input[1] <= '8' &&
         input[3] >= 'A' && input[3] <= 'H' &&
         input[4] >= '1' && input[4] <= '8' ) return true;
    return false;
}

//  Call-by-reference function to assign values to the int appropriately
void parseInput(char* pre, int* num1, int* num2, int* num3, int* num4) {
    *num1 = *pre - 'A'; //  Normalizes a char 'A' to an int 0
    *num2 = *(pre + 1) - '1'; //  Normalizes a char '1' to an int 0
    *num3 = *(pre + 3) - 'A';
    *num4 = *(pre + 4) - '1';
}

/*  Functions relating to movePiece (general function which handles moving
 *  a given piece on the board) and it's various components: */

        //  Function to turn given cell, board[y][x], to a 'blank'/empty cell
        void blank(int x, int y) {
            board[y][x].id = ' ';
            board[y][x].color = ' ';
        }

        /*  Function to be called whenever a piece moves successfully to it's destination;
         *  will replace the dest. cell with info at the source (x1, y1) cell, 'wiping' it
         *  afterwards */
        void moveSuccess(int x1, int y1, int x2, int y2) {
            board[y2][x2] = board[y1][x1];
            blank(x1, y1); //  Set board[x1][y1] to a 'blank cell'
        }

        //  Function to check if (x1, y1) can capture a piece at (x2, y2)
        int canCapture(int x1, int y1, int x2, int y2) { 
            return ( board[y1][x1].color == B && board[y2][x2].color == W ) ||
                ( board[y1][x1].color == W && board[y2][x2].color == B );
        }

        //  Function to return the 2-dimensional Euclidian distance
        int distance(int x1, int y1, int x2, int y2) {
            int xDiff = ( x1 - x2 );
            int yDiff = ( y1 - y2 );
            int xSq = xDiff * xDiff;
            int ySq = yDiff * yDiff;
            return sqrt( xSq + ySq );
        }

        void pawnPromote(int x1, int y1) {
                 if ( ( board[y1][x1].color == W && y1 == 6 ) ||
                      ( board[y1][x1].color == B && y1 == 1 ) ) {
                    puts("\nWhat would you like to promote your pawn to? Please choose from: 'N', 'B', 'Q' or 'R'");
                    char choice = getchar();
                    while ( (choice != 'N' && choice != 'B' && choice != 'Q' && choice != 'R') ) {
                        puts("Please input 'N', 'B', 'Q' or 'R' (without the single-quotes)");
                        choice = getchar();
                    }
                    puts("");
                    board[y1][x1].id = choice;
                }
        }

        /*  As a reminder of the format, the move "B8,A1" would translate to a function call of:
         *  movePawn( 1, 7, 0, 0 ). The function will return -1 if the move is invalid for ANY reason. */
        int movePawn(int x1, int y1, int x2, int y2) {
            //  Pawns can never move backwards:
            if ( ( board[y1][x1].color == W && y2 < y1 ) ||
                 ( board[y1][x1].color == B && y2 > y1 ) ) return -1; 
            
            int yDistSq = ( y2 - y1 ) * ( y2 - y1 );
            //  If it is their first move, Pawns can either move 1 or two ranks (within their own file)
            if ( ( board[y1][x1].color == W && y1 == 1 ) ||
                 ( board[y1][x1].color == B && y1 == 6 ) ) {
                if ( yDistSq != 1 && yDistSq != 4 ) return -1;
            }
            else {
                //  Pawns can only ever move up/down one rank (if it's not their first move) so:
                if ( yDistSq != 1 ) return -1;
            }

            //  Without capture a Pawn can only move (progressively) within its own file:
            if ( x1 == x2 && board[y2][x2].id == ' ') {
                //  Check if the pawn can promote itself:
                pawnPromote(x1, y1);
                //  After checking, successfully move the Pawn:
                moveSuccess(x1, y1, x2, y2);
            }
            //  Check if capture is possible and capture if so:
            else if ( (x2 == (x1 + 1) || x2 == (x1 - 1) ) ) {
                if ( canCapture(x1, y1, x2, y2) ) {
                    pawnPromote(x1, y1);
                    moveSuccess(x1, y1, x2, y2);
                }
                //  Error code if move was invalid due to attempting to capture own piece
                else return -2;
            }
            else return -1;

            /*  No errors were found while the move was processed
             *  No pieces were harmed in the making of this program.
             *  This is a personal project. Any ressemblance to real pieces is purely coincidental.
             *  Please do not attempt any of the invalid moves at /home/. */
            return 0;
        }

        /*  Bishops can move diagonally but, mathematically, their four directions have unique
         *  properties for correctness. Moving clockwise around a circle (a 90 turn each time),
         *  these four direction are marked Q1-Q4 below: */
        int moveBishop(int x1, int y1, int x2, int y2) {
            if ( x1 == x2 || y1 == y2 ) return -1;
            else if ( x2 > x1 ) {
                //  Q1: ( x2 > x1 ) && ( y2 > y1 )
                if ( y2 > y1 ) {
                    if ( x2 == x1 + (y2 - y1) ) {
                        //  Ccheck if there are any pieces 'in the way' of the Bishop:
                        int j = y1 + 1;
                        int i = x1 + 1;
                        for ( ; i < x2 && j < y2 ; i++, j++ ) {
                            if ( board[j][i].id != ' ' ) return -4;
                        }
                        //  Complete succes if next guard is passed:
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -2;
                    }
                    else return -1;
                }
                //  Q2: ( x2 > x1 ) && ( y1 > y2 )
                else {
                    if ( x2 == x1 + (y1 - y2) ) {
                        //  Ditto as with Q1 but now we decrement j:
                        int j = y1 - 1;
                        int i = x1 + 1;
                        for ( ; i < x2 && j > y2 ; i++, j-- ) {
                            if ( board[j][i].id != ' ' ) return -4;
                        }
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -2;
                    }
                    else return -1;
                }
            }
            else {
                //  Q3: ( x1 > x2 ) && ( y2 > y1 )
                if ( y2 > y1 ) {
                    if ( x1 == x2 + (y2 - y1) ) {
                        //  Now we decrement i & not j:
                        int j = y1 + 1;
                        int i = x1 - 1;
                        for ( ; i > x2 && j < y2 ; i--, j++ ) {
                            if ( board[j][i].id != ' ' ) return -4;
                        }
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -2;
                    }
                    else return -1;
                }
                //  Q4: ( x1 > x2 ) && ( y1 > y2 )
                else {
                    if ( x1 == x2 + (y1 - y2) ) {
                        //  Decrement both now:
                        int j = y1 - 1;
                        int i = x1 - 1;
                        for ( ; i > x2 && j > y2 ; i--, j-- ) {
                            if ( board[j][i].id != ' ' ) return -4;
                        }
                        if ( board[y2][x2].id == ' ' ||
                            canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                        else return -2;
                    }
                    else return -1;
                }
            }

            //  No errors were found while the move was processed
            return 0;
        }

        int moveRook(int x1, int y1, int x2, int y2) {
            /*  When a Rook (correctly) moves, it can either move horizontally
             *  or vertically, therefore: */
            if (x1 != x2 && y1 != y2 ) return -1;

            //  Rook is moving vertically
            if ( x1 == x2 ) {
                //  Like the Bishop, we need to check if there are any pieces 'in the way':
                if ( y2 > y1 ) {
                    int j = y1 + 1;
                    for ( ; j < y2 ; j++ ) {
                        if ( board[j][x1].id != ' ' ) return -4;
                    }
                }
                else {
                    int j = y1 - 1;
                    for ( ; j > y2 ; j-- ) {
                        if ( board[j][x1].id != ' ' ) return -4;
                    }
                }
                if ( board[y2][x2].id == ' ' ||
                    canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -2;
            }
            //  Rook is moving horizontally
            else {
                if ( x2 > x1 ) {
                    int i = x1 + 1;
                    for ( ; i < x2 ; i++ ) {
                        if ( board[y1][i].id != ' ' ) return -4;
                    }
                }
                else {
                    int i = x1 - 1;
                    for ( ; i > x2 ; i-- ) {
                        if ( board[y1][i].id != ' ' ) return -4;
                    }
                }
                if ( board[y2][x2].id == ' ' ||
                    canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -2;
            }

            //  No errors were found while the move was processed
            return 0;
        }

        /*  Queens move as either Bishops or Rooks and since both those pieces have
         *  distinct requirements for their moves to be valid, and due to the nature
         *  of moveSuccess()'s ability to accept any piece (regardless of it's id),
         *  we can simply call the requisite function once we determine how the
         *  Queen is going to be moved. */
        int moveQueen(int x1, int y1, int x2, int y2) {
            if ( x1 == x2 || y1 == y2 ) return moveRook(x1, y1, x2, y2);
            else return moveBishop(x1, y1, x2, y2); 
        }

        //  Kings will move like Queens (i.e. akin to Bishops or Rooks), but only 1 tile at a time. 
        int moveKing(int x1, int y1, int x2, int y2) {
            int move = distance(x1, y1, x2, y2);
            /*  If the King moves as a Rook then the distance is simple:
             *  it'll be 1. However if it movs as a Bishop then the
             *  distance will be sqrt(2). Thus: */
            if ( move == sqrt(2) || move == 1 ) {
                if ( board[y2][x2].id == ' ' ||
                    canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -2;
            }
            else return -1;

            //  No errors were found so we return 0
            return 0;
        }

        int moveKnight(int x1, int y1, int x2, int y2) {
            if ( x1 == x2 || y1 == y2 ) return -1;
            /*  Knights will always move in an 'L-shape' which means that the Euclidean
             *  distance should be 5 ^ 0.5. However to avoid problems with floating point
             *  values, we'll be comparing the squares (instead of the square roots): */
            int xDistSq = ( x2 - x1 ) * ( x2 - x1 );
            int yDistSq = ( y2 - y1 ) * ( y2 - y1 );
            if ( ( xDistSq == 1 && yDistSq == 4 ) ||
                 ( xDistSq == 4 && yDistSq == 1 ) ) {
                if ( board[y2][x2].id == ' ' ||
                     canCapture(x1, y1, x2, y2) ) moveSuccess(x1, y1, x2, y2);
                else return -2;
            }
            else return -1;

            //  No errors were encountered so we return 0
            return 0;
        }

        /*  Format: (x1, y1) is the current position while (x2, y2) is the requested destination;
         *  Note: x <--> columns/letters/files, y <--> rows/numbers/ranks */
        int movePiece(int x1, int y1, int x2, int y2) {
            //  Check if destination is invalid (due to the board's dimensions):
            if ( ( y2 >= 8 || x2 >= 8 || y2 < 0 || x2 < 0 ) ||
                ( x1 == x2 && y1 == y2 ) ) {
                printf("What you have entered is %soutside of the board%s, please try again!\n\n", ULN, NULN);
                return -5;
            }
            //  Check if source is invalid:
            else if ( board[y1][x1].id == ' ' ) {
                printf("There is %sno piece on that tile%s, please try again!\n\n", ULN, NULN);
                return -3;
            }

            int errCode;
            
            /*  We now check what the piece's id is and pass it the
             *  coordinates along to the appropriate function */
            if ( board[y1][x1].id == 'P') {
                //  Success:
                if ( ( errCode = movePawn(x1, y1, x2, y2) ) == 0 ) return 0;
                //  Failure:
                else if ( errCode == -2 ) {
                    printf("You cannot capture your %sown piece%s, please try again!\n\n", ULN, NULN);
                    return -2;
                }
                else return -1;
            }
            else if ( board[y1][x1].id == 'R') {
                //  Success:
                if ( ( errCode = moveRook(x1, y1, x2, y2) ) == 0 ) return 0;
                //  Failure:
                else if ( errCode == -2 ) {
                    printf("You cannot capture your %sown piece%s, please try again!\n\n", ULN, NULN);
                    return -2;
                }
                else if (errCode == -4) {
                    printf("There is a %spiece in the way%s, please try again!\n\n", ULN, NULN);
                    return -4;
                }
                else return -1;
            }
            else if ( board[y1][x1].id == 'B') {
                //  Success:
                if ( ( errCode = moveBishop(x1, y1, x2, y2) ) == 0 ) return 0;
                //  Failure:
                else if ( errCode == -2 ) {
                    printf("You cannot capture your %sown piece%s, please try again!\n\n", ULN, NULN);
                    return -2;
                }
                else if (errCode == -4) {
                    printf("There is a %spiece in the way%s, please try again!\n\n", ULN, NULN);
                    return -4;
                }
                else return -1;
            }
            else if ( board[y1][x1].id == 'Q') {
                //  Success:
                if ( ( errCode = moveQueen(x1, y1, x2, y2) ) == 0 ) return 0;
                //  Failure:
                else if ( errCode == -2 ) {
                    printf("You cannot capture your %sown piece%s, please try again!\n\n", ULN, NULN);
                    return -2;
                }
                else if (errCode == -4) {
                    printf("There is a %spiece in the way%s, please try again!\n\n", ULN, NULN);
                    return -4;
                }
                else return -1;
            }
            else if ( board[y1][x1].id == 'K') {
                //  Success:
                if ( ( errCode = moveKing(x1, y1, x2, y2) ) == 0 ) return 0;
                //  Failure:
                else if ( errCode == -2 ) {
                    printf("You cannot capture your %sown piece%s, please try again!\n\n", ULN, NULN);
                    return -2;
                }
                else return -1;
            }
            else if ( board[y1][x1].id == 'N') {
                //  Success:
                if ( ( errCode = moveKnight(x1, y1, x2, y2) ) == 0 ) return 0;
                //  Failure:
                else if ( errCode == -2 ) {
                    printf("You cannot capture your %sown piece%s, please try again!\n\n", ULN, NULN);
                    return -2;
                }
                else return -1;
            }

            /*  This should never be reached but to account for a bug
             *  or other strange occurence: */
            else {
                puts("Something strange happened with that piece's id");
                return -1;
            }
        }

//  End of code relating to movePiece and it's supporting functions


/*  Function to rebuild a game from a previous logfile. Note that only the most
 *  immediate/recent game can be saved which means that, currently a player must
 *  choose between continuing a previous game or deleting it and starting a new
 *  one: */
int rebuildBoard(const char* path, char* turn, int* tCounter) {
    char command[6];
    int x1;
    int y1;
    int x2;
    int y2;
    FILE* fPtr = fopen(path, "rt");
    if ( fPtr == NULL ) {
        puts("Something went wrong, the move log file could not be read");
        return -1;
    }
    else {
        char symbol = '\0';
        FILE* mh = fopen("move_history.txt", "at");

        do {
            fgets( command, sizeof(command), fPtr );
            if ( validInput(command) ) {
                parseInput( command, &x1, &y1, &x2, &y2 );
                /*  We'd like the move history of the previous game to continue into this one; Note
                 *  we don't need to wipe it because we only call this function after already wiping it.
                 *  We need to set up the requisite helper chars/ints for printing to move_history.txt */
                symbol = board[y1][x1].id;
                movePiece( x1, y1, x2, y2 );
                /*  In case one of the players wants to view the move history of the 
                 *  game, this function rebuilds the move_history.txt file. This is an
                 *  important utility we feel as it is possible that games are played
                 *  over days possibly */
                fprintf(mh, "%d. %c%c(%c%c) to %c%c,\n", *tCounter,
                        ( x1 + 'A' ), ( y1 + '1' ), *turn, symbol,
                        ( x2 + 'A' ), ( y2 + '1' ));
                /*  tCounter and turn are also reconstructed so that the complete image/snapshot of the
                 *  previous boardstate (both visual and mechanical) is fully rebuilt */
                (*tCounter)++;
                *turn = ( *tCounter % 2 == 0 ? B : W );
            }
        } while ( !feof(fPtr) );
        fclose(mh);
    }
    puts("Your game is rebuilt!");
    fclose(fPtr);
    return 0;
}


int main(void) {

    //  Setting up an empty board:
    initializeBoard();

    //  Integer to store the menu of options
    int choice = -1;

    //  Char used to keep or discard the logfile (different from move_history.txt):
    char logKeep = '\0';

    //  Bool to escape while loop later
    bool play = true;

    //  Char to store turn order, W == White's turn, B == Black's turn
    char turn = W;

    //  Int used in fprinting the move history
    int tCounter = 1;

    //  String containing the user's request; format for user input string is: "A1,A5"
    char target[6];
    /*  Note that x-coordinates are used in the second dimension, while
     *  while y-coordinates are used in the first. I.e. D8 is board[7][3]
     *  Board looks like this:
     *  { y0={ x0, ..., xn },
     *    y1={ x0, ..., xn },
     *    y2={ x0, ..., xn } } */

    /*  We initialize the variables at -1 so that movePiece's inherent
     *  error handling will catch a situation where, somehow, our I/O
     *  is incorrect */
    int x1 = -1;
    int y1 = -1;
    int x2 = -1;
    int y2 = -1;

    //  Erase previous game's move history
    fclose(fopen("move_history.txt", "wt"));

    //  Offer to recreate/resume previous game from existing log-file:
    FILE* check = fopen("move_log.txt", "rt");
    if ( !check ) puts("There is no previous logfile available, enjoy your game and good luck!");
    else {
        char logChoice = '\0';
        puts("Log file is not empty, would you like to rebuild from a previous game? Y/n");
        logChoice = getchar();
        /*  We felt it would be useful to have a user enter a capital 'Y' or a lowecase 'n'
         *  to further distinguish the two as the possible consequence of an error on the user's
         *  part would result in the erasure of their previous game */
        while ( logChoice != 'Y' && logChoice != 'n' ) {
            puts("Please input either 'Y' or 'n' (without the single quotes):");
            while ( logChoice != '\n' && logChoice != '\0' ) logChoice = getchar();
            logChoice = getchar();
        }
        if ( logChoice == 'Y') rebuildBoard("move_log.txt", &turn, &tCounter);
        else puts("Understood, here is your fresh game, good luck and have fun!");
        puts("");
    }

    //  Game's loop
    while ( play ) {
        printBoard();
        puts("\n\nPlease type a number corresponding to one of the following options:");
        puts("\t1. Print the board");
        puts("\t2. Make a move");
        puts("\t3. Concede");
        puts("\t4. See move history");

        //  Take in user input:
        while ( scanf("%d", &choice) != 1 || choice < 1 || choice > 4 ) {
            do {
                choice = getchar();
            } while (choice != '\n' && choice != EOF);
            puts("Please input choice 1, 2, 3, 4 or 5.");
        }
        puts("");

        //  Switch statements so we can act based on the user's input
        switch ( choice ) {
            //  User wants the board state to be printed:
            case 1 :
                printBoard();
                break;

            //  User wants to move a piece:
            case 2 :
                printf("It is %s's turn right now. ", ( turn == W ? "White" : "Black" ) );
                do {
                    puts("Please enter a move & follow this format 'A5,B8':");
                    puts("\tA valid move is from A-H (column/file) & 1-8 (row/rank)");
                    scanf("%5s", target);
                    do {
                        target[5] = getchar();
                    } while (target[5] != '\n' && choice != EOF);
                    target[5] = '\0';
                } while ( !validInput(target) );
                //  Use the newly filled array, target, to assign values to the variables:
                parseInput( target, &x1, &y1, &x2, &y2 );

                //  To make sure pieces are only moved on their own turn:
                if ( turn == board[y1][x1].color ) {
                    char symbol = board[y1][x1].id;
                    int errCode = 1;
                    /*  Possible error codes from movePiece:
                     *   -1 -> Move was invalid for some miscellaneous reason (too general for it's own code),
                     *   -2 -> User tried to capture their own piece,
                     *   -3 -> User input an empty tile as a source tile,
                     *   -4 -> There was a piece in between the source and destination tiles,
                     *             (Note, this applies only to Bishop, Rook and Queen)
                     *   -5 -> User tried to move outside the bounds of the board */
                    
                    if ( ( errCode = movePiece(x1, y1, x2, y2) ) != 0 ) {
                        if ( errCode == -1) puts("Your move is invalid, please try again!\n");
                    }
                    else {
                        //  Record move made with a file pointer in append-mode:
                        FILE* mh = fopen("move_history.txt", "at");
                        fprintf(mh, "%d. %c%c(%c%c) to %c%c,\n", tCounter,
                                ( x1 + 'A' ), ( y1 + '1' ), turn, symbol,
                                ( x2 + 'A' ), ( y2 + '1' ));
                        fclose(mh);
                        //  Record move for (possible) reconstruction purposes:
                        FILE* ml = fopen("move_log.txt", "at");
                        fprintf(ml, "%c%c,%c%c\n",
                                ( x1 + 'A' ), ( y1 + '1' ),
                                ( x2 + 'A' ), ( y2 + '1' ) );
                        fclose(ml);
                        tCounter++;
                        //  Switch turns if move was successful:
                        if ( turn == W ) turn = B;
                        else turn = W;
                    }
                }
                else printf("It is %s's turn right now so that piece can't move yet.\n\n", ( turn == W ? "White" : "Black" ) );
                break;

            //  User wants to exit:
            case 3 :
                printf("Game over, %s won!\n", ( turn == W ? "White" : "Black" ) );
                printBoard();
                puts("");
                play = false;

                puts("Would you like to keep the log-file? 'Y' or 'n'");
                /*  We do an extra getchar here to remove the newline left in stdin from
                 *  scanf'ing an int (when we used scanf to get a value for choice) as
                 *  well as accounting for the possibility that of user doesn't input anything */
                logKeep = getchar();
                while ( logKeep == '\n' ) {
                    logKeep = getchar();
                }
                while ( logKeep != 'Y' && logKeep != 'n' ) {
                    puts("Please input either 'Y' or 'n' (without the single quotes):");
                    while ( logKeep != '\n' && logKeep != '\0' ) logKeep = getchar();
                    logKeep = getchar();
                }
                puts("");

                break;

            //  Want to print/see move history of the game
            case 4 :
            {
                //  Open a FILE ptr to read & print move history:
                FILE* rp = fopen("move_history.txt", "rt");
                if ( feof(rp) || rp == NULL ) puts("The move history does not exist.");
                else {
                    char line[20] = "";
                    fgets(line, sizeof(line), rp);
                    //  Guard against an empty file:
                    if ( strncmp(line, "", 1) == 0 ) puts("No moves have been played yet!");
                    else puts("Here is the move history:");
                    while ( !feof(rp) && rp != NULL ) {
                        printf("%s", line);
                        fgets(line, sizeof(line), rp);
                    }
                }
                fclose(rp);
                break;
            }
            
            //  If for some reason even the input check fails
            default :
                puts("Something went wrong with input checking...");
                exit(-1);
        }
        puts("\n--------------------------------------------------------------------------------\n");
    }

    /*  If player doesn't want to keep the log file, we delete it. It is
     *  important to delete it (not overwrite it) so that the next time
     *  the user launches our program, the game will know whether there
     *  is a previous game state to load or not. */
    if ( logKeep == 'n' ) system("rm -f move_log.txt");

    //  No errors encountered during the execution of the program:
    return EXIT_SUCCESS;
}