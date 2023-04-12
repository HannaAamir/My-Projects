#include <iostream>
#include <string>
#include "TinyCalculator.hpp"
using namespace std;


  int main() {
     // more expression to enter?

    TinyCalculator theCalculator;
    TinyCalculator::OpType OperationType;
      cout << "The program (TinyCalculator) prompts the user to select an "
          "arithmetic operation, then calculates and outputs the answer. The "
          "program runs until the user does not want to continue. (Y/N) A "
          "final running sum and average of all calculations done along with "
          "other statistics are displayed at the end."
       << endl;
    bool more = true;
    //int three_user_tries = 0; //this ensures that the user does at least 3 calculations as specified in assignment limitations/assumptions
    do {
      string userInput; // Holding the user input

      cout << "\n";  
			
      // display the static displayUserMenu() member function
      OperationType = TinyCalculator::displayUserMenu();

      theCalculator.processUserInput(OperationType);

      // check if the user wants to enter more expression
      //three_user_tries++;
      more = theCalculator.checkForPlayAgain(); 
    } while (more);

    // display a final report of two calculators
    theCalculator.displayReport();


    return 0;
  }

//