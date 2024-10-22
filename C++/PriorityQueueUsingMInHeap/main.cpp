#include <iostream>
#include "priorityQueue.h"
using namespace std;

int main() {

  // initate heap object using PriorityQueue class
  priorityQueue minHeap;

// Prompt for user input and build a heap
    cout << "Please enter a list of values to build a binary heap. End with -1: ";
    int value;
    while (true) {
        cin >> value;

        if (value == -1) {
            break;
        }

        minHeap.insert(value);
    }

    cout << "Your heap printed: ";
    minHeap.print();


// Display a menu for the user to choose from, and execute the user-choice via switch statement
    int user_choice = 0;
    while (user_choice != 4) {
        cout << "\nEnter your selection below:\n1. Insert an item into the heap\n2. Delete the minimum.\n3. Print the array representation of the queue.\n4. Exit." << endl;
        cin >> user_choice;

        switch (user_choice) {
        case 1:
            int num;
            cout << "Please enter the value you would like to insert: ";
            cin >> num;
            minHeap.insert(num);
            break;
        case 2:
            minHeap.deleteMin();
            break;
        case 3:
            minHeap.printMin();
            break;
        case 4:
          cout << "Program terminated. Goodbye!" << endl;
          return -1;
        }
    }
}
