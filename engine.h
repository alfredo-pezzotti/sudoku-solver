/*
    sudoku-solver, v1.0.0
    Released under GPLv3 license:
    www.gnu.org/licenses/gpl-3.0.html
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
*/
#ifndef ENGINE_H
#define ENGINE_H
#include <stdbool.h>

// UNASSIGNED is used for empty
// cells in sudoku grid
#define UNASSIGNED '.'

// N is used for the size of
// Sudoku grid. The size will be NxN
#define N 9
 
// This function finds an entry
// in grid that is still unassigned
bool FindUnassignedLocation(char grid[N][N], 
                            char* row, char* col);
 
// Checks whether it will be legal
// to assign num to the given row, col
bool IsSafe(char grid[N][N], char row,
            char col, char num);


bool SolveSudoku(char grid[N][N]);

bool UsedInRow( char grid[N][N], char row, char num);

bool UsedInCol(
    char grid[N][N], char col, char num);


bool UsedInBox(
    char grid[N][N], char boxStartRow,
    char boxStartCol, char num);

bool IsSafe(
    char grid[N][N], char row,
    char col, char num);

void PrintGrid(char grid[N][N]);


#endif
