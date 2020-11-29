#!/usr/bin/python3

"""
    GUI frontend for sudoku solver.
    Released under GPLv3 (www.gnu.org/licenses/gpl-3.0.html)
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
"""

import tkinter as tk
from tkinter import ttk as ttk
import collections


# definitions:
def Open():
    # define code here
    pass


#
root = tk.Tk()
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

# create a dictionary to reach the elements of the grid
# in the following way: sudokuElements[row][column]
sudokuElements = collections.defaultdict(list)
row = 0

# create grid
for r in range (11):
    column = 0
    for c in range (11):
        if (c != 3) and (c != 7) and (r != 3) and (r != 7):
            sudokuElements[row].append( tk.Entry(topFrame, width=2).grid(row=r, column=c) )
            column += 1
        elif ((c == 3) or (c == 7)) and ((r != 3) and (r != 7)):
            tk.Label(topFrame, text="|", borderwidth=2).grid(row=r, column=c)
        else:
            ttk.Separator(topFrame, orient="horizontal").grid(row=r, column=c)
    if (r != 3) and (r != 7):
        row += 1

# create solve button:
solveBtn = tk.Button(bottomFrame, text="solve!")
solveBtn.pack()

# start of program:
root.mainloop()

#EOF
