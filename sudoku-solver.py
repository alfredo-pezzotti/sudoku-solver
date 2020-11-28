#!/usr/bin/python3

"""
    GUI frontend for sudoku solver.
    Released under GPLv3 (www.gnu.org/licenses/gpl-3.0.html)
    by Alfredo Pezzotti alfredo.pezzottiATyahoo.com
"""

import tkinter as tk
from tkinter import ttk as ttk


# definitions:
def Open():
    # define code here
    pass


#
root = tk.Tk()
#root.geometry("400x400")
frame = tk.Frame(root)
frame.pack()

# menu bar:
mainMenu = tk.Menu(frame)
mainMenu.add_command(label="Open", command=Open)
root.config(menu = mainMenu)

topFrame = tk.Frame(root)
#topFrame.config(bg="#FFFFFF")
topFrame.pack(side="top")

bottomFrame = tk.Frame(root)
bottomFrame.pack(side="bottom")

# create grid
for r in range (11):
    for c in range (11):
        if (c != 3) and (c != 7) and (r != 3) and (r != 7):
            tk.Entry(topFrame, width=2).grid(row=r, column=c)
        elif ((c == 3) or (c == 7)) and ((r != 3) and (r != 7)):
            tk.Label(topFrame, text="|", borderwidth=2).grid(row=r, column=c)
        else:
            ttk.Separator(topFrame, orient="horizontal").grid(row=r, column=c)

# create solve button:
solveBtn = tk.Button(bottomFrame, text="solve!")
solveBtn.pack()

# start of program:
root.mainloop()

#EOF
