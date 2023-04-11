from graphics import *
def main():

    winName = "Lab 4 - AamirHanna"
    
    color1 = input ("What color would you like the circle to be? ")
    
    x1, y1 = eval (input ("what are the x, y coordinates of the center of circle? "))
    
    radius1 = eval(input("what is the radius of the circle? "))

    win = GraphWin(winName, 500, 500)
    center1 = Point (x1, y1)
    circ1 = Circle(center1, radius1)
    circ1.setFill (color1)
    circ1.draw (win)

    x2 = x1
    y2 = y1 - (2*radius1)
    radius2 = radius1*(1/2)
    center2 = Point(x2, y2)
    circ2 = Circle(center2, radius2)
    circ2.setFill("green")
    circ2.draw(win)

    line = Line(center1, center2)
    line.setFill("red")
    line.draw(win)

    win.getMouse()

    for i in range(1):
        line.undraw()
        circ2.move(2*radius1, 2*radius1)
        line = Line(circ2.getCenter(),center1)
        line.setFill("red")
        line.draw(win)
        win.getMouse()
        line.undraw()
        circ2.move(-2*radius1, 2*radius1)
        line= Line(circ2.getCenter(), center1)
        line.setFill("red")
        line.draw(win)
        win.getMouse()
        line.undraw()
        circ2.move(-2*radius1, -2*radius1)
        line=Line(circ2.getCenter(),center1)
        line.setFill("red")
        line.draw(win)
        win.getMouse()
        line.undraw()
        circ2.move(2*radius1, -2*radius1)
        line = Line(circ2.getCenter(), center1)
        line.setFill("red")
        line.draw(win)
        win.getMouse()
        
    
