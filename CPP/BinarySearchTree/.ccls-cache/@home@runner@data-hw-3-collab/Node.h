#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;
// Node class representing an int node in the tree with a left and right nodes
// pointers.
class Node {

public:
  // node members are made public for simplicity
  int element; // value of the node
  Node *left;  // left node pointer
  Node *right; // right node pointer

  Node() // default constructor
  {
    element = NULL;
    left = right = nullptr;
  }

  // constructor was changed to have default nullptrs to allow creation of one
  // node at a time
  Node(int e, Node *lt = nullptr,
       Node *rt = nullptr) // Constructor that takes left and right nodes.
  {
    element = e;
    left = lt;
    right = rt;
  }
};
#endif