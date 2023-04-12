//
//  main.cpp
//  PA4
//
//  Created by Hanna Aamir on 10/22/22.
//

#include <iostream>
#include <math.h>
#include <string>
using namespace std;

enum ShapeType { INVALID = -1, RECTANGLE = 0, TRIANGLE, SQUARE, CIRCLE };
const double PI = M_PI;
int default_horizontal_spaces = 0;
char space = ' ';

double computeArea(
    ShapeType shape, double length1,
    double length2 =
        0) { // remove default arguments from definition + put only in
             // declaration + must be only in the rightmost position of all
             // paraaters in function prototype and function definition

  double area = 0.0;

  switch (shape) {
  case ShapeType::RECTANGLE:
  case ShapeType::SQUARE:
    area = length1 * length2;
    break;
  case ShapeType::TRIANGLE:
    area = (length1 * length2) /
           2.0; // ASSUMING LENGTH1 IS BASE AND LENGTH2 IS HEIGHT
    break;
  case ShapeType::CIRCLE:
    area = PI * (sqrt(length1 / 2.0)); // ASSUMING LENGTH1 IS DIAMETER
    break;
  default:
    std::cout << "An invalid shape.";
  }
  return area;
}

double computePerimeter(ShapeType shape, double length1, double length2 = 0) {
  double perimeter = 0.0;
  switch (shape) {
  case ShapeType::RECTANGLE:
  case ShapeType::SQUARE:
    perimeter = (2 * length1) + (2 * length2);
    break;
  case ShapeType::TRIANGLE:
    perimeter = (length1 * 2) +
                length2; // assuming length1 is side or based, NEEDS TO BE FIXED
    break;
  case ShapeType::CIRCLE:
    perimeter = 2 * PI * length1; // assuming length 1 is diameter
    break;
  default:
    std::cout << "An invalid shape.";
  }
  return perimeter;
}

void moveRight(int numOfHorizontalSpaces =
                   default_horizontal_spaces) { // make it equivalent so that in
                                                // moveup, move right matches
                                                // the previus function call
  std::cout << string(numOfHorizontalSpaces, ' ');
  default_horizontal_spaces = numOfHorizontalSpaces;
}
void moveUp(int numOfVerticalLines = 1) {

  std::cout << string(numOfVerticalLines, '\n') << endl;
  moveRight();
}

void draw(ShapeType shape, double length1, double length2=0,
          char lineType = '*') {
  // length1 is width (or base in triangle), length2 is height
  double square_height_adjustment =
      length1 - 2.0; // len2 is the same as len1 for a square
  double rectangle_height_adjustment = length2 - 2.0;
  double triangle_midpoint = (length1 / 2.0) - 1.0;
  double radius = length1 / 2.0;

  moveUp();

  switch (shape) {
  case ShapeType::RECTANGLE:
    cout << string(length1, lineType);
    moveUp();

    for (double h = 0.0; h < (rectangle_height_adjustment); h++) {
      std::cout << lineType;
      cout << string(length1 - 2.0, space); 
      std::cout << lineType;
      moveUp();
    }
    cout << string(length1, lineType) << endl; // could change endl to moveUp()
    break;

  case ShapeType::SQUARE:
    cout << string(length1, lineType); // width
   

    for (int h = 1; h < (square_height_adjustment/2); h++) {
      cout << endl << string(default_horizontal_spaces, space);
      cout << lineType;
      cout << string(square_height_adjustment, space);
      cout << lineType;
      
    }
    cout << endl << string(default_horizontal_spaces, space);
    cout << string(length1, lineType) << endl; // width
    break;

  case ShapeType::TRIANGLE:

    cout << string(triangle_midpoint, space);
    cout << lineType;
    moveUp();
    for (int h = 1; h < length2 - 1; h++) {
      if (triangle_midpoint - h > 0) {
        cout << string(triangle_midpoint - h, space);
      } else {
        break;
      }
      cout << lineType;
      cout << string(h * 2, space);
      cout << lineType << endl;
      moveUp();
    }
    cout << string(length1, lineType);

    break;
  case ShapeType::CIRCLE: {
    if (radius <= 2.0) {
      cout << "O" << endl;
    } else {
      if (length2 == 0) {

        cout << '(';
        cout << string(length1, lineType);
        cout << ')' << endl;
      } else {
        cout << "Error: circle dimensions unclear. Please try again" << endl;
      }
    }

    break;
  default:
    cout << "An invalid shape.";
  }
  }
}

int main(int argc, const char *argv[]) {
  // insert code here...
  moveRight(24);
  draw(CIRCLE, 2); // 0 should be removed
  moveRight(20);
  draw(TRIANGLE, 10, 5);
  moveRight(20);
  draw(SQUARE, 10, 0);
  moveRight(17);
  draw(CIRCLE, 17, 0, '.');
  moveRight(10);
  draw(RECTANGLE, 30, 6, '-');

  return 0;
}
