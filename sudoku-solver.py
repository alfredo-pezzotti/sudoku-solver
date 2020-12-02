#!/usr/bin/python3

"""
    GUI frontend for sudoku solver.
    Released under GPLv3 (www.gnu.org/licenses/gpl-3.0.html)
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
"""

import tkinter as tk
from tkinter import ttk as ttk
from tkinter.messagebox import showerror
import collections
import subprocess as subp
import sys


# create a global dictionary to reach the elements of the grid
# in the following way: sudokuElements[row][column]
sudokuElements = collections.defaultdict(list)
# dataString contains the string with the I/O puzzle data
# to be passed to the C program, returned and then printed
# in the widgets' Entries:
dataString = ""

# definitions:
def Open():
    # define code here
    pass

# fx to call the executable's subprocess:
def SpawnSolver():
    global dataString
    if (sys.platform == "linux") or (sys.platform == "linux2"):
        procOut = subp.run(["./sudoku-solver", "-d", dataString], capture_output=True )
    #elif platform == "darwin":
    #    # OS X
    elif sys.platform == "win32":
        procOut = subp.run(["sudoku-solver.exe", "-d", dataString], capture_output=True) 
    # assign output to dataString
    dataString = procOut.stdout

    return procOut.returncode

# sets the puzzle grid with the correct results
def PrintResult():
    global dataString
    global sudokuElements
    return

# called whenever the "Solve" button is clicked:
def SolvePuzzle():
    global dataString
    global sudokuElements
    row = 0
    for r in range (9):
        col = 0
        for c in range (9):
            temp = (sudokuElements[row][col]).get()
            if (len(temp) > 1) or ((temp != '' ) and
                                   (temp != '1') and
                                   (temp != '2') and
                                   (temp != '3') and
                                   (temp != '4') and
                                   (temp != '5') and
                                   (temp != '6') and
                                   (temp != '7') and
                                   (temp != '8') and
                                   (temp != '9')):
                # raise a dialog informing of $temp problem at
                # (r,c) position 
                errorMessage = showerror(title="Invalid puzzle", 
                                       message="Looks like you entered something funny" + 
                                         " in grid element (" + str(row + 1) + 
                                         ", " + str(col + 1) + "):\n" + temp)
                return
            elif (temp == ''):
                dataString = dataString + '.'   # append vacancy
            else:
                dataString = dataString + temp
            col += 1
        # end of row:
        row += 1
    
    # spawn the sudoku-solver process passing dataString as argument
    # with option -d (--direct-input)
    returnCode = SpawnSolver()
    # the puzzle was successfully solved
    if returnCode == 0:
        PrintResult()
    # the puzzle has not been solved:
    elif returnCode == 1:
        errorMessage = showerror( title="Non-solvable puzzle",
                                  message="The algorithm did not manage to find a" +
                                  " solution for the submitted puzzle. It's pretty" +
                                  " smart so you better check input for errors.")
    
        return
    
    # end of fx
    return
    

    
""" MAIN """
# create a root window
root = tk.Tk()
root.wm_title("sudoku-solver")
root.call('wm', 'iconphoto', root._w, tk.PhotoImage(file='res/sudoku.png'))
#root.geometry("400x400")
frame = tk.Frame(root)
#frame.config(bg="#FFFFFF")
frame.pack()

# menu bar:
mainMenu = tk.Menu(root)
root.config(menu = mainMenu)
fileMenu = tk.Menu(mainMenu, tearoff=0)
mainMenu.add_cascade(label="File", menu=fileMenu)
# add commands to file menu:
fileMenu.add_command(label="Open", command=Open)
#file_menu.add_separator()
fileMenu.add_command(label="Quit", command=root.destroy)

topFrame = tk.Frame(root)
#topFrame.config(bg="#FFFFFF")
topFrame.pack(side="top")

bottomFrame = tk.Frame(root)
bottomFrame.pack(side="bottom")

row = 0

# create grid, assigning each entry to a sudokuElement's item
for r in range (11):
    column = 0
    for c in range (11):
        if (c != 3) and (c != 7) and (r != 3) and (r != 7):
            # TODO: create the widget first, and only after that call .grid(), coz
            # Widget.grid() returns a None type.
            temp = tk.Entry(topFrame, width=2)
            sudokuElements[row].append(temp)
            (sudokuElements[row][column]).grid(row=r, column=c)
            column += 1
        elif ((c == 3) or (c == 7)) and ((r != 3) and (r != 7)):
            tk.Label(topFrame, text="|", borderwidth=2).grid(row=r, column=c)
        else:
            ttk.Separator(topFrame, orient="horizontal").grid(row=r, column=c)
    # skip the separator row
    if (r != 3) and (r != 7):
        row += 1

# create solve button:
solveBtn = tk.Button(bottomFrame, text="solve!", command=SolvePuzzle)
solveBtn.pack()

# start of program:
root.mainloop()

#EOF
