/*
    sudoku-solver, v1.0.0
    Released under GPLv3 license:
    www.gnu.org/licenses/gpl-3.0.html
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
*/
#include <stdio.h>
#include "engine.h"
  
 
/* 
    Takes a partially filled-in grid 
    and attempts to assign values to
    all unassigned locations in such 
    a way to meet the requirements
    for Sudoku solution (non-duplication
    across rows, columns, and boxes) 
*/
bool SolveSudoku(char grid[N][N])
{
    char row, col;
 
    // Check If there is no unassigned
    // location, we are done
    if (!FindUnassignedLocation(grid, &row, &col))
    {
        return true; // success!
    }
 
    //Consider digits 1 to 9
    for (char num = 49; num <= 57; num++) 
    {
         
        // Check if looks promising
        if (IsSafe(grid, row, col, num)) 
        {
             
            // Make tentative assignment
            grid[row][col] = num;
 
            // Return, if success, yay!
            if (SolveSudoku(grid))
            {
                return true;
            }
 
            // Failure, unmake & try again
            grid[row][col] = UNASSIGNED;
        }
    }
   
    // This triggers backtracking
    return false;
}


/* 
    Searches the grid to find an entry 
    that is still unassigned. If
    found, the reference parameters row, 
    col will be set the location
    that is unassigned, and true is 
    returned. If no unassigned entries
    remain, false is returned. 
*/
bool FindUnassignedLocation(
    char grid[N][N], char *row, char *col)
{
    for ( (*row) = 0; (*row) < N; (*row)++)
    {
        for ( (*col) = 0; (*col) < N; (*col)++)
        {
            if (grid[*row][*col] == UNASSIGNED)
            {
                return true;
            }
        }
    }

    return false;
}


/* 
    Returns a boolean which indicates 
    whether an assigned entry
    in the specified row matches the 
    given number. 
*/
bool UsedInRow(
    char grid[N][N], char row, char num)
{
    for (char col = 0; col < N; col++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }

    return false;
}


/* 
    Returns a boolean which indicates 
    whether an assigned entry
    in the specified column matches 
    the given number. 
*/
bool UsedInCol(
    char grid[N][N], char col, char num)
{
    for (char row = 0; row < N; row++)
    {
        if (grid[row][col] == num)
        {
            return true;
        }
    }

    return false;
}


/* 
    Returns a boolean which indicates 
    whether an assigned entry
    within the specified 3x3 box 
    matches the given number. 
*/
bool UsedInBox(
    char grid[N][N], char boxStartRow,
    char boxStartCol, char num)
{
    for (char row = 0; row < 3; row++)
    {
        for (char col = 0; col < 3; col++)
        {
            if (grid[row + boxStartRow][col + boxStartCol] == num)
            {
                return true;
            }
        }
    }

    return false;
}


/* 
    Returns a boolean which indicates 
    whether it will be legal to assign
    num to the given row, col location. 
*/
bool IsSafe(
    char grid[N][N], char row,
    char col, char num)
{
     
    /* Check if 'num' is not already placed 
       in current row, current column and 
       current 3x3 box */
    return !UsedInRow(grid, row, num)
           && !UsedInCol(grid, col, num)
           && !UsedInBox(grid, row - row % 3,
                         col - col % 3, num)
           && grid[row][col] == UNASSIGNED;
}


/* A utility function to print grid  */
void PrintGrid(char grid[N][N])
{
    for (char row = 0; row < N; row++) 
    {
        for (char col = 0; col < N; col++)
        {
            printf("%c ", grid[row][col]);
        }
        printf("\n");
    }
}
 
//EOF
