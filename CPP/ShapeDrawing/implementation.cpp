#include "functions.hpp"
#include <iostream>
#include <string>

using namespace std;
// initializes the number of default horizontal spaces to be moved on the
// console, to enable transitioning between drawing the different shapes
int default_horizontal_spaces = 0;
// space is used to draw the width of different shapes
char space = ' ';

double computeArea(ShapeType shape, double length1, double length2) {
  // area is intialized
  double area = 0.0;

  // switch statement used to sort through different shapes since they are of
  // enum type
  switch (shape) {
  case ShapeType::RECTANGLE:
    area = length1 * length2; // area of rectangle = width * height
    break;
  case ShapeType::SQUARE:
    area = length1 * length1; // area of square is length * length
    break;
  case ShapeType::TRIANGLE:
    area = (length1 * length2) /
           2.0; // assuming length1 = base, and length2=
                // height, area of triangle is (base*height)/2
    break;
  case ShapeType::CIRCLE:
    area = M_PI * (length1 * length1); // assuming length1 is radius, area of
                                       // circle is Pi*(radius)^2
    break;
  default:
    std::cout << "An invalid shape."; // driver program invoked function with an
                                      // invalid shape
  }
  return area;
}

double computePerimeter(ShapeType shape, double length1, double length2) {
  double triangle_side =
      sqrt(pow((length1 / 2), 2) +
           pow(length2, 2)); // declaring a variable to compute the isosceles
                             // side/hypotenuse of triangle

  double perimeter = 0.0; // initializing perimeter to be further computed
  // switch statement is used to deal with shapes as they are enum types
  switch (shape) {
  case ShapeType::RECTANGLE:
    perimeter =
        (2 * length1) +
        (2 * length2); // perimeter of a rectangle is (2*width) + (2*length)
    break;
  case ShapeType::SQUARE:
    perimeter = (4 * length1); // perimeter of a square is (side*4)
    break;
  case ShapeType::TRIANGLE:
    // length1 is base and length2 is height

    perimeter = length1 +
                (triangle_side *
                 2); // perimeter of an isosceles triangle is base + side + side
    break;
  case ShapeType::CIRCLE:
    perimeter = 2 * PI * length1; // assuming length 1 is radius, perimeter of a
                                  // circle is 2 * PI * radius
    break;
  default:
    std::cout << "An invalid shape."; // driver program invoked function with an
                                      // invalid shape
  }
  return perimeter; // perimeter is returned as a double
}
void moveRight(int numOfHorizontalSpaces) {
  std::cout << string(
      numOfHorizontalSpaces,
      ' '); // prints out the number of horizontal spaces specified by the
            // function paramater that was entered in the driver program
  default_horizontal_spaces =
      numOfHorizontalSpaces; // global default_horizontal_spaces variable is set
                             // to most recent function invocation paramater so
                             // that all shapes, from top to bottom, are aligned
                             // with eachother
}
void moveUp(int numOfVerticalLines) {

  std::cout << string(numOfVerticalLines, '\n')
            << endl; // prints out number of newlines/moves down on the console
                     // specified by the paramater entered by the driver program
  moveRight(
      default_horizontal_spaces); // moves right by it's most recent invocation
                                  // to stay in horizontal alignement throughout
                                  // drawing all the shapes
}

void draw(ShapeType shape, double length1, double length2, char lineType) {
  // length1 is width (or base in triangle, or radius in circle), length2 is
  // height
  double square_height_adjustment =
      length1 - 2.0; // assuming length1 is width, this subtracts the top and
                     // bottom drawn lines of the square, to prevent overlap
                     // with the length, when it will be drawn
  double rectangle_height_adjustment =
      length2 - 2.0; // length2 is the height, so this decrements the top and
                     // botton drawn lines of the rectangle, to prevent overlap
                     // with the width as it going to be drawn
  double triangle_midpoint = (length1 / 2.0) - 1.0;
  // centers the triangle to be drawn

  moveUp();

  switch (shape) {
  case ShapeType::RECTANGLE:
    cout << string(length1, lineType); // prints/draws width of rectangle
    moveUp(); // moves down on console to continue drawing in alignment

    // for loop draws out the length/height
    for (double h = 0.0; h < (rectangle_height_adjustment); h++) {
      std::cout << lineType;                // draws left height
      cout << string(length1 - 2.0, space); // fills the specified width with
                                            // space, to ultimately draw height
      std::cout << lineType;                // draws right height
      moveUp();
    }
    cout << string(length1, lineType) << endl; // draws bottom width
    break;

  case ShapeType::SQUARE:
    cout << string(length1, lineType); // draws the width

    // for loop draws out the length/height
    for (int h = 1; h < (square_height_adjustment / 2); h++) {
      cout << endl
           << string(default_horizontal_spaces,
                     space); // pads horizontal spaces to center and align the
                             // square
      cout << lineType;      // draws left height
      cout << string(square_height_adjustment,
                     space); // fills the specified width with space, to
                             // ultimately draw height
      cout << lineType;      // draws right height
    }
    cout << endl
         << string(default_horizontal_spaces,
                   space);                     // horizontally aligns the square
    cout << string(length1, lineType) << endl; // width
    break;

  case ShapeType::TRIANGLE:

    cout << string(
        triangle_midpoint,
        space); // starts drawing the isosceles triangle by centering it
    cout << lineType;
    moveUp();
    // length2 subtracts 1 to account for the top already being drawn
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
    cout << string(length1, lineType); // draws the base

    break;
  case ShapeType::CIRCLE: {
    // if the radius is less than or equal to 2, an O is drawn, otherwise, a
    // circle will be drawn on the console using the specified chracter
    if (length1 <= 2.0) {
      cout << "O" << endl;
    } else {
      if (length2 == 0) {

        cout << '(';
        cout << string(length1, lineType); // drawing the circle
        cout << ')' << endl;
      } else {
        cout << "Error: circle dimensions unclear. Please try again"
             << endl; // error management
      }
    }

    break;
  default:
    cout << "An invalid shape."; // printed to screen if driver program invoked
                                 // function with an invalid shape
  }
  }
}
