# button.py
#    A simple Button widget.

from graphics import *

class Button:

    """A button is a labeled rectangle in a window.
    It is activated or deactivated with the activate()
    and deactivate() methods. The clicked(p) method
    returns true if the button is active and p is inside it."""

    def __init__(self, win, center, width, height, label, value = 0):
        """ Creates a rectangular button, eg:
        qb = Button(myWin, Point(30,25), 20, 10, 'Quit') """

        w,h = width/2.0, height/2.0
        x,y = center.getX(), center.getY()
        self.xmax, self.xmin = x+w, x-w
        self.ymax, self.ymin = y+h, y-h
        p1 = Point(self.xmin, self.ymin)
        p2 = Point(self.xmax, self.ymax)
        self.rect = Rectangle(p1,p2)
        self.rect.setFill('lightgray')
        self.rect.draw(win)
        self.label = Text(center, label)
        self.label.draw(win)
        self.deactivate()
        # a value that helps determine if the color has changed
        self.colorChange = 0
        # each button is assigned a value, default to 0
        self.value = value

    def clicked(self, p):
        """ RETURNS true if button active and p is inside"""
        return self.active and \
               self.xmin <= p.getX() <= self.xmax and \
               self.ymin <= p.getY() <= self.ymax

    def getLabel(self):
        """RETURNS the label string of this button."""
        return self.label.getText()

    def activate(self):
        """Sets this button to 'active'."""
        self.label.setFill('black')
        self.label.setSize(20)
        self.rect.setWidth(2)
        self.rect.setFill("white")
        self.active = 1

    def deactivate(self):
        """Sets this button to 'inactive'."""
        self.label.setFill('darkgrey')
        self.rect.setFill('darkgrey')
        self.rect.setWidth(1)
        self.active = 0

    def undraw(self):
        """undraws the buttons, uses graphics.py undraw"""
        self.rect.undraw()
        self.label.undraw()

    def clickedColor(self, p):
        """
        if a button is clicked, and it is currently white it changes to red
        and vise versa
        :param p: point
        :return: True or False
        """
        if self.clicked(p) and self.colorChange == 0:
            self.rect.setFill("red")
            self.colorChange = 1
        elif self.clicked(p) and self.colorChange == 1:
            self.rect.setFill("white")
            self.colorChange = 0
        return self.xmin <= p.getX() <= self.xmax and \
               self.ymin <= p.getY() <= self.ymax

    def getColor(self):
        """returns the value of the colorChange, can show if button is red or white"""
        return self.colorChange

    def buttonValue(self):
        """returns the value of the button"""
        return self.value
