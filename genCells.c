#include <stdlib.h>
#include <stdio.h>

int main(){
    FILE *cGen = fopen("clean_board", "wt");
    if (cGen == NULL) exit (1);
    for(char col = 'A'; col <= 'H'; col++){
        for(char row = '2'; row <= '7'; row++){
            if (row == '2') fprintf(cGen, "char %c2[2] = {'W', 'P'};\n", col);
            else if (row == '7') fprintf(cGen, "char %c7[2] = {'B', 'P'};\n", col);
            else fprintf(cGen, "char %c%c[2] = {'O', 'O'};\n", col, row);
        }
    }

    // White heavy pieces:
    fprintf(cGen, "char A1[2] = {'W', 'R'};\n");
    fprintf(cGen, "char B1[2] = {'W', 'N'};\n");
    fprintf(cGen, "char C1[2] = {'W', 'B'};\n");
    fprintf(cGen, "char D1[2] = {'W', 'Q'};\n");
    fprintf(cGen, "char E1[2] = {'W', 'K'};\n");
    fprintf(cGen, "char F1[2] = {'W', 'B'};\n");
    fprintf(cGen, "char G1[2] = {'W', 'N'};\n");
    fprintf(cGen, "char H1[2] = {'W', 'R'};\n");

    // Black heavy pieces:
    fprintf(cGen, "char A8[2] = {'B', 'R'};\n");
    fprintf(cGen, "char B8[2] = {'B', 'N'};\n");
    fprintf(cGen, "char C8[2] = {'B', 'B'};\n");
    fprintf(cGen, "char D8[2] = {'B', 'Q'};\n");
    fprintf(cGen, "char E8[2] = {'B', 'K'};\n");
    fprintf(cGen, "char F8[2] = {'B', 'B'};\n");
    fprintf(cGen, "char G8[2] = {'B', 'N'};\n");
    fprintf(cGen, "char H8[2] = {'B', 'R'};\n");

    fclose(cGen);
    return 0;
}