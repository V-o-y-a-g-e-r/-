from tkinter import *
import tkinter.filedialog
from tkinter import font as fn

class Text_Editor:

    def __init__(self):

        root.geometry("664x400")
        root.title("Text Editor")
        #root.pack_propagate(0)
        root.resizable(width = False, height = False)
        self.var = StringVar("")
        self.custom_font = fn.Font(family = "Helvetica", size = 15)
        self.menu = Menu(root)
        self.menu.add_command(label = "Open", font = self.custom_font,
                              command = self.open_file)
        self.menu.add_separator()
        self.menu.add_command(label = "Save",
                              font = self.custom_font, command = self.save_file)
        self.menu.add_command(label = "Exit", command = self.exit, font = self.custom_font)
        self.scroll = Scrollbar(root)
        self.scroll.pack(side=RIGHT, fill=BOTH)
        self.text_area = Text(root, yscrollcommand = self.scroll.set, font = self.custom_font)
        self.text_area.pack(side = LEFT, fill = Y)
        self.scroll.config(command = self.text_area.yview)
        root.config(menu = self.menu)

    def exit(self):
        root.quit()
    def open_file(self):
        text_file = tkinter.filedialog.askopenfilename(parent = root,
            initialdir = "C:/Users/Łukasz/Desktop")#here, enter the file path in your device
        if text_file:
            self.file = open(text_file)
            self.var.set(self.file.read())
            self.text_area.insert(1.0, self.var.get())


    def save_file(self):
        text_file = tkinter.filedialog.asksaveasfile(mode = "w",
            initialdir = "C:/Users/Łukasz/Desktop")#here, enter the file path in your device
        if text_file:
            self.var.set(self.text_area.get(1.0, END + "-1c"))
            text_file.write(self.var.get())
            self.file.close()



def main():
    global root
    root= Tk()
    app = Text_Editor()
    root.mainloop()
main()


