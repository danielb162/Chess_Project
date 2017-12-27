#include "chess.h"
#ifndef BOOLS
    #define BOOLS
    #define TRUE 1
    #define FALSE 0
#endif

// To check if code compiles we add this (normally would use extern/modular programming so this will be removed):
static const char B = 'B';
static const char W = 'W';
Cell board[8][8];
void main() {
}

/* TO DO:
    0.5: Update failure states for all 'move' functions
    1. Update moveKing to prevent moving into 'check'
    2. Incoperate 'strange' rules:
        https://en.wikipedia.org/wiki/En_passant
        https://en.wikipedia.org/wiki/Castling
    3. Add captured pieces to their respective arrays
    4. Whenever a move is made, record it in a text-file (with game ID?)
    5. Update return codes to explain to user better why their move wasn't valid (?)
*/


// Arrays to record the number of captured X pieces to be used later; max is 17 as King can't be captured
Cell capturedBlack[17];
Cell capturedWhite[17];

// Function to turn given cell, board[x][y], to a 'blank' cell
void blank(int x, int y) {
    board[x][y].id = ' ';
    board[x][y].color = ' ';
}

/*  Function to be called whenever a piece moves successfully to it's destination;
    will replace the dest. cell with info @ source cell and 'wipe' source cell */
void moveSuccess(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    blank(x1, y1); // Set board[x1][y2] to a 'blank cell'
}

// Function to check if (x1, y1) can capture a piece at (x2, y2)
int canCapture(int x1, int y1, int x2, int y2) { 
    if ( ( board[x1][y1].color == B && board[x2][y2].color == W ) || ( board[x1][y1].color == W && board[x2][y2].color == B ) ) return TRUE;
    else return FALSE;
}

// Function to return the 2-dimensional Euclidian distance
int distance(int x1, int y1, int x2, int y2) {
    int xSq = pow(( x1 - x2 ), 2);
    int ySq = pow(( y1 - y2 ), 2);
    return sqrt( xSq + ySq);
}


// Returns -1 if for ANY reason move is invalid
int movePawn(int x1, int y1, int x2, int y2) {
    // Pawns can only ever move up/down one row so these act as global checks:
    if ( ( board[x1][y1].color == W && y2 != (y1 + 1) ) || ( board[x1][y1].color == B && y2 != (y1 - 1) ) ) return -1;
    // Without capture pawn can only move (progressively) within it's rank:
    else if ( x1 == x2 && board[x2][y2].id == ' ') {
        moveSuccess(x1,y1, x2, y2);
    }
    // Check if capture is possible and capture if so:
    else if ( (x2 == (x1 + 1) || x2 == (x1 - 1) ) ) {
        if ( canCapture(x1, y1, x2, y2) == TRUE ) {
            moveSuccess(x1, y1, x2, y2);
        }
        else return -1;
    }
    else return -1;

    // No errors were found while the move was processed
    return 0;
}

int moveBishop(int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) return -1;
    else if ( x2 > x1 ) {
        // Q1: x2 > x1 && y2 > y1
        if ( y2 > y1 ) {
            if ( x2 == x1 + (y2 - y1) ) {
                if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            else return -1;
        }
        // Q2: x2 > x1 && y1 > y2
        else {
            if ( x2 == x1 + (y1 - y2) ) {
                if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            else return -1;
        }
    }
    else {
        // Q3: x1 > x2 && y2 > y1
        if ( y2 > y1 ) {
            if ( x1 == x2 + (y2 - y1) ) {
                if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            else return -1;
        }
        // Q4: x1 > x2 && y1 > y2
        else {
            if ( x1 == x2 + (y1 - y2) ) {
                if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
                else return -1;
            }
            else return -1;
        }
    }

    // No errors were found while the move was processed
    return 0;
}

int moveRook(int x1, int y1, int x2, int y2) {
    // One of these must be the same so:
    if (x1 != x2 && y1 != y2 ) return -1;

    if ( x1 == x2 ) {
        if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
        else return -1;
    }
    else if ( y1 == y2 ) {
        if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
        else return -1;
    }
    else return -1;

    // No errors were found while the move was processed
    return 0;
}

int moveQueen(int x1, int y1, int x2, int y2) {
    if ( x1 == x2 || y1 == y2 ) return moveRook(x1, y1, x2, y2);
    else return moveBishop(x1, y1, x2, y2); 
}

// Maybe replace below with a check for Euclidian distance using the distance functiong ?
int moveKing(x1, y1, x2, y2){
    // If the king is moving (vertically) as a rook would (but only by one tile):
    if ( x1 == x2 && ( ( y1 == y2 - 1 ) || ( y1 == y2 + 1 ) ) ) {
        return moveRook(x1, y1, x2, y2);
    }
    // Ditto as above but horizontally (split for readability):
    else if ( y1 == y2 && ( ( x1 == x2 - 1 ) || ( x1 == x2 + 1 ) ) ) {
        return moveRook(x1, y1, x2, y2);
    }
    // King is moving like a bishop (but only by one tile):
    else if ( x1 == x2 + 1 || x1 == x2 - 1 ) {
        if ( y1 == y2 + 1 || y1 == y2 - 1 ) {
            return moveBishop(x1, y1, x2, y2);
        }
        else return -1;
    }
    else return -1;
}

int moveKnight(int x1, int y1, int x2, int y2) {
    int flag = distance(x1, y1, x2, y2);
    // Knights will always move in an 'L-shape' which means that the distance should be 5^0.5
    if ( flag == sqrt(5) ) {
        if ( board[x2][y2].id == ' ' || canCapture(x1, y1, x2, y2) == TRUE ) moveSuccess(x1, y1, x2, y2);
        else return -1;
    }
    else return -1;
}


// Format: (x1, y1) is the current position while (x2, y2) is the requested destination; nb: x <--> columns/letters, y <--> rows/numbers
int movePiece(int x1, int y1, int x2, int y2) {
    // Check if dest. is invalid (due to the board's dimensions):
    if (y2 >= 8 || x2 >= 8 || y2 < 0 || x2 < 0) return -1;
    else if ( x1 == x2 && y1 == y2 ) return -1;
    
    // UPDATE feedback from calling all move functions
    if( board[x1][y1].id == 'P') {
        // Success:
        if( movePawn(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }
    else if( board[x1][y1].id == 'R') {
        // Success:
        if( moveRook(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }
    else if( board[x1][y1].id == 'B') {
        // Success:
        if( moveBishop(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }
    else if( board[x1][y1].id == 'Q') {
        // Success:
        if( moveQueen(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }
    else if( board[x1][y1].id == 'K') {
        // Success:
        if( moveKing(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }
    else if( board[x1][y1].id == 'N') {
        // Success:
        if( movePawn(x1, y1, x2, y2) == 0 ) return 0;
        // Failure:
        else return -1;
    }
    else return -1;
}


