
#include "AudioProduct.hpp"
#include "BookProduct.hpp"
#include "Cart.hpp"
#include "EBookProduct.hpp"
#include "PaperBookProduct.hpp"
#include "Product.hpp"
#include "VideoProduct.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // create the various product objects: 3 AudioProduct objects, 2 VideoProduct
  // objects, 1 ebook and 1 paper book objects
  NameType aName{"Beetles", ""};
  AudioProduct music1("Yesterday", 16.5, aName);
  music1.setGenre(GenreType::Pop);
  music1.setReviewRate(9.8);

  aName = {"Michael", "Jackson"};
  AudioProduct music2("We are the World", 13.75, aName);
  music2.setGenre(GenreType::Country);
  music2.setReviewRate(9.1);

  aName = {"Robert", "Wise"};
  VideoProduct movie1("Sound of Music", 22.00, aName, 1965, 175);
  movie1.setFilmRate(FilmRateType::G);
  movie1.setReviewRate(9.2);

  aName = {"Ernest", "Hemmingway"};
  EBook book1("The old Man and the Sea", 8.30, aName, 127);
  book1.setReviewRate(9.5);

  aName = {"George", "Lucas"};
  VideoProduct movie2("Star Wars", 22.00, aName, 1977, 120);
  movie2.setFilmRate(FilmRateType::PG);
  movie2.setReviewRate(8.5);

  aName = {"Taylor", "Swift"};
  AudioProduct music3("Lavender Haze", 13.65, aName);
  music3.setGenre(GenreType::Pop);
  music3.setReviewRate(3.4);

  aName = {"Donna", "Tart"};
  PaperBook book2("The Secret History", 17.00, aName, 54);
  book2.setReviewRate(10.0);

  cout << "Testing Cart" << endl;
  cout << "============" << endl;
  cout << endl;
  // create a cart object
  NameType owner = {"John", "Smith"};
  Cart myCart(owner);

  cout.setf(std::ios::showpoint);
  cout.setf(std::ios::fixed);
  cout.precision(2);
  // add 7 items into the cart
  myCart.addItem(&music1);
  myCart.addItem(&music2);
  myCart.addItem(&music3);
  myCart.addItem(&movie1);
  myCart.addItem(&movie2);
  myCart.addItem(&book1);
  myCart.addItem(&book2);
  // display cart
  myCart.displayCart();
}
