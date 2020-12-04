/*
    sudoku-solver, v1.0.0
    Released under GPLv3 license:
    www.gnu.org/licenses/gpl-3.0.html
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
*/

#include <unistd.h> // used for getcwd()
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat(), strcpy()
#include "sudoku.h"
#include "engine.h"
#include "main.h"

int MinimalSolve();
int DirectSolve(char *inputString);

int main (int argc, char *argv[])   // list of arguments starts from argv[1]
{ 
    // init mode variables:
    helpMode    = false;
    directInput = false;
    printTable  = false;
    minimalMode = false;

    // check input mode:
    if (argc != 1)
    {
        // arguments are present:
        if ( !strcmp(argv[1], "-h") )
        {
            helpMode = true;
        }
        else if ( !strcmp(argv[1], "-d") )
        {
            directInput = true;
        }
        else if ( !strcmp(argv[1], "-p") )
        {
            printTable = true;
        }
        else
        {
            helpMode = true;
        }
    }
    else
    {
        minimalMode = true;
    }
    
    // starts minimal mode, in which the board.txt file is read,
    // arrGrid is populated and output is written to solved.txt
    if (minimalMode)
    {
        return MinimalSolve();
    }
    // searches for an input string from the GUI, formatted by 
    // concatenating all rows of the matrix from first to last
    else if (directInput)
    {
        return DirectSolve(argv[2]);
    }
    
   
    return 0;
}


int DirectSolve(char *inputString)
{
    int row, col;
    char dataString[81];
    char arrGrid[9][9];
    
    // populate the working grid parsing the input:
    for (row=0; row<9; row++)
    {
        for (col=0; col<9; col++)
        {
            arrGrid[row][col] = inputString[ (row*9) + col ];
        }
    }

    // solve the grid:
    if(!SolveSudoku(arrGrid))
    {
        return 1;   // puzzle is not solvable
    }
    // assign output values to output buffer:
    for (row=0; row<9; row++)
    {
        for (col=0; col<9; col++)
        {
            dataString[ (row*9) + col ] = arrGrid[row][col];
        }
    }

    // print result on the stdout so that the GUI can read it:
    printf("%s", dataString);


    return 0;
}

int MinimalSolve()
{
    FILE *fpin, *fpout;
    
    char    inFilePath [256];
    char  *pinFilePath = NULL;
    char   outFilePath[256];
    char *poutFilePath = NULL;
    size_t  inFilePathLen = 256;    // I really hope nobody has a 
                                    // longer directory tree
    size_t outFilePathLen = 256; 

    //DEBUG!
    //long inFileSize;
    char arrGrid[9][9];

    // get current working directory
    pinFilePath  =  inFilePath;
    poutFilePath = outFilePath;
    pinFilePath = getcwd(pinFilePath, inFilePathLen);
    // copy the path over to the outfile:
    poutFilePath = strcpy(outFilePath, inFilePath);
    
     
    // add filename to path:
    pinFilePath = strcat(inFilePath, &spacer);
    pinFilePath = strcat(inFilePath, inBoard);
    poutFilePath = strcat(outFilePath, &spacer);
    poutFilePath = strcat(outFilePath, outBoard);
    inFilePathLen = strlen(pinFilePath);
    outFilePathLen = strlen(poutFilePath);

    // read the input board file read only
    fpin = fopen(inFilePath, "r");
    // create a new board file read-write:
    fpout = fopen(outFilePath, "w+");
    if (fpin == NULL)
    {
        printf("ERROR: cannot open input file in %s\n", inFilePath);
        return 2;
    }
    if (fpout == NULL)
    {
        printf("ERROR: cannot create output file in %s\n", outFilePath);
        return 2;
    }
    
/*
    DEBUG!
    // get input file size:
    fseek(fpin, (long) 0, SEEK_END);
    inFileSize = ftell(fpin);
    rewind(fpin); 
    printf("File size: %li bytes\n", inFileSize);   
*/

    // read the input file and populate the grid:
    PopulateMatrix(fpin, arrGrid);
    // solve the puzzle:
    if(!SolveSudoku(arrGrid))
    {
        printf("Dude, this puzzle can't be solved, wtf did you throw at me?\n");
        return 1;
    }

    // print out the solved puzzle: 
    rewind(fpin);
    rewind(fpout);
    PrintOutMatrix(fpin, fpout, arrGrid);

    // close the file streams:
    rewind(fpin);
    rewind(fpout);
    fclose(fpin);
    fclose(fpout);

    return 0;
}

//EOF
