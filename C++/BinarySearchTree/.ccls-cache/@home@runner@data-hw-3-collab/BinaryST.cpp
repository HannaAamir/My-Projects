#include "BinaryST.h"

// made this getter function to access private element of the class, to further
// be accessed and used by convert function in main.cpp
Node *BinaryST::get_root() { return root; }

// matching setter function
void BinaryST::set_root(Node *root) { this->root = root; }

void BinaryST::insert(int item) { // insert a new node with the value item if
  insert(item, root);             // it is not in the tree.
}

int BinaryST::findMin()
    const {             // find the minimum value in the tree and return it.
  return findMin(root); // private function for recursion
}

int BinaryST::findMax()
    const { // find the maximum value in the tree and return it.
  return findMax(root);
}
// print the tree inorder traversal format
void BinaryST::inorder() const {
  inorder(root); // private function for recursion
  cout << endl;
}
// print the tree in preorder traversal format
void BinaryST::preorder() const {
  preorder(root); // private function for recursion
  cout << endl;
}
// print the tree in postorder traversal format.
void BinaryST::postorder() const {
  postorder(root); // private function for recursion
  cout << endl;
}

void BinaryST::inorder(
    const Node *sroot) const // recursive function for inorder traversal
{
  // inorder traversal is value of nodes in sorted order - right, root, and
  // left. we begin with left in this loop however, it is still in order when
  // reversed, which is negligible.
  if (sroot != NULL) {
    inorder(sroot->left);
    cout << sroot->element << " ";
    inorder(sroot->right);
  }
}
void BinaryST::preorder(
    const Node *sroot) const // recursive function for preorder traversal
{
  // preorder traversal is root, left, right, hence the order of pointer access
  // in the loop
  if (sroot != NULL) {
    cout << sroot->element << " ";
    preorder(sroot->left);
    preorder(sroot->right);
  }
}
void BinaryST::postorder(
    const Node *sroot) const // recursive function for postorder traversal
{
  // postorder is left, right, root, hence the order of pointer access in the
  // loop
  if (sroot != NULL) {
    postorder(sroot->left);
    postorder(sroot->right);
    cout << sroot->element << " ";
  }
}

int BinaryST::findMin(Node *sroot) const // recursive function to find and
                                         // return the minimum value in the tree
{
  // as you traverse down left in a BST, the node value gets smaller, hence the
  // recursive call if while traversing down, there is no node, the most
  // recently traversed left node is returned as it is the minimum
  if (sroot->left == nullptr)
    return sroot->element;
  return findMin(sroot->left);
}
int BinaryST::findMax(Node *sroot) const // recursive function to find and
                                         // return the maximum value in the tree
{
  // as you traverse down right in a BST, the node value gets larger, hence the
  // recursive call if while traversing down, there is no node, the most
  // recently traversed right node is returned as it is the maximum
  if (sroot->right == nullptr)
    return sroot->element;
  return findMax(sroot->right);
}

void BinaryST::insert(int item,
                      Node *&rt) // recursive function for insert //change
 {
  // if there is no root node, the new node is placed as the root
  if (rt == nullptr) {
    rt = new Node(item);
  }

  // if the given node value (item) is less than the root node value, then place
  // it  in the left subtree
  if (item < rt->element) {
    insert(item, rt->left);
  }
  // if the given node value (item) is greater than the root node, then place it
  // in the right subtree
  else if (item > rt->element) {
    insert(item, rt->right);
  }
}
