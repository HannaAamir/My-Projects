//
//  Homework3.cpp
//
//
//  Created by Hanna Aamir on 3/24/23.
//

//#include "Homework3.hpp"
// HM3: Binary Search Tree sample starting code
// Abeer Khaleq
// CSCI2421 - 3/7/23

#include "BinaryST.h"
#include "Node.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

Node *convert(vector<int> const &keys, int low, int high) {
  // base case/ error handling
  if (low > high) {
    return NULL;
  }

  // locates the middle element of the current vector
  int mid = (low + high) / 2;

  // creates a new node from the middle element and then assigns it to the root
  Node *root = new Node(keys[mid]);

  // left subtree of the root is to be constructed by keys which are less than
  // middle element
  root->left = convert(keys, low, mid - 1);

  // right subtree of the root is to be constructed by keys more than the middle
  // element
  root->right = convert(keys, mid + 1, high);

  return root;
}

int main() {

  // declaring user variables
  int user_choice;
  int user_input;
  // vector stores user-inputted nodes to be converted into BST
  vector<int> nodes = {};
  // creates an instance of the BST
  BinaryST *binary_tree = new BinaryST();

  cout << "Enter items/nodes into BST/vector (enter '-1' to end): " << endl;

  while (1) {
    cin >> user_input;
    if (user_input == -1) // program exists if user enters -1
      break;
    nodes.push_back(
        user_input); // storing user-inputted nodes into vector for BST
  }

  sort(nodes.begin(),
       nodes.end()); // sorting the nodes of the BST in ascending order
  Node *head = convert(nodes, 0, nodes.size() - 1); // converting the nodes
  binary_tree->set_root(head); // setting the root of the binary tree as formed
                               // from convert function call

  //user menu
  cout << "\nTo access or alter the BST, select an option from the following menu by entering the associated number. \n";
  cout << "1. find minimum value. \n";
  cout << "2. find maximum value.\n";
  cout << "3. insert a new value.\n";
  cout << "4. display tree in preorder\n";
  cout << "5. display tree in postorder\n";
  cout << "6. display tree inorder\n";
  cout << "8. exit \n";
  cout << "--------------------------------- \n";

  // while loop presents various choices to user to access/alter BST and keeps
  // running until user enters 8
  while (user_choice != 8) {
    cout << "Enter input: ";
    cin >> user_choice;
    if (user_choice == 1) {
      cout << binary_tree->findMin() << endl;
    }

    if (user_choice == 2) {
      cout << binary_tree->findMax() << endl;
    }

    if (user_choice == 3) {
      int temp;
      cout << "Enter item to insert: ";
      cin >> temp;
      binary_tree->insert(temp);
    }

    if (user_choice == 4) {
      binary_tree->preorder();
    }

    if (user_choice == 5) {
      binary_tree->postorder();
    }

    if (user_choice == 6) {
      binary_tree->inorder();
    }

    if (user_choice == -1) {
      return 0;
    }
  }
}