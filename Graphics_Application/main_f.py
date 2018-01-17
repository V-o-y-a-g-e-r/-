import tkinter as tk

class Application(tk.Tk):

    def __init__(self):#class constructor

        tk.Tk.__init__(self)#parent class constructor
        #window parameters
        self.title("Window Application")
        self.geometry("500x404")
        self.resizable(0,0)
        #canvas
        self.paint_here = tk.Canvas(self, width = self.winfo_reqwidth(), height = self.winfo_reqheight()*2, bg = "white")
        self.paint_here.pack(fill = tk.BOTH)
        #locations for drawing stuff
        self.x1, self.y1 = None, None
        self.paint_obj = "Line"
        #binding buttons for drawing
        self.paint_here.bind("<B1-Motion>", self.motion)
        self.paint_here.bind("<ButtonPress-1>", self.button_down)
        self.paint_here.bind("<ButtonRelease-1>", self.button_up)

    def button_down(self, event):
        #take coords when button is down
        self.x1, self.y1 = event.x, event.y

    def button_up(self, event):
        #delete coords
        self.x1, self.y1 = None, None

    def motion(self, event):
        #when button is down and moving
        #here, functions for drawing will be used
        if self.paint_obj == "Line":
            self.create_line(event)


        #updating position of the mouse
        self.x1, self.y1 = event.x, event.y

    def create_line(self, event):
        #drawing line
        event.widget.create_line(self.x1, self.y1, event.x, event.y,
                                 smooth=tk.TRUE, fill="black", width=2)

my_app = Application()
my_app.mainloop()