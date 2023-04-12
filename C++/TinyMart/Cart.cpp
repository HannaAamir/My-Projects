#include "Cart.hpp"
#include <iostream>
#include <string>

using namespace std;

bool Cart::addItem(Product *theProduct) {

  if (isCartFull()) {
    cout << "Error: Your cart is full." << endl; 
    cout << endl;
    return false;
  } else {
    purchasedItems[itemNum] = theProduct;
    itemNum++;
  }
  return true;
}

bool Cart::removeItem(prod_id_t theProductID) {

  for (int i = 0; i < itemNum; i++) {
    if (theProductID == purchasedItems[i]->getProdID()) {
      for (int j = i; j < itemNum; j++) {
        purchasedItems[j] = purchasedItems[j + 1];
      }
      itemNum--;
      return false;
    }
  }
  cout << "Error: Item could not be found. Remove item." << endl; 
  return true;
}

void Cart::displayCart() {

  double totalCost = 0;
  int numOfItems = 0;

  cout << "Cart Owner: " << owner.firstName + " " + owner.lastName << endl;
  cout << endl;

  for (int i = 0; i < itemNum; i++) {
    totalCost += purchasedItems[i]->getPrice();
    numOfItems++;
    purchasedItems[i]->displayProdInfo();
    cout << endl;
  }

  cout << "===== Summary of Purchase =====" << endl;
  cout << "Total number of purchases: " << numOfItems << endl;
  cout << "Total purchasing amount: $" << totalCost << endl;
  cout << "Average cost: $" << totalCost / numOfItems << endl;
}

bool Cart::isCartFull() {

  if (itemNum >= MAX_ITEMS) {
    return true;
  } else
    return false;
}
