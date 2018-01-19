import tkinter as tk

class Application(tk.Tk):

    def __init__(self):#class constructor

        tk.Tk.__init__(self)#parent class constructor

        #window parameters
        self.title("Window Application")
        self.geometry("500x404")
        self.resizable(0,0)
        #menu tool bar
        self.menu_bar = tk.Menu(self)
        self.config(menu=self.menu_bar)
        #now let's create other mini-menu for cascade and other stuff
        self.min_menu = tk.Menu(self.menu_bar)
        self.menu_bar.add_cascade(label = "Draw", menu = self.min_menu)
        self.min_menu.add_command(label = "Line",
                                  command = lambda : self.set_tool("Line"))
        self.min_menu.add_separator()
        self.min_menu.add_command(label="Rectangle",
                                  command=lambda: self.set_tool("Rectangle"))
        self.min_menu.add_separator()
        self.min_menu.add_command(label="Triangle",
                                  command=lambda: self.set_tool("Triangle"))
        self.min_menu.add_separator()
        self.min_menu.add_command(label="Oval",
                                  command=lambda: self.set_tool("Oval"))
        self.min_menu.add_separator()

        #now other cascade
        self.info_menu = tk.Menu(self.menu_bar)
        self.menu_bar.add_cascade(label = "Options", menu = self.info_menu)
        #color cascade
        self.color_set = tk.Menu(self.info_menu)
        self.info_menu.add_cascade(label = "Colour", menu = self.color_set)
        self.color_set.add_command(label = "Black",
                                   command = lambda : self.give_clolor("black"))
        self.color_set.add_separator()
        self.color_set.add_command(label = "Blue",
                                   command = lambda : self.give_colour("blue"))
        self.color_set.add_separator()
        self.color_set.add_command(label="Gray",
                                   command=lambda: self.give_colour("gray"))
        self.color_set.add_separator()
        self.color_set.add_command(label="Green",
                                   command=lambda: self.give_colour("Green"))
        self.color_set.add_separator()
        self.color_set.add_command(label="Yellow",
                                   command=lambda: self.give_colour("yellow"))
        self.color_set.add_separator()
        self.color_set.add_command(label="Violet",
                                   command=lambda: self.give_colour("violet"))
        self.color_set.add_separator()
        self.color_set.add_command(label="Brown",
                                   command=lambda: self.give_colour("brown"))
        self.color_set.add_separator()
        self.color_set.add_command(label="Pink",
                                   command=lambda: self.give_colour("pink"))
        self.color_set.add_separator()
        #now adding cascade for outline color
        self.outline_color_set = tk.Menu(self.info_menu)

        self.info_menu.add_cascade(label="Outline colour", menu=self.outline_color_set)

        self.outline_color_set.add_command(label="Black",
                                   command=lambda: self.set_outline_color("black"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Blue",
                                   command=lambda: self.set_outline_color("blue"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Gray",
                                   command=lambda: self.set_outline_color("gray"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Green",
                                   command=lambda: self.set_outline_color("Green"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Yellow",
                                   command=lambda: self.set_outline_color("yellow"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Violet",
                                   command=lambda: self.set_outline_color("violet"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Brown",
                                   command=lambda: self.set_outline_color("brown"))
        self.outline_color_set.add_separator()
        self.outline_color_set.add_command(label="Pink",
                                   command=lambda: self.set_outline_color("pink"))
        self.outline_color_set.add_separator()

        #now to set the size of the font
        self.font_size = tk.Menu(self.info_menu)
        self.info_menu.add_cascade(label = "Size", menu = self.font_size)

        self.font_size.add_command(label = "1", command = lambda : self.set_size(1))
        self.font_size.add_command(label="2", command=lambda: self.set_size(2))
        self.font_size.add_command(label="3", command=lambda: self.set_size(3))
        self.font_size.add_command(label="4", command=lambda: self.set_size(4))
        self.font_size.add_command(label="5", command=lambda: self.set_size(5))
        self.font_size.add_command(label="6", command=lambda: self.set_size(6))
        self.font_size.add_command(label="7", command=lambda: self.set_size(7))
        self.font_size.add_command(label="8", command=lambda: self.set_size(8))
        self.font_size.add_command(label="9", command=lambda: self.set_size(9))
        self.font_size.add_command(label="10", command=lambda: self.set_size(10))

        #canvas object
        self.paint_here = tk.Canvas(self, width = self.winfo_reqwidth(),
                                    height = self.winfo_reqheight()*2, bg = "white")
        self.paint_here.pack(fill = tk.BOTH)

        #locations for drawing stuff
        self.x1, self.y1, self.x2, self.y2 = None, None, None, None
        self.color = "black"#default option
        self.outline_color = "black"#default option
        self.size = "2"#default option
        self.paint_obj = "Line"#default option
        self.bool_var = tk.BooleanVar(False)
        #binding buttons for drawing
        self.paint_here.bind("<B1-Motion>", self.motion)
        self.paint_here.bind("<ButtonPress-1>", self.button_down)
        self.paint_here.bind("<ButtonRelease-1>", self.button_up)


    def set_size(self, size):
        self.size = size

    def set_tool(self, tool):
        self.paint_obj = tool

    def set_outline_color(self, colour):
        self.outline_color = colour

    def give_colour(self, color):
        self.color = color

    def button_down(self, event):
        #take coords when button is down
        self.x1, self.y1 = event.x, event.y

    def button_up(self, event):
        self.x2, self.y2 = event.x, event.y

        #drawing oval-shaped object
        #this method is located here because
        #we must have coords/size of the oval given from above
        #it is not line-like drawing, size must be given before
        if self.paint_obj == "Oval":
            self.create_oval(event)

        elif self.paint_obj == "Triangle":
            self.create_triangle(event)

        #delete coords for other drawing tools
        self.x1, self.y1 = None, None

    def motion(self, event):
        #when button is down and moving
        #here, functions for drawing will be used
        if self.paint_obj == "Line":
            self.create_line(event)
            # updating position of the mouse
            self.x1, self.y1 = event.x, event.y

        elif self.paint_obj == "Rectangle":
            self.create_rectangle(event)



    def create_line(self, event):
        #drawing line
        event.widget.create_line(self.x1, self.y1, event.x, event.y,
                                 smooth = tk.TRUE, fill = self.color,
                                 width = self.size)

    def create_rectangle(self, event):
        #drawing rectangle
        event.widget.create_rectangle(self.x1, self.y1, event.x, event.y,
                                      fill = self.color,
                                      outline = self.outline_color)

    def create_oval(self, event):
        #drawing ovals
        event.widget.create_oval(self.x1, self.y1, self.x2, self.y2,
                                fill = self.color,
                                outline = self.outline_color)

    def create_triangle(self, event):
        #drawing triangle
        x3 = self.x1 - (self.x2 - self.x1)
        y3 = self.y2
        event.widget.create_polygon(self.x1, self.y1, self.x2, self.y2,
                                    x3, y3, fill = self.color,
                                    outline = self.outline_color)



my_app = Application()
my_app.mainloop()