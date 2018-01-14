'''
Hi,

This is calculator made just for fun in tkinter to pratice this library.
It is able to calculate the result of previous calculation.
Just remeber that, user should press '=' sign after inputing the expression.
Work is in progress, so dont be surprised if there is something missing.

Cheers
~ V-o-y-a-g-e-r :)
'''

import tkinter as tk
from tkinter import ttk
from tkinter import font

class Calc():
    def __init__(self):
        global root
        root = tk.Tk()
        root.resizable(width = False, height = False)
        root.title("Calculator")
        root.geometry("352x296")
        self.fontFigure = font.Font(family="Helvetica", size=20, weight="bold", slant = "italic")
        self.style = ttk.Style()
        self.style.configure("TEntry", font = self.fontFigure, padding = 10)
        self.style.configure("TButton", font = self.fontFigure, padding = 10)
        self.var = tk.StringVar();
        self.value = ""
        self.show = ""
        self.entry = ttk.Entry(root, font = self.fontFigure, textvariable = self.var)
        self.entry.grid(row = 0, columnspan = 4)
        self.button7 = ttk.Button(root, text = 7, width = 4, command = lambda: self.button_Pressed("7")).grid(row = 1, column = 0)
        self.button8 = ttk.Button(root, text = 8, width = 4, command = lambda: self.button_Pressed("8")).grid(row = 1, column = 1)
        self.button9 = ttk.Button(root, text = 9, width = 4, command = lambda: self.button_Pressed(("9"))).grid(row = 1, column = 2)
        self.buttonMult = ttk.Button(root, text = "*", width = 4, command = lambda: self.set_Math("*")).grid(row = 1, column = 3)
        self.button4 = ttk.Button(root, text=4, width=4, command=lambda: self.button_Pressed("4")).grid(row=2, column=0)
        self.button5 = ttk.Button(root, text=5, width=4, command=lambda: self.button_Pressed("5")).grid(row=2, column=1)
        self.button6 = ttk.Button(root, text=6, width=4, command=lambda: self.button_Pressed(("6"))).grid(row=2,column=2)
        self.buttonAdd = ttk.Button(root, text="+", width=4, command=lambda: self.set_Math("+")).grid(row=2, column=3)
        self.button1 = ttk.Button(root, text=1, width=4, command=lambda: self.button_Pressed("1")).grid(row=3, column=0)
        self.button2 = ttk.Button(root, text=2, width=4, command=lambda: self.button_Pressed("2")).grid(row=3, column=1)
        self.button3 = ttk.Button(root, text=3, width=4, command=lambda: self.button_Pressed(("3"))).grid(row=3, column=2)
        self.buttonSub = ttk.Button(root, text="-", width=4, command=lambda: self.set_Math("-")).grid(row=3, column=3)
        self.buttonEqual = ttk.Button(root, text ="=", width = 4, command = lambda: self.do_Math()).grid(row = 4, column = 0)
        self.buttonDiv = ttk.Button(root, text="/", width=4, command=lambda: self.set_Math("/")).grid(row=4, column=1)
        self.buttonAC = ttk.Button(root, text="AC", width=4, command=lambda: self.set_Math("AC")).grid(row=4, column=2)
        self.button0 = ttk.Button(root, text = "0", width = 4, command = lambda: self.button_Pressed("0")).grid(row = 4, column = 3)

    def button_Pressed(self, value_):
        self.value += value_
        self.show += value_
        self.var.set(self.show)

    def set_Math(self, sign):
        self.entry.delete(0, "end")
        self.sign = sign
        self.value += " "
        self.show = ""
        if sign == "AC":
            self.value = ""
            self.var.set("")
            return

    def do_Math(self):
        if self.sign == "*":
            self.value.rstrip()
            var1, var2= self.value.split()
            result = float(var1) * float(var2)
            self.var.set(str(result))
            self.value = str(result)
        elif self.sign == "+":
            self.value.rstrip()
            var1, var2= self.value.split()
            result = float(var1) + float(var2)
            self.var.set(str(result))
            self.value = str(result)
        elif self.sign == "-":
            self.value.rstrip()
            var1, var2= self.value.split()
            result = float(var1) - float(var2)
            self.var.set(str(result))
            self.value = str(result)
        if self.sign == "/":
            self.value.rstrip()
            var1, var2= self.value.split()
            result = float(var1) / float(var2)
            self.var.set(str(result))
            self.value = str(result)

def main():

    app = Calc()
    root.mainloop()

main()