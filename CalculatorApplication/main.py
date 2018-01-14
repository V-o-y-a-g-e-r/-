import tkinter as tk
from tkinter import ttk

class Calc():
    def __init__(self):
        self.value = ""
        global root
        root = tk.Tk()
        root.resizable(width = False, height = False)
        root.geometry("385x350")
        self.style = ttk.Style()
        self.style.configure("TEntry", font = "Helvetica 20", padding = 10)
        self.style.configure("TButton", font = "Helvetica 20", padding = 10)
        self.var = tk.StringVar();
        self.entry = ttk.Entry(root, textvariable = self.var)
        self.entry.grid(row = 0, columnspan = 4)
        self.button7 = ttk.Button(root, text = 7, width = 4, command = lambda:self.button_Pressed("7")).grid(row = 1, column = 0)
        self.button8 = ttk.Button(root, text = 8, width = 4, command = lambda:self.button_Pressed("8")).grid(row = 1, column = 1)
        self.button9 = ttk.Button(root, text = 9, width = 4, command = lambda:self.button_Pressed(("9"))).grid(row = 1, column = 2)
        self.buttonMult = ttk.Button(root, text = "*", width = 4, command = lambda:self.set_Math("*")).grid(row = 1, column = 3)
        self.button4 = ttk.Button(root, text=4, width=4, command=lambda: self.button_Pressed("4")).grid(row=2, column=0)
        self.button5 = ttk.Button(root, text=5, width=4, command=lambda: self.button_Pressed("5")).grid(row=2, column=1)
        self.button6 = ttk.Button(root, text=6, width=4, command=lambda: self.button_Pressed(("6"))).grid(row=2,column=2)
        self.buttonAdd = ttk.Button(root, text="+", width=4, command=lambda: self.set_Math("+")).grid(row=2, column=3)
        self.button1 = ttk.Button(root, text=1, width=4, command=lambda: self.button_Pressed("1")).grid(row=3, column=0)
        self.button2 = ttk.Button(root, text=2, width=4, command=lambda: self.button_Pressed("2")).grid(row=3, column=1)
        self.button3 = ttk.Button(root, text=3, width=4, command=lambda: self.button_Pressed(("3"))).grid(row=3, column=2)
        self.buttonSub = ttk.Button(root, text="-", width=4, command=lambda: self.set_Math("-")).grid(row=3, column=3)
        self.buttonEqual = ttk.Button(root, text ="=", width = 4, command = lambda:self.do_Math()).grid(row = 4, column = 0)
        self.buttonDiv = ttk.Button(root, text="/", width=4, command=lambda: self.set_Math("/")).grid(row=4, column=1)
        self.buttonAC = ttk.Button(root, text="AC", width=4, command=lambda: self.set_Math("AC")).grid(row=4, column=2)
    def button_Pressed(self, value):
        self.entry.delete(0, "end")
        self.var.set(value)
        self.value += str(value)
        self.value += " "
    def set_Math(self, sign):
        self.entry.delete(0, "end")
        if sign == "AC":
            self.value = ""
            return
        self.sign = sign

    def do_Math(self):
        if self.sign == "*":
            self.value.rstrip()
            var1, var2, space = self.value.split(" ")
            result = float(var1) * float(var2)
            self.var.set(str(result))
            self.value = ""
        elif self.sign == "+":
            self.value.rstrip()
            var1, var2, space = self.value.split(" ")
            result = float(var1) + float(var2)
            self.var.set(str(result))
            self.value = ""
        elif self.sign == "-":
            self.value.rstrip()
            var1, var2, space = self.value.split(" ")
            result = float(var1) - float(var2)
            self.var.set(str(result))
            self.value = ""
        if self.sign == "/":
            self.value.rstrip()
            var1, var2, space = self.value.split(" ")
            result = float(var1) / float(var2)
            self.var.set(str(result))
            self.value = ""
def main():

    app = Calc()
    root.mainloop()

main()