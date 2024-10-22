#ifndef header
#define header
//include the math library to use M_PI, sqrt() and pow()
#include <math.h>

// globally declared enum type which contains all integral constants representing each shape
enum ShapeType { INVALID = -1, RECTANGLE = 0, TRIANGLE, SQUARE, CIRCLE };
//declaring global Pi variable as constant Pi from math library for accuracy and precision
const double PI = M_PI;

double computeArea( ShapeType shape, double length1, double length2 = 0);
//double ComputeArea uses shape, length1(width/base) and length2(height/length) to compute and return the area of a specified shape. Additionally, the default value for length2 is given to account for shapes with only one paramater (ie. circle, square).
double computePerimeter(ShapeType shape, double length1, double length2 = 0);
//double computePerimeter using shape, length1(width/base), length2(height/length1) to compute and return the perimeter of specified shape. Additionally, the default value for length2 is given to account for shapes with only one paramater (ie. circle, square)
void moveRight(int numOfHorizontalSpaces = 0);
//void moveRight determines the horizontal starting point on the screen by moving the shape right on the console by the amount specified in the paramater (numOfHorizontalSpaces). 
//default value is set to 0 to enable funcition invocations when transitioning from different shapes to be drawn.
void moveUp(int numOfVerticalLines = 1);
//void moveUp vetically moves the shape down on the console specified by the paramater numOfVerticalLines.
//numOfVerticalLines has a defult value of 1 to move down on the console while drawing a specific shape
void draw(ShapeType shape, double length1, double length2=0,
          char lineType = '*');
//void draw draws the specified shape, line by line, using length1 (width/base), length2(height/length) and lineType.
//lineType has a default character '*' to draw the shape if the driver program does not specify a character.
//length2 has a default value of 0 to account for shapes with only one paramter (ie, circle, square)

#endif

