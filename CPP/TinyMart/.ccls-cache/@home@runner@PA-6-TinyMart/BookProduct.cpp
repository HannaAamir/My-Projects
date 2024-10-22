#include "Product.hpp"
#include "BookProduct.hpp"
#include <iostream>
#include <string>

using namespace std;

BookProduct::BookProduct(string aProdName, double aPrice, NameType anAuthor, int pageNum) : Product(aProdName, aPrice), author(anAuthor), pages(pageNum) {}

void BookProduct::displayProdInfo() {
  Product::displayProdInfo();
}

void BookProduct::displayContentsInfo() {

  cout << "Author: " << author.firstName << " " << author.lastName << " " << endl;
  cout << "Pages: " << pages << " " << endl;
}