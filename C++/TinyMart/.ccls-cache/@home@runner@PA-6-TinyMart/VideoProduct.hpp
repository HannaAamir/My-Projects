#ifndef VIDEOPRODUCT_HPP
#define VIDEOPRODUCT_HPP

#include "Product.hpp"
#include <iostream>
#include <string>

using namespace std;
//enum-type for film rating
enum FilmRateType {NotRated = 0, G, PG, PG_13, R, NC_17};
//string type to access enum-type film rating (particularly in display function)
const string FilmRateString[] = {"Not rated", "G", "PG", "PG 13", "R", "NC 17"};

class VideoProduct : public Product {

public:

    VideoProduct();//default constructor
    VideoProduct(string aProdName, double aPrice, NameType aDirectorName, int aReleaseYear, int aRunTime); //movie name, price, director, release year, run time
    //getters
    NameType getDirector() { return director; }
    FilmRateType getFilmRate() { return filmRate; }
    int getReleaseYear() { return releaseYear; }
    int getRunTime() { return runTime; }
    //setters
    void setDirector(NameType aName) { director = aName; }
    void setFilmRate(FilmRateType aRate) { filmRate = aRate; }
    void setReleaseYear(int aReleaseYear) { releaseYear = aReleaseYear; }
    void setRunTime(int aRunTime) { runTime = aRunTime; }
    
    bool isNewRelease(int theYear);
    /*Checks if the movie is equal to or newer than the specified year.*/
    //base-class functions - descriptions avalible in Product.hpp
    //functions are overrided to display information specific to video product
    virtual string getProdTypeStr() override;
    virtual void displayProdInfo() override;
    virtual void displayContentsInfo() override;

private:
    NameType director;
    FilmRateType filmRate;
    int releaseYear;
    int runTime;

};

#endif