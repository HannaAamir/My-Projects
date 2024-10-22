#include <iostream>
#include <string>
using namespace std;

class TinyCalculator {
public:
//initialize all static counter variables for each operation to be 0, in a constructor, so that each class object can have an accurate report
  TinyCalculator() {
    running_total=0;//i'm here :D ITS WORKING ACCURAL
  }
//decalre and define each operation type as an enum type, within the class, for appropriate reference
  enum OpType {
    INVALID = -1,
    ADD = 0,
    SUBTRACT = 1,
    MULTIPLY = 2,
    DIVIDE = 3,
    MODULO = 4
  };
  static OpType displayUserMenu();
  //
  int processUserInput(OpType operationType);
  void displayReport(); // maybe not void
  bool checkForPlayAgain();

  //    int const getRunningTotal();
  //    int const getAddCount(); //make getters const functions
  //    int const getSubCount();
  //    int const getMultCount();
  //    int const getDivCount();
  //    int const getModCount();
  //    int const getTotalCount();
  //    int const getAvgOp();
private:
  // might not need this
  int running_total;
  static int add_count;
  static int sub_count;
  static int mult_count;
  static int div_count;
  static int mod_count;
  int addition(int left, int right);
  int subtraction(int left, int right);
  int multiplication(int left, int right);
  int division(int left, int right);
  int modulo(int left, int right);
  int total_count_operations(); // helper function
  int average_operations();     // helper function
};

int TinyCalculator::add_count = 0;
int TinyCalculator::sub_count = 0;
int TinyCalculator::mult_count = 0;
int TinyCalculator::div_count = 0;
int TinyCalculator::mod_count = 0;

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
  int num_of_subtractiions = 0;
  int quotient = 0;
  while (quotient >= right) {
    quotient = subtraction(left, right);
    num_of_subtractiions++;
  }
  return num_of_subtractiions;
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

  cout << "The program (TinyCalculator) prompts the user to select an "
          "arithmetic operation, then calculates and outputs the answer. The "
          "program runs until the user does not want to continue. (Y/N) A "
          "final running sum and average of all calculations done along with "
          "other statistics are displayed at the end."
       << endl
       << "Select the operation type you would like to calculate by entering "
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
    add_count++;
    break;
  case OpType::SUBTRACT:
    result = subtraction(first, second);
    sub_count++;
    break;
  case OpType::MULTIPLY:
    result = multiplication(first, second);
    mult_count++;
    break;
  case OpType::DIVIDE:
    result = division(first, second);
    div_count++;
    break;
  case OpType::MODULO:
    result = modulo(first, second);
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
  cout << "CALCULATOR REPORT:";
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

  int main() {
    bool more = true; // more expression to enter?

    TinyCalculator theCalculator;
    TinyCalculator::OpType OperationType;

    do {
      string userInput; // Holding the user input

      cout << "\n";  
			
      // display the static displayUserMenu() member function
      OperationType = TinyCalculator::displayUserMenu();

      theCalculator.processUserInput(OperationType);

      // check if the user wants to enter more expression
      more = theCalculator.checkForPlayAgain(); 
    } while (more);

    // display a final report of two calculators
    theCalculator.displayReport();

    return 0;
  }

//