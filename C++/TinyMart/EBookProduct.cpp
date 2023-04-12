#include "EBookProduct.hpp"
#include <iostream>
#include <string>

using namespace std;

EBook::EBook(string aProdName, double aPrice, NameType anAuthor, int pageNum)
    : BookProduct(aProdName, aPrice, anAuthor, pageNum) {}

string EBook::getProdTypeStr() { return "E book"; }