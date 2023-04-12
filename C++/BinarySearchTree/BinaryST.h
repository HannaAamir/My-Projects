#ifndef BINARYST_H
#define BINARYST_H
#include "Node.h"

using namespace std;

class BinaryST {
public:
  // default constructor
  Node *root; // tree root node
  BinaryST() { root = nullptr; }
  Node *get_root();

  void set_root(Node *root);
  void insert(int item);
  int findMin() const;
  int findMax() const;
  // print the tree inorder traversal format
  void inorder() const;
  // print the tree in preorder traversal format
  void preorder() const;
  // print the tree in postorder traversal format.
  void postorder() const;
  // calculates and returns the height of the tree

  // private members
private:
  // private helper functions for recursion
  void
  inorder(const Node *sroot) const; // recursive function for inorder traversal
  void preorder(
      const Node *sroot) const; // recursive function for preorder traversal
  void postorder(
      const Node *sroot) const; // recursive function for postorder traversal

  int findMin(Node *sroot) const;   // recursive function to find and return the
  int findMax(Node *sroot) const;   // recursive function to find and return the
  void insert(int item, Node *&rt); // recursive function for insert //change
};
#endif