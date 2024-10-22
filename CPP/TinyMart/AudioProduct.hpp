#ifndef AUDIOPRODUCT_HPP
#define AUDIOPRODUCT_HPP

#include "Product.hpp"
#include <iostream>
#include <string>

using namespace std;
//enum type to sort thorugh integral data types representing the music genres
enum GenreType {Blues = 0, Classical, Country, Folk, Jazz, Metal, Pop, RnB, Rock, INVALID};
//associated string-type variable to access enum-type Genre
const string GenreString[] = {"Blues", "Classical", "Country", "Folk", "Jazz", "Metal", "Pop", "RnB", "Rock", "INVALID" };

class AudioProduct : public Product {

public:
 
    AudioProduct(); //default constructor
    AudioProduct(string aProdName, double aPrice, NameType aSinger); //song name, price, singer 

    //getters
    NameType getSinger() { return singer; }
    GenreType getGenre() { return genre; }
    //setters
    void setSinger(NameType aSinger) { singer = aSinger; }
    void setGenre(GenreType aGenre) { genre = aGenre; }
    //base-class functions - descriptions avalible in Product.hpp
    //functions are overrided to display information specific to audio product
    virtual string getProdTypeStr() override;
    virtual void displayProdInfo() override;
    virtual void displayContentsInfo() override;

private:
    NameType singer; //NameType from base class is used to access singer name
    GenreType genre; //enum-type variable for genre 

};

#endif