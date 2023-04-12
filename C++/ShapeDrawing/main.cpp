

#include <iostream>
// include header file to invoke all functions
#include "functions.hpp"

using namespace std;

int main(int argc, const char *argv[]) {

  // function calls to draw the different shapes
  moveRight(24);
  draw(CIRCLE, 2);
  moveRight(20);
  draw(TRIANGLE, 10, 5);
  moveRight(20);
  draw(SQUARE, 10, 0);
  moveRight(17);
  draw(CIRCLE, 17, 0, '.');
  moveRight(10);
  draw(RECTANGLE, 30, 6, '-');

  // setting the digit precision for the perimeter and area values to be
  // computed
  cout.setf(std::ios::fixed); // decimal point and trailing zeros
  cout.setf(std::ios::showpoint);
  cout.precision(2);

  // computes and prints the area and perimeter of each shape drawn
  cout << "Area of the first circle is: " << computeArea(CIRCLE, 2)
       << " square units."
       << "\n";
  cout << "Perimeter of the first circle is: " << computePerimeter(CIRCLE, 2)
       << " units." << endl;
  cout << "Area of the triangle is: " << computeArea(TRIANGLE, 10, 5)
       << " square units."
       << "\n";
  cout << "Perimeter of the triangle is: " << computePerimeter(TRIANGLE, 10, 5)
       << " units." << endl;
  cout << "Area of the square is: " << computeArea(SQUARE, 10, 0)
       << " square units."
       << "\n";
  cout << "Perimeter of the square is: " << computePerimeter(SQUARE, 10, 0)
       << " units." << endl;
  cout << "Area of the second circle is: " << computeArea(CIRCLE, 16, 0)
       << " square units."
       << "\n";
  cout << "Circumference of second circle is: "
       << computePerimeter(CIRCLE, 16, 0) << " units." << endl;
  cout << "Area of the rectangle is: " << computeArea(RECTANGLE, 30, 6)
       << " square units."
       << "\n";
  cout << "Perimeter of the rectangle is: "
       << computePerimeter(RECTANGLE, 30, 6) << " units." << endl;

  // declaring and intializing variables to to compute the total area and total
  // perimeter of all shapes combines
  double total_area = computeArea(CIRCLE, 2) + computeArea(TRIANGLE, 10, 5) +
                      computeArea(SQUARE, 10, 0) + computeArea(CIRCLE, 16, 0) +
                      computeArea(RECTANGLE, 30, 6);
  double total_perimeter =
      computePerimeter(CIRCLE, 2) + computePerimeter(TRIANGLE, 10, 5) +
      computePerimeter(SQUARE, 10, 0) + computePerimeter(CIRCLE, 16, 0) +
      computePerimeter(RECTANGLE, 30, 6);
  // printing the total area and the total perimeter
  cout << "Total Area: " << total_area << " square units." << endl;
  cout << "Total Perimeter: " << total_perimeter << " units." << endl;
  return 0;
}
