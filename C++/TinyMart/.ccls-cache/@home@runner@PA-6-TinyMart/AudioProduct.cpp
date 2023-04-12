#include "Product.hpp"
#include "AudioProduct.hpp"
#include <iostream>
#include <string>

using namespace std;

AudioProduct::AudioProduct(string aProdName, double aPrice, NameType aSingerName) : Product(aProdName, aPrice), singer(aSingerName), genre(GenreType::INVALID) {}

string AudioProduct::getProdTypeStr() {

  return "Music"; //returns music when product is an "AudioProduct"
}

void AudioProduct::displayProdInfo() {
  Product::displayProdInfo();
}

void AudioProduct::displayContentsInfo() {

  cout << "Singer Name: " << singer.firstName << " " << singer.lastName << endl;
  cout << "Genre: " << GenreString[genre] << endl; //using genre string to access and display genre of song
}