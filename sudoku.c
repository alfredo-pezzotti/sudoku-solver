/*
    sudoku-solver, v1.0.0
    Released under GPLv3 license:
    www.gnu.org/licenses/gpl-3.0.html
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"
//DEBUG!
//#include <errno.h>


int PopulateMatrix (FILE *fpin, char arrGrid[9][9])
{
    char *line = NULL;
    ssize_t reading = 0;
    size_t lineLen = 8; // short value, to make getline call realloc()
    char rowCursor = 0;
    char rowCounter = 0;
    char columnCounter = 0;

    char i, j;//, possVals=0;
    //DEBUG!
    //int errsv = 0;
    

    // allocate lineLen bytes for the text file's line
    line = malloc(lineLen);

    printf("Input puzzle:\n");   
    
    // ssize_t takes all values between [-1, SSIZE_MAX].
    // getline returns -1 on failure to read a line (including end-of-
    // file condition). This while continues till there are no more lines.
    while ( (reading = getline(&line, &lineLen, fpin)) != -1 )
    {
        // set cursor to first character of line
        rowCursor = 0;
        // reset the index to address the minors' elements
        columnCounter = 0;

        // current line is a separatorRow
        if (line[rowCursor] == '-')
        {
            printf("%s", line);
            // jump to next line
            continue;
        }

        // move the cursor over each element of the selected line:
        while (line[rowCursor] != NUL)
        { 
            // if the cursor is on a number in the set 
            // {1, 2, 3, 4, 5, 6, 7, 8, 9} or the char '.',
            // we have a matrix element:
            if ( ( (line[rowCursor] > 48) && (line[rowCursor] < 58) ) ||
                 (line[rowCursor] == '.') )
            {
                // assign the input element's value to the correct 
                // grid element:
                i = rowCounter;
                j = columnCounter;
                arrGrid[i][j] = line[rowCursor];

                columnCounter++;
            }
            
            rowCursor++;
        }

        // print the input line to the console:
        printf("%s", line);
        rowCounter++; 

    }
    
    printf("\n\n");
    // remember: no mem leaks!
    free(line);

    return 0;
}


// TODO embed this function in "populateMatrix" via an input option
int PrintOutMatrix (FILE *fpin, FILE *fpout, char arrGrid[9][9])
{
    char *lineIn = NULL;
    char *lineOut = NULL;

    ssize_t reading = 0;
    size_t lineInLen = 8;   // short value, to make getline call realloc()
    size_t lineOutLen = 8;
    char rowCursor = 0;
    char rowCounter = 0;
    char columnCounter = 0;

    char i, j;

    // DEBUG
    //int errsv = 0;


    // allocate lineLen bytes for the text file's line
    lineIn  = malloc(lineInLen);

    printf("Solved puzzle:\n");
    
    // ssize_t takes all values between [-1, SSIZE_MAX].
    // getline returns -1 on failure to read a line (including end-of-
    // file condition). This while continues till there are no more lines.
    // USE fputs()
    while ( (reading = getline(&lineIn, &lineInLen, fpin)) != -1 )
    {
        if ( (rowCursor == 0) && (rowCounter == 0) )
        {
            lineOutLen = lineInLen;
            lineOut = malloc(lineOutLen);    // allocate same number of 
                                            // bytes for output
        }
        // set cursor to first character of line
        rowCursor = 0;
        // reset the index to address the minors' elements
        columnCounter = 0;
       // current line is a separatorRow
        if (lineIn[rowCursor] == '-')
        {
            rowCounter--;   // don't count current line as 
                            // a row for computation grid
        }

        // move the cursor over each element of the selected line:
        while (lineIn[rowCursor] != NUL)
        { 
            // if the cursor is on a valid sudoku grid element, replace it with
            // the solution found by the algorithm:
            if ( ( (lineIn[rowCursor] > 48) && (lineIn[rowCursor] < 58) ) ||
                 (lineIn[rowCursor] == '.') )
             {
                // assign the input element's value to the correct 
                // grid element:
                i = rowCounter;
                j = columnCounter;
                lineOut[rowCursor] = arrGrid[i][j];

                columnCounter++;

                //DEBUG!
                //errsv = errno;
            }
            else if (lineIn[rowCursor] == '-')
            {
                lineOut[rowCursor] = '-';
            }
            else if (lineIn[rowCursor] == '|')
            {
                lineOut[rowCursor] = '|';
            }
            else if (lineIn[rowCursor] == ' ')
            {
                lineOut[rowCursor] = ' ';
            }
            else if (lineIn[rowCursor] == '\n')
            {
                lineOut[rowCursor] = '\n';
            }

            rowCursor++;
        }
        
        lineOut[lineOutLen-1] = NUL;   // add NUL char to terminate string 
        // store the line to the output stream:
        fputs(lineOut, fpout);
        // print the solved line to the console:
        printf("%s", lineOut);

/*
        //DEBUG!
        errsv = errno;
        printf("errsv: %i\n", errsv);
        
        printf("lineIn:  %s", lineIn);
        printf("lineOut: %s", lineOut);
        printf("\n");
*/

        rowCounter++;
    }
 
    
    printf("\n\n");

    // no mem leaks!
    free(lineIn);
    free(lineOut);


    return 0;
}



//EOF

