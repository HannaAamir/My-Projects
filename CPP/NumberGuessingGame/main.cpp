// import libaries to enable generation of a random number each time the game is played

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main() {

  // define and declare variables
  int guess;
  int num;
  int tries = 0;
  // set user input answer as yes ('Y') to execute while loop once and begin the game initially 
  char answer = 'Y';

  // outer while loop to play another round of the game according to user input 
  while (answer == 'y' || answer == 'Y') {
    //generate random number in outer while loop to generate a new number for each new game
    srand(time(NULL));
    num = rand() % 1000;
    //prompt user to enter their guess
    cout << "Enter your guess number: ";
    //inner nested while loop executes with guess hints for user, while their guess is not equivalent to the random number 
    while (guess != num) {
      // the number of tries increases with each iteration of this inner nested while loop to inform user how many tries it took them to guess correctly 
      tries++;
      // user guess input is read to be evaluated
      cin >> guess;
      // the following two if-else branches alert the user about whether their guess is greater or lower than the randon number
      if (guess > num) {
        cout << guess << " is greater than the random number. Try it again: ";
        //cin >> guess;
      } else if (guess < num) {
        cout << guess << " is lower than the random number. Try it again: ";
      } else {
        // this final else branch executes if the user guess is correct
        cout << "Great!! " << guess << " is correct. You guessed it in "
             << tries << " tries.";       
        
        }
    }
    //  outer while loop concludes with asking the user if they would like to play again 
    cout << "\nDo you want to try it again? [Y/N]";
    // user's answer is read as input and evaluated to potentially execute outer while loop and begin the game again
    cin >> answer;
  }

  return 0;
}
