#ifndef header
#define header

class TinyCalculator {
public:
//Initialize running_total member variable in constructor as it is a non-static variable. Additionally, it is initialized to 0 for each class object to ensure accuracy.
  TinyCalculator() {
    running_total=0;
  }
//declare and define each operation type as an enum type, within the class, for successful operation type handling
  enum OpType {
    INVALID = -1,
    ADD = 0,
    SUBTRACT = 1,
    MULTIPLY = 2,
    DIVIDE = 3,
    MODULO = 4
  };
  static OpType displayUserMenu();
  /* static OpType displayUserMenu() is public and displays an introductory text about the different operation types and returns the OpType choice entered by the user. */
  int processUserInput(OpType operationType);
/*int processUserInput(OpType operationType) is a public driver function which employs a control panel role. It uses the OpType operationType paramter, the user's operation choice, to compute that particular calculation. Regardless of the operation type, it prompts the user for the left and right operand. Finally, it computes the result of the chosen operation, adds the result to the running total, increments the operation type count and asks if the user wants to do another calculation.  */
  void displayReport(); 
/* void displayReport() displays the final report about a particular TinyCalculator object (includes: the running total, the count of operations per type, the total count of operations and the average). */
  bool checkForPlayAgain();
/*bool checkForPlayAgain() acts as another public driver function and asks the user to play again. If the user enters 'Y' or 'y', then the function returns true. It is invoked in main() in a do-while loop to ensure the program continues to run, if need be. */
  int getRunningTotal() const;
/* int getRunningTotal() const returns the private member variable running_total to the user. It is of constant type to avoid any data tempering(encapsulation).*/
  int getAddCount() const; 
/*int getAddCount() const returns the private static member variable add_count to the user. It is  of constant type to avoid any data tempering (encapsulation).*/
  int getSubCount() const;
/*int getSubCount() const returns the private static member variable sub_count to the user. It is  of constant type to avoid any data tempering (encapsulation).*/
  int getMultCount() const;
/*int getMultCount() const returns the private static member variable mult_count to the user. It is  of constant type to avoid any data tempering (encapsulation).*/
  int getDivCount() const;
/*int getDivCount() const returns the private static member variable div_count to the user. It is  of constant type to avoid any data tempering (encapsulation).*/
  int getModCount() const;
/*int getModCount() const returns the private static member variable mod_count to the user. It is  of constant type to avoid any data tempering (encapsulation).*/
  int getTotalCount();
/*int getTotalCount() const returns the total count of operations to the user.*/
  int getAvgOp();
/*int getAvgOp() const returns the average of all operations to the user.*/

/* No setter functions have been declared for this class becuase the sole purpose of this program is to compute different artihmetic operations and keep track of them - so setting these computations manually defies the very implementation purpose of TinyCalculator. */

private:
 
  int running_total; //keeps track of the running_total for each TinyCalculator object
  static int add_count; //keeps track of the number of addition operations for each TinyCalculator object
  static int sub_count; //keeps track of the number of subtraction operations for each TinyCalculator object
  static int mult_count; //keeps track of the number of multiplication operations for each TinyCalculator object
  static int div_count; //keeps track of the number of division operations of each TinyCalculator object
  static int mod_count; //keeps track of the number of modulo operations of each TinyCalculator object
  int addition(int left, int right);
/*int addition(int left, int right) computes an addition operation using the left and right operand entered by the user. */
  int subtraction(int left, int right);
/* int subtraction(int left, int right) computes a subtraction operation using the left operand and by invoking addition() with the negative of the right operand, entered by the user.*/
  int multiplication(int left, int right);
/* int multiplication(int left, int right) computes a multiplication operation by adding the left operand by the numbers of the right operand.*/
  int division(int left, int right);
/*int division(int left, int right) computes a division operation by subtracting the right operand from the left operand until the result is less than the right operand, and then returns the number of subtractions */
  int modulo(int left, int right);
/* int modulo(int left, int right) computes by invoking division() to return the remainder (left operand - the division result * right operand). */
  int total_count_operations();
/* int total_count_operations() is a helper function which returns the total number of operations computed in an instance of TinyCalculator by adding all the static counter variables for each operation type.*/
  int average_operations(); 
/* int average_operations() is a helper function which returns the average of the total operations computed in an instance of TinyCalculator by dividing running_total by what is returned by total_count_operations()*/
};

#endif
