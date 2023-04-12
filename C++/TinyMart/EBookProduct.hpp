#ifndef EBOOKPRODUCT_HPP
#define EBOOKPRODUCT_HPP

#include "Product.hpp"
#include "BookProduct.hpp"
#include <iostream>
#include <string>

using namespace std;

class EBook : public BookProduct {

public:

    EBook(); //default constructor
    EBook(string aProdName, double aPrice, NameType anAuthor, int pageNum); //book name, price, author, number of pages
    virtual string getProdTypeStr() override; //getter for type of book is overriden as this is derived from Book Class

private:

};

#endif