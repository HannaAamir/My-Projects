#ifndef header
#define header
#include <iostream>
using namespace std;

//declaring "social sentiment scores" data type (struct).
// The structure consists of two fields [word, score] where
// word is a string type and score is double type.
// Note that this data type is a global type
struct social_sentiment_scores {
  string word; //sentiment word 
  double score; //score of sentiment word
};

void buildSocialSentScoresTable(string tableFileName);
/*
 * This function opens and reads data from the specified 'csv' file.
 * The file contains the list of scores, one per line.
 * The function builds the "global" SocualSentimentScores (SSS) table of
 * "social sentiment scores" struct data structure
 * using the sentiment of each word data read in line by line.
 *
 * @ param tableFileName the file name containing the social sentiment scores
 * data
 */
double computeSSS(string reviewFileName);
/*
 * This function opens and reads the review text from the specified review file.
 * Then, it looks up the SSS table to find the sentiment score of each word
 * in the file if the word exists in the SSS table.
 * The scores are cumulated to count the final score of all the words in the
 * review file.
 */
double getStarRank(double finalScore);
/* This function returns a star rank from the specified final SS score.
*/

#endif