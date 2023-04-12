#include "Product.hpp"
#include <iostream>
#include <string>

using namespace std;

int Product::nextID = 0;

Product::Product(string aProdName, double aPrice) : prodName(aProdName), price(aPrice), reviewRate(0) {

  prodID = createNewID();
  aProdName = "!None!"; //If the product name is the empty string, it should be set to "!None!"
    
}

void Product::displayProdInfo() {

  cout << "[" << getProdTypeStr() << "]" << endl; //accesses and displays product type
  cout << "Product ID: " << prodID << "    " << "Product Name: " << prodName << endl;
  cout << "Price: $" << price << "    " << "Product Review Rate: " << reviewRate << endl;
  displayContentsInfo(); //displays information for derived product-type specifically
}

prod_id_t Product::createNewID() {

  nextID += 1; //creating new product-wise ID
  return nextID;
}