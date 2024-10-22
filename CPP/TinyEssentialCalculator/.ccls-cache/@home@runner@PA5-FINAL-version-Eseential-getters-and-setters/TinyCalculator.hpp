#ifndef header
#define header

class TinyCalculator {
public:
//initialize running_total membr variable in constructor as it is a non-static variable. additionally, it is initialized to 0 for each class object to ensure accuracy.
  TinyCalculator() {
    running_total=0;
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
  int getRunningTotal() const;
  int getAddCount() const; //make getters const functions
  int getSubCount() const;
  int getMultCount() const;
  int getDivCount() const;
  int getModCount() const;
  int getTotalCount();
  int getAvgOp();

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

#endif
