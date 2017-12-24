#include "chess.h"

int main(){
    FILE *cGen = fopen("clean_board", "wt");
    if (cGen == NULL) exit(1);

    // Initialize the 64 empty Cell structs to be used later:
    for (char col = 'A'; col <= 'H'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            fprintf(cGen, "Cell %c%c;\n", col, row);
        }
    }

    fprintf(cGen, "\n");

    // Specify the colors of the 'active' tiles; fully initialize all pawns
    for (char col = 'A'; col <= 'H'; col++) {
        for (char row = '1'; row <= '8'; row++) {
            if (row == '1') {
                fprintf(cGen, "%c%c.color = 'W';\n", col, row);
            }
            else if (row == '2') {
                fprintf(cGen, "%c%c.id = 'P';\n", col, row);
                fprintf(cGen, "%c%c.color = 'W';\n", col, row);
            }
            else if (row == '7') {
                fprintf(cGen, "%c%c.id = 'P';\n", col, row);
                fprintf(cGen, "%c%c.color = 'B';\n", col, row);
            }
            else if (row == '8') {
                fprintf(cGen, "%c%c.color = 'B';\n", col, row);
            }
            else {
                fprintf(cGen, "%c%c.id = 'O';\n", col, row);
                fprintf(cGen, "%c%c.color = 'O';\n", col, row);
            }
        }
    }

    fprintf(cGen, "\n");

    // Assigning the white heavy pieces their id's:
    fprintf(cGen, "A1.id = 'R';\n");
    fprintf(cGen, "B1.id = 'N';\n");
    fprintf(cGen, "C1.id = 'B';\n");
    fprintf(cGen, "D1.id = 'Q';\n");
    fprintf(cGen, "E1.id = 'K';\n");
    fprintf(cGen, "F1.id = 'B';\n");
    fprintf(cGen, "G1.id = 'N';\n");
    fprintf(cGen, "H1.id = 'R';\n");

    // Assigning the black heavy pieces their id's:
    fprintf(cGen, "A8.id = 'R';\n");
    fprintf(cGen, "B8.id = 'N';\n");
    fprintf(cGen, "C8.id = 'B';\n");
    fprintf(cGen, "D8.id = 'Q';\n");
    fprintf(cGen, "E8.id = 'K';\n");
    fprintf(cGen, "F8.id = 'B';\n");
    fprintf(cGen, "G8.id = 'N';\n");
    fprintf(cGen, "H8.id = 'R';\n");

    fprintf(cGen, "\n");

    // Create the row arrays:
    fprintf(cGen, "Cell row1[8] = {A1, B1, C1, D1, E1, F1, G1, H1};\n");
    fprintf(cGen, "Cell row2[8] = {A2, B2, C2, D2, E2, F2, G2, H2};\n");
    fprintf(cGen, "Cell row3[8] = {A3, B3, C3, D3, E3, F3, G3, H3};\n");
    fprintf(cGen, "Cell row4[8] = {A4, B4, C4, D4, E4, F4, G4, H4};\n");
    fprintf(cGen, "Cell row5[8] = {A5, B5, C5, D5, E5, F5, G5, H5};\n");
    fprintf(cGen, "Cell row6[8] = {A6, B6, C6, D6, E6, F6, G6, H6};\n");
    fprintf(cGen, "Cell row7[8] = {A7, B7, C7, D7, E7, F7, G7, H7};\n");
    fprintf(cGen, "Cell row8[8] = {A8, B8, C8, D8, E8, F8, G8, H8};\n");

    fprintf(cGen, "\n");

    // Create the column arrays:
    fprintf(cGen, "Cell col1[8] = {A1, A2, A3, A4, A5, A6, A7, A8};\n");
    fprintf(cGen, "Cell col2[8] = {B1, B2, B3, B4, B5, B6, B7, B8};\n");
    fprintf(cGen, "Cell col3[8] = {C1, C2, C3, C4, C5, C6, C7, C8};\n");
    fprintf(cGen, "Cell col4[8] = {D1, D2, D3, D4, D5, D6, D7, D8};\n");
    fprintf(cGen, "Cell col5[8] = {E1, E2, E3, E4, E5, E6, E7, E8};\n");
    fprintf(cGen, "Cell col6[8] = {F1, F2, F3, F4, F5, F6, F7, F8};\n");
    fprintf(cGen, "Cell col7[8] = {G1, G2, G3, G4, G5, G6, G7, G8};\n");
    fprintf(cGen, "Cell col8[8] = {H1, H2, H3, H4, H5, H6, H7, H8};\n");


    // Flush the buffer and return 0 since we encounterd no errors
    fclose(cGen);
    return 0;
}