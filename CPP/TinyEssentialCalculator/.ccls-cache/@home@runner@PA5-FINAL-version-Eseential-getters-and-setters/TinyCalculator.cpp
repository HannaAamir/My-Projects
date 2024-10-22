#include "TinyCalculator.hpp"
#include <iostream>

using namespace std;

int TinyCalculator::add_count = 0;
int TinyCalculator::sub_count = 0;
int TinyCalculator::mult_count = 0;
int TinyCalculator::div_count = 0;
int TinyCalculator::mod_count = 0;
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
  return left + right;
}

int TinyCalculator::subtraction(int left, int right) {
  left = left;
  right = (0 - right);
  return addition(left, right);
}

int TinyCalculator::multiplication(int left, int right) {
  int product = left;
  for (int r = 1; r < right;
       r++) { // r is 1 and less then right because we already added it once by
              // product initialization
    product += addition(left, 0);
  }
  return product;
}

int TinyCalculator::division(int left, int right) {
  int num_of_subtractions = 0;

  while (left >= right) {
    left = subtraction(left, right);
    num_of_subtractions++;
  }
  return num_of_subtractions;
}

int TinyCalculator::modulo(int left, int right) {
  int remainder = left % right;
  return remainder;
}

int TinyCalculator::total_count_operations() {
  int total = (add_count + sub_count + mult_count + div_count + mod_count);
  return total;
}

int TinyCalculator::average_operations() {
  return running_total / total_count_operations();
}

TinyCalculator::OpType TinyCalculator::displayUserMenu() {
  char user_choice;


       cout << "Select the operation type you would like to calculate by entering "
          "the first letter of the operation."
       << endl;
  cout << "(A)ddition" << endl
       << "(S)ubtraction" << endl
       << "(M)ultiplication" << endl
       << "(D)ivision" << endl
       << "(%)Modulo" << endl;

  cin >> user_choice;
  TinyCalculator::OpType operation;
  switch (user_choice) {
  case 'A': // characters representing the operations
    cout << "You selected addition." << endl;
    operation = OpType::ADD;
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
    cout << "Invalid selection. Please try again!" << endl;
    operation = OpType::INVALID;
    break;
  }
  return operation;
}

int TinyCalculator::processUserInput(OpType operationType) {
  int first = 0;
  int second = 0;
  int result = 0;
  cout << "Enter your first number: ";
  cin >> first;
  cout << "Enter your second number: ";
  cin >> second;

  switch (operationType) {

  case OpType::ADD:
    result = addition(first, second);
    cout << "The answer: " << first << " + " << second <<" = "<< result << endl; 
    add_count++;
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
  running_total += result;
  return result;
}

void TinyCalculator::displayReport() {
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
  cout << "Do you want to do another calculation; yes (Y/y) or no (N/n)?"
       << endl;
  cin >> user_input;

		if (user_input == 'y' || user_input == 'Y')
			return true;
		else {
      return false;
    }
	}

