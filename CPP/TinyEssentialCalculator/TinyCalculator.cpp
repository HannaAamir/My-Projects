#include "TinyCalculator.hpp"
#include <iostream>

using namespace std;
//all static counter variables for operation type had to be intialized to 0 outside of the class and outside of the constructor to be implemented for each instance/object of TinyCalculator
int TinyCalculator::add_count = 0;
int TinyCalculator::sub_count = 0;
int TinyCalculator::mult_count = 0;
int TinyCalculator::div_count = 0;
int TinyCalculator::mod_count = 0;

//below are the getter function to return the private member variables or functions, that otherwise wouldn't be able to be soley accessed by the user
int TinyCalculator::getRunningTotal() const {
  return running_total;
}
int TinyCalculator::getAddCount() const{
  return add_count;
}
int TinyCalculator::getSubCount() const {
  return sub_count;
}
int TinyCalculator::getMultCount() const {
  return mult_count;
}
int TinyCalculator::getDivCount() const {
  return div_count;
}
int TinyCalculator::getModCount() const {
  return mod_count;
}
int TinyCalculator::getTotalCount() {
  return total_count_operations();
}
int TinyCalculator::getAvgOp() {
  return average_operations();
}

int TinyCalculator::addition(int left, int right) {
  left = left;
  right = right;
  //computing the addition of the left and right operand entered by the user
  return left + right;
}

int TinyCalculator::subtraction(int left, int right) {
  left = left;
  //negating the right operand
  right = (0 - right);
  //adding the negated right operand to compute a subtraction operation
  return addition(left, right);
}

int TinyCalculator::multiplication(int left, int right) {
  int product = left; //initializing the product to the left operand, to be added right number of times to itself
  for (int r = 1; r < right;
       r++) { // r is 1 and less then right because we already added it once by
              // product initialization
    product += addition(left, 0); //invoking addition() to add left operand right number of times
  }
  return product; //returning the product
}

int TinyCalculator::division(int left, int right) {
  int num_of_subtractions = 0; 

  while (left >= right) { //keeps subtracting right from left until the result is less than the right operand
    left = subtraction(left, right);
    num_of_subtractions++; 
  }
  return num_of_subtractions; //returning the number of subtraction, essentially the quotient
}

int TinyCalculator::modulo(int left, int right) {

  int division_result = (division(left,right) * right); //
  int remainder = left - division_result; //the quotient gets subtracted by the divisor to return the remainder (modulo) 
  return remainder;
}

int TinyCalculator::total_count_operations() {
  return add_count + sub_count + mult_count + div_count + mod_count;  //adding all the static counter variables to return the total count of all operations
}

int TinyCalculator::average_operations() {
  return running_total / total_count_operations(); //the average of all operations is the running total divided by the total number of operations
}

TinyCalculator::OpType TinyCalculator::displayUserMenu() {
  char user_choice; //declare a variable for the user to enter their choice of operation


       cout << "Select the operation type you would like to calculate by entering "
          "the first letter of the operation."
       << endl;
  cout << "(A)ddition" << endl
       << "(S)ubtraction" << endl
       << "(M)ultiplication" << endl
       << "(D)ivision" << endl
       << "(%)Modulo" << endl; //introductory text for the user to choose an operation

  cin >> user_choice;
  TinyCalculator::OpType operation; //variable to assign and return the user's operation choice
  switch (user_choice) {
  case 'A': // characters representing the operations
    cout << "You selected addition." << endl; //outputs choice of user
    operation = OpType::ADD; //user's operation is assigned OpType enum value for further computation
    break;
  case 'S':
    cout << "You selected subtraction."<< endl;
    operation = OpType::SUBTRACT;
    break;
  case 'M':
    cout << "You selected multiplication." << endl;
    operation = OpType::MULTIPLY;
    break;
  case 'D':
    cout << "You selected division." << endl;
    operation = OpType::DIVIDE;
    break;
  case '%':
    cout << "You selected modulo." << endl;
    operation = OpType::MODULO;
    break;
  default:
    cout << "Invalid selection. Please try again!" << endl; //invalid operation
    operation = OpType::INVALID;
    break;
  }
  return operation; //user's choice of operation is returned for further computation
}

int TinyCalculator::processUserInput(OpType operationType) {
  int first = 0; //left operand
  int second = 0; //right operand
  int result = 0; //operation computation result
  cout << "Enter your first number: "; //user is prompted to enter left and right operands
  cin >> first;
  cout << "Enter your second number: ";
  cin >> second;

  switch (operationType) { //user input is processed/iterated to see if it matches an OpType operation

  case OpType::ADD:
    result = addition(first, second); //operation function matching operation type is invoked to peform calculation
    cout << "The answer: " << first << " + " << second <<" = "<< result << endl;  //displays the user's desired calculation
    add_count++; //operation counter static variable is updated/incremented
    break;
  case OpType::SUBTRACT:
    result = subtraction(first, second);
    cout << "The answer: " << first << " - " << second <<" = "<< result << endl; 
    sub_count++;
    break;
  case OpType::MULTIPLY:
    result = multiplication(first, second);
    cout << "The answer: " << first << " * " << second <<" = "<< result << endl; 
    mult_count++;
    break;
  case OpType::DIVIDE:
    result = division(first, second);
    cout << "The answer: " << first << " / " << second <<" = "<< result << endl; 
    div_count++;
    break;
  case OpType::MODULO:
    result = modulo(first, second);
    cout << "The answer: " << first << " % " << second <<" = "<< result << endl; 
    mod_count++;
    break;
  default:
    cout
        << "Invalid operation. No calculations could be done, please try again."
        << endl;
    break;
  }
  running_total += result; //running total is incremented/updated with the most recent calculation of a particular TinyCalculator instance
  return result; //result of the calculation is returned
}

void TinyCalculator::displayReport() {
  //as specified in TinyCalculator.hpp, a report is displayed to the screen consisting of various data (eg. counter of each operation type, average etc.)
  cout << endl << "CALCULATOR REPORT" << endl;
  cout << "Addtions: " << add_count << endl;
  cout << "Subtractions: " << sub_count << endl;
  cout << "Multiplications: " << mult_count << endl;
  cout << "Divisions: " << div_count << endl;
  cout << "Modulos: " << mod_count << endl;
  cout << "The total count of all operations: " << total_count_operations()
       << endl;
  cout << "The running total of all operation types: " << running_total << endl;
  cout << "The average of total operations: " << average_operations() << endl;
}

bool TinyCalculator::checkForPlayAgain() {
  char user_input;
  cout << "Would you like to do another calculation - yes (Y/y) or no (N/n)?"
       << endl; //prompts the user to run the calculator again, possibly
  cin >> user_input;

		if (user_input == 'y' || user_input == 'Y')
			return true; //function returns true if user indicates wanting to run the calculator again
		else {
      return false;
    }
	}

