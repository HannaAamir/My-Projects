from graphics import *
def main():

    winName = input ("What would you like the name of the window to be? ")
    
    color1 = input ("What color would you like the circle to be? ")
    
    x1, y1 = eval (input ("what are the x, y coordinates of the center of circle? "))
    
    radius1 = eval(input("what is the radius of the circle? "))
   
    win = GraphWin(winName, 500, 500)
    center1 = Point (x1, y1)
    circ1 = Circle(center1, radius1)
    circ1.setFill (color1)
    circ1.draw (win)
       
    color2 = input ("What color would you like the second circle to be? ")
    x2, y2 = eval (input ("what are the x, y coordinates of the center of circle? "))
    radius2 = eval(input("what is the radius of the circle? "))
    center2 = Point (x2, y2)
    circ2 = Circle(center2, radius2)
    circ2.setFill (color2)
    circ2.draw (win)
    line = Line(center1, center2)
   
    line.setFill('red')
    
    line.draw(win)
    
    win.getMouse()
     
    for i in range (10):
         
        circ1.move(10,10)
        
        line.undraw()
        
        time.sleep(2)

    newCenter = circ1.getCenter()
   
    line = Line(circ1.getCenter(), center2)
    line.setFill('red')
    line.draw(win)
