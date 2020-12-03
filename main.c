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



int main (int argc, char *argv[])   // list of arguments starts from argv[1]
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
    
    // init mode variables:
    helpMode    = false;
    directInput = false;
    printTable  = false;

    // check input mode:
    if (argc != 1)
    {
        // arguments are present:
        // TODO NOPE! replace with strcmp()
        switch (argv[1])
        {
            case "-h":
                helpMode = true;
                break;
            case "-d":
                directInput = true;
                break;
            case "-p":
                printTable = true;
                break;
        }
    }

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
    
    
/*
    //DEBUG
    //!PrintGrid(arrGrid);
*/
   
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

/*
    //DEBUG!
    PrintGrid(arrGrid);
*/

    // close the file streams:
    rewind(fpin);
    rewind(fpout);
    fclose(fpin);
    fclose(fpout);


    return 0;
}



//EOF

