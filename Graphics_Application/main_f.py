import tkinter as tk

class Application(tk.Tk):

    def __init__(self):#class constructor

        tk.Tk.__init__(self)#parent class constructor
        ###
        self.title("Window Application")
        self.geometry("500x404")
        #self.resizable(0,0)
        ###
        self.w = tk.Canvas(self, width = self.winfo_reqwidth(), height = self.winfo_reqheight()*2, bg = "white")
        self.w.pack(fill = tk.BOTH)
        self.w.bind("<B1-Motion>", self.paint)


    #paint method
    def paint(self, event):
        x1, y1 = event.x -1, event.y -1
        x2, y2 = event.x +1, event.y +1
        self.w.create_oval(x1, y1, x2, y2)


my_app = Application()
my_app.mainloop()