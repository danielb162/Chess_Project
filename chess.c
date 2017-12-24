#include "chess.h"


// TO DO: Change this so it prints out the colors of the board appropriately with DGREY for black pieces and WHITE for white pieces
/*int printBoard(){
    // Top padding:
    printf("----------------\n");
    for(char col = 'A'; col <= 'H'; col++){ // Col counter, i.e. A - H
        for(char row = '2'; row <= '7'; row++){ // Row counter, i.e. 1 - 8
            char temp[2] = {col, row};
            if (col == 'A') printf("|%c|", col, row);
            else if (col == 'H') printf("%c|\n", col, row);
            else printf("%c|", col, row);
        }
    }
    // Bottom padding:
    printf("----------------\n");
    return 0;
}
*/

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

int main(){
    // Uses genCells.c to create a clean board state
    #include "clean_board"
 
    /* Sanity check for clean_board:
    printf("A8's id is: \033[1;37m%c\033[0m\nD7's id is: \033[1;30m%c\033[0m\n", A8.id, D7.id);
    printf("A1's id is %c, it's color is %c\n", row1[0].id, row1[0].color);*/

    //printBoard();



    // No errors encountered
    return 0;
}