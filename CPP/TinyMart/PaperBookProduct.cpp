#include "Product.hpp"
#include "BookProduct.hpp"
#include "PaperBookProduct.hpp"
#include <iostream>
#include <string>

using namespace std;

PaperBook::PaperBook(string aProdName, double aPrice, NameType anAuthor, int pageNum) : BookProduct(aProdName, aPrice, anAuthor, pageNum) {}

string PaperBook::getProdTypeStr() {
  
  return "Paper book";
}