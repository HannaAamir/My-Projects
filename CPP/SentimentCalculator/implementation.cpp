#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;
// declaring constant variable for the max number of entries in SocialSentScore(SSS) table (6279)
const int MAX_NUM_ENTRIES = 6279;
//a global table of SSS which is an array of "social sentiment scores" struct declared above
social_sentiment_scores SSS_table [MAX_NUM_ENTRIES];

void buildSocialSentScoresTable(string tableFileName) {
    // Declare local variables as needed
    ifstream instream;
    // open the social sentiment file stream
    instream.open("socialsent.csv");
    // check if the file opened successfully.  Exit the program if failed
    if (instream.fail())
    {
    cout << "File open failed.\n";
    exit(1);
    }
    // read social sensitive words and scores line by line from the specified
    // file. build the global soscial sensitive table with the data.
    int i = 0;
    string line;
    while (getline(instream, line)) {
        // use std::string.find() function to find the position index of ','
        size_t position_of_comma;
        position_of_comma = line.find(",");
        
        
        
            
        // use std::string.substr() function to extract 'word' substring
        
      
        // starting from the beginning of the line till ','

        // then set it to the word field of the i-th entry in the SSS table
        SSS_table[i].word = line.substr(0, position_of_comma);

        // read the second token (score) in the line and set it to the score
    
        // field of the i-th entry in the SSS table
        SSS_table[i].score = std::stof(line.substr(position_of_comma + 1.0));

        i++; // go to the next word
    }
    instream.close();
}

double computeSSS(string reviewFileName) {
    // open the specified review file
    ifstream instream(reviewFileName);
    double totalScore = 0.0;
    // handling open() errors
    if (instream.fail())
    {
        cout << "File open failed.\n";
        exit(1);
    }
    
    string word;
    // read the words in  the review file line by line
    while (instream >> word) {
        // trim non-alphanumeric characters in the word
        char nonAlphaNum[] = "{}[]()-.,!?\"\'";
        for (int i = 0; i < strlen(nonAlphaNum); i++) {
            // include <algorithm> to use std::remove()
            word.erase(
              std::remove(word.begin(), word.end(), nonAlphaNum[i]),
              word.end());
        } // end of for
        
        // search if the word is in the table.  If so, add the score of the word
        // to the global variable
        
        for (int i=0; i< MAX_NUM_ENTRIES; i++) {
            if (SSS_table[i].word == word) {
                totalScore += SSS_table[i].score;
                cout << SSS_table[i].word << ": " << SSS_table[i].score << "," <<totalScore << endl;
            } // end of while
            
            // return the total score
            
        } // end of function
        
    }
    return totalScore;
}

double getStarRank(double finalScore) {
    double rank;
            if (finalScore < -5.0) {
                rank=1.0;
            } else if (finalScore >= -5.0 && finalScore < -1.0) {
                rank=2.0;
            } else if (finalScore >= -1.0 && finalScore < 1.0) {
                rank=3.0;
            } else if (finalScore >= 1.0 && finalScore < 5.0) {
                rank=4.0;
            } else {
                rank=5.0;
            }
    return rank;
        }

    