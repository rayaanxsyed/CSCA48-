/**
 * Exercise 11 - Sudoku
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 *
 * Starter code:  (Updated by) Charles Xu, 2024
 *             (Originally by) Mustafa Quraish, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

/**
 * Given a 9x9 Sudoku grid, this function prints out the grid in a format
 * that is easy to view, aiding in debugging or visualization.
 *
 * @param sudoku The 9x9 Sudoku grid to be printed.
 */
void print_sudoku(int sudoku[9][9]) {
    printf("The Sudoku contains:\n");
    printf("+-------+-------+-------+\n");
    for (int j = 0; j < 9; j++) {
        printf("| ");
        for (int i = 0; i < 9; i++) {
            printf("%d ", sudoku[j][i]);
            if (i % 3 == 2) printf("| ");
        }
        printf("\n");
        if (j % 3 == 2) printf("+-------+-------+-------+\n");
    }
}

#endif
// Check for valid rows. Returns 1 if it is valid and 0 if not.
int is_valid_row(int sudoku[9][9], int row) {
    int unique_values[10] = {0};

    for (int i = 0; i < 9; i++) {
        int value = sudoku[row][i];
        if (value != 0) {
            if (unique_values[value] == 1){
                return 0; // We have duplicate so it's invalid 
            }
            unique_values[value] = 1; // We continue searching 
        }
    }
    return 1; // It is valid
}

// Check for valid columsn. Return 1 if it is valid and 0 if not. 
int is_valid_column(int sudoku[9][9], int column) {
    int unique_values[10] = {0};

    for (int i = 0; i < 9; i++) {
        int value = sudoku[i][column];
        if (value != 0) {
            if (unique_values[value] == 1){
                return 0; // We have duplicate so it's invalid 
            }
            unique_values[value] = 1; // We continue searching 
        }
    }
    return 1; // It's valid
}

int is_valid_subgrid(int sudoku[9][9], int beginning_row, int beginning_column) {
    int unique_values[10] = {0};
    for (int row = beginning_row; row < beginning_row + 3; row++) {
        for (int col = beginning_column; col < beginning_column + 3; col++) {
            int value = sudoku[row][col]; // Traversing our subgrid to check for duplicates
            if (value != 0) { // Check for unique values
                if (unique_values[value]) {
                    return 0; // Duplicate found, invalid
                }
                unique_values[value] = 1; // Continue searching
            }
        }
    }
    return 1; // It is valid 
}
/**
 * This function checks if the current Sudoku grid (not necessarily complete)
 * is valid. A Sudoku grid is considered valid if, ignoring the 0s, each row,
 * column, and 3x3 subgrid does not repeat any digits from 1 to 9.
 *
 * @note An incomplete Sudoku grid may be valid if the criteria above is met.
 *
 * @param sudoku The 9x9 Sudoku grid to be checked.
 * @return 1 if the Sudoku is valid, 0 if it's not.
 */
int is_valid_sudoku(int sudoku[9][9]) {
    // TODO: Complete this function.
    for (int i = 0; i < 9; i++) {
        if (is_valid_row(sudoku, i) != 1 || is_valid_column(sudoku, i) != 1) {
            return 0; // If any row or column is invalid, the whole sudoku puzzle is invalid
        }
    }
    for (int beginning_row = 0; beginning_row < 9; beginning_row += 3) {
        for (int beginning_column = 0; beginning_column < 9; beginning_column += 3) {
            if (is_valid_subgrid(sudoku, beginning_row, beginning_column) != 1) {
                return 0; // Duplicates found, invalid
            }
        }
    }
    return 1; // It is valid
}
// Check if the sudoku is already solved
int is_solved_sudoku(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) { // Iterate through the puzzle
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) { // If there's a 0 that exists then it's not solved
                return 0;
            }
        }
    }
    return 1; // Solved, don't need to do any solving
}

/**
 * Given a (possibly partially) completed Sudoku grid, this function attempts
 * to solve the Sudoku. The `sudoku` array is changed to contain the solution
 * if one exists. None of the digits in the input grid should be changed.
 *
 * @note: Empty spots in the grid are denoted with 0s.
 *
 * @param sudoku The 9x9 Sudoku grid to be solved.
 * @return 1 if the Sudoku was solved successfully and the `sudoku` array is
 * updated, 0 if it's not possible to solve the Sudoku, and the input `sudoku`
 * array remains unchanged in this case.
 */
int solve_sudoku(int sudoku[9][9]) {
    // TODO: Complete this function.
    if (is_valid_sudoku(sudoku) == 0) {
        return 0; // We can't solve an unsolvable sudoku puzzle
    }

    if (is_solved_sudoku(sudoku) == 1) {
        return 1; // Puzzle is already solved
    }
    int row, col;
    
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sudoku[row][col] == 0) {
                // Let's try numbers from 1 to 9 and see what happens
                for (int num = 1; num <= 9; num++) {
                    sudoku[row][col] = num;
                    // Check if our value actually works
                    if (is_valid_sudoku(sudoku) == 1) {
                        // It works so let's move to the next and see if they work too
                        if (solve_sudoku(sudoku) == 1) {
                            return 1; // Boom, solved
                        }
                    }
                    // If our number doesn't lead to it being solved, try again with new combinations 
                    sudoku[row][col] = 0;
                }
                // If nothing works, it's unsolvable
                return 0;
            }
        }
    }
    
    return 1; // Solved 
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    int sudoku_grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    print_sudoku(sudoku_grid);

    int solved = solve_sudoku(sudoku_grid);

    printf("\nsolve_sudoku() return value: %d\n\n", solved);

    /* Look at the handout to see the solution for this! */
    print_sudoku(sudoku_grid);

    return 0;
}

#endif