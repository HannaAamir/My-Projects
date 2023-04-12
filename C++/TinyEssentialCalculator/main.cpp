#include <iostream>
#include <string>
#include <cstdlib>
#include "TinyCalculator.hpp"
using namespace std;


  int main() {
     

    TinyCalculator theCalculator; //instantiating class object
    TinyCalculator::OpType OperationType; //declaring a variable to reference operation type specified in the class
      cout << "The program (TinyCalculator) prompts the user to select an "
          "arithmetic operation, then calculates and outputs the answer. The "
          "program runs until the user does not want to continue. A "
          "final running sum and average of all calculations done along with "
          "other statistics are displayed at the end."
       << endl; //program begins interaction with the user by informing them with a description of the purpose
    bool more = true;  //allows the do-while loop to execute/drives the program
   
    do {
      string userInput; // Holding the user input

      cout << "\n";  
			
      // display the static displayUserMenu() member function
      OperationType = TinyCalculator::displayUserMenu();

      theCalculator.processUserInput(OperationType); //processes the user's input for specified operation

      // check if the user wants to enter more expression
      more = theCalculator.checkForPlayAgain(); 
    } while (more);

    // display a final report of the calculator object
    theCalculator.displayReport();


    return 0;
  }

//