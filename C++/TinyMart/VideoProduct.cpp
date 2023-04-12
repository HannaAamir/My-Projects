#include "Product.hpp"
#include "VideoProduct.hpp"
#include <iostream>
#include <string>

using namespace std;

VideoProduct::VideoProduct(string aProdName, double aPrice, NameType aDirectorName, int aReleaseYear, int aRunTime) : Product(aProdName, aPrice), director(aDirectorName), releaseYear(aReleaseYear), runTime(aRunTime), filmRate(FilmRateType::NotRated) {}

string VideoProduct::getProdTypeStr() {
  return "Movie"; //returns "Movie" when product is an AudioProduct
}

void VideoProduct::displayProdInfo() {
  Product::displayProdInfo();
}

void VideoProduct::displayContentsInfo() {

  cout << "Release Year: " << releaseYear << endl;
  cout << "Film Rating: " << FilmRateString[filmRate] << endl;
  cout << "Runtime: " << runTime << endl;
  cout << "Director Name: " << director.firstName + " " + director.lastName << endl;
}

bool VideoProduct::isNewRelease (int theYear) {
  return theYear >= 2022;
}