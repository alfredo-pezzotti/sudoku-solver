/*
    sudoku-solver, v1.0.0
    Released under GPLv3 license:
    www.gnu.org/licenses/gpl-3.0.html
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
*/
#ifndef SUDOKU_H
#define SUDOKU_H

#define byte unsigned char

// if the OS is windows, paths are separated by backslashes
#ifndef __linux__
static const char spacer = '\\';
#endif

#ifdef __linux__
static const char spacer = '/';
#endif

#ifndef NUL
#define NUL '\0'
#endif

// TODO: I wanna put those in a text file for configuration purposes
// names of the boards 
static const char  inBoard[] = "board.txt";
static const char outBoard[] = "solved.txt";

// these are gonna be used when printing a template
// for the user
static const char defaultRow[]   = ".  .  .  |  .  .  .  |  .  .  .";
static const char separatorRow[] = "-------------------------------";


/*
    This function takes care of building a computation
    grid out of the input text file.
*/
int PopulateMatrix (FILE* fpin, char arrGrid[9][9]);


/*
    This function takes the computation grid and uses
    the input file template to build an output grid.
*/
int PrintOutMatrix (FILE *fpin, FILE *fpout, char arrGrid[9][9]);



#endif
