import tkinter as tk

class Application(tk.Tk):

    def __init__(self):#class constructor

        tk.Tk.__init__(self)#parent class constructor
        ###
        self.title("Window Application")
        self.geometry("500x404")
        self.resizable(0,0)
        ###
        self.menu = tk.Menu(self)#menu bar
        self.file_menu = tk.Menu(self.menu, tearoff = 0)
        #file menu bar which contains cascade
        self.color_menu = tk.Menu(self.file_menu, tearoff = 0)
        self.menu.add_cascade(label = "Edit", menu = self.file_menu)
        #adding cascade to the bar
        self.file_menu.add_cascade(label = "Color choose", menu = self.color_menu)
        self.file_menu.add_command(label = "Draw line", command = self.draw_line)
        self.color_menu.add_command(label = "Blue", command = lambda: self.color_change("blue"))
        self.color_menu.add_command(label="Red", command= lambda: self.color_change("red"))
        self.color = "black"  # default color is black
        #canvas widget filed
        self.w = tk.Canvas(self, width = self.winfo_reqwidth(), height = self.winfo_reqheight()*2, bg = "white")
        self.w.pack(fill = tk.BOTH)
        self.w.bind("<B1-Motion>", self.paint)
        self.w.bind("<B3-Motion>", self.rubber)
        #now, define coordinates for other drawings
        self.x1, self.y1, self.x2, self.y2 = None, None, None, None
        self.w.bind("<Button-1>", self.first_coords)
        self.w.bind("<Button-3>", self.second_coords)

        self.config(menu = self.menu)

    def first_coords(self, event):
        self.x1, self.y1 = event.x, event.y

    def second_coords(self, event):
        self.x2, self.y2 = event.x, event.y

    def draw_line(self):
        self.w.create_line(self.x1, self.y1, self.x2, self.y2, fill = self.color)

    #paint method
    def paint(self, event):
        x1, y1 = event.x -1, event.y -1
        x2, y2 = event.x +1, event.y +1
        self.w.create_oval(x1, y1, x2, y2, fill = self.color, outline=self.color)

    def rubber(self, event):
        x1, y1 = event.x - 10, event.y - 10
        x2, y2 = event.x + 10, event.y + 10
        self.w.create_oval(x1, y1, x2, y2, fill = "white", outline = "white")

    #color change method
    def color_change(self, color):
        #here, add other colors in the cascade
        if color == "blue": self.color = "blue"
        elif color == "red": self.color = "red"

my_app = Application()
my_app.mainloop()