
//  Created by Hanna Aamir on 10/25/22.

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "functions.hpp"
using namespace std;




int main(int argc, char *argv[]) {
    cout << "[word: current_score, accumulated_score]" << endl;
    // define and initialize a 'double' variable (0.0) to store the total social
    // sentiment point for the words in the review file.
    double total_sentiment_score = 0.0;
    // define and initialize the sentiment data file to the file name (the
    // default file name: "socialsent.csv")
    string sentiment_file = "socialsent.csv";
    // invoke a function to build the social sentiment scores table
    buildSocialSentScoresTable(sentiment_file);
    // define a review file variable and initialize it with the default file
    // name (review.txt)
    string review_file = "review.txt";
    // in the code below, if the review file is provided at the command line,
    // use the specified one instead of the default one
    if (argc > 1) { // an optional review file is specified
        // assign(copy) argv[1] (a C-string) to the review file name variable.
        char tempFileName[35];
        strcpy(tempFileName, argv[1]);
        review_file = tempFileName;
    }

    // call one of the functions to compute a SSS for the specified review file
  //double computeSSS returns a sentiment score of a review based on the SocialSentScores table and the contents of the specified review file
    double total_score = computeSSS(review_file);

    // call one of the functions to convert the SSS to a star rank
  //double getStarRank function returns a star rank of the sentiment score of the specified review file (eg. 1 star, 2 stars etc.)
    double star_rank = getStarRank(total_sentiment_score);

    // display the result along with a star rank
    
    cout << endl << review_file << " Score: " << total_score << endl;
    cout << review_file << " Stars: " << star_rank << endl;
}





