#ifndef BOOKPRODUCT_HPP
#define BOOKPRODUCT_HPP

#include "Product.hpp"
#include <iostream>
#include <string>

using namespace std;

class BookProduct : public Product {

public:
    BookProduct();
    BookProduct(string aProdName, double aPrice, NameType anAuthor, int pageNum); //book name, price, author, number of pages
    //getters
    NameType getAuthor() { return author; }
    int getPages() { return pages; }
    //setters
    void setAuthor(NameType aAuthor) { author = aAuthor; }
    void setPage(int aPages) { pages = aPages; }
    //base-class functions - descriptions avalible in Product.hpp
    //functions are overrided to display information specific to book product
    virtual string getProdTypeStr() override = 0;
    virtual void displayProdInfo() override;
    virtual void displayContentsInfo() override;

private:
    NameType author;
    int pages;

};

#endif