    sudoku-solver, v1.0.0
    Released under GPLv3 license:
    www.gnu.org/licenses/gpl-3.0.html
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com


This software takes as input a text file containing
the puzzle, and spits out a solution both on terminal
and in a solved.txt file, in the same directory in
which the binary resides.

INSTALLATION:
    There's no need to install the software, just run:
        $ make

    To build the sudoku-solver executable both on windows
    and unix. If for some reasons you want to debug it,
    run debug.sh/debug.bat, depending on your platform.
    A more capable makefile will be provided in future releases.

USAGE:
    Populate the provided board.txt file with your puzzle.
    Then, run sudoku-solver in the same directory as the board
    file (unix: you can navigate to the board and run the
    binary if you added it to path).
    The program will generate a solved.txt file with the solved
    puzzle, as well as print out on the console the solution.
