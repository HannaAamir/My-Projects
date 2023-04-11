# Hanna Aamir
# Student Number: 251100204
# This is the main program which interacts with the user, to perform sentimental analysis of Twitter data belonging to four different regions/ timezones
# (ie. Eastern, Central, Pacific, Mountain) - based on the files entered by the user

# all the functions from "sentiment_analysis.py" module are imported for computation of the sentiment analysis of the twitter data
from sentiment_analysis import *

# the following two lines prompt the user to enter the name of the file containing the tweets, and then the name of the file containing the keywords
file_tweets = input("Enter name of file containing tweets:\n")
file_keywords = input("Enter name of file containing keywords:\n")

# a variable is assigned, calling the "compute_tweets()" function, for reference
# the "compute_tweets()" function returns a list with four tuples - each tuple contains the sentimental
# analysis (ie. happiness score, number of keyword tweets and total number of tweets) for one of the four timezones.
data = compute_tweets(file_tweets, file_keywords)

# the remainder of this file prints one of the four region with it's sentimental analysis of designated tweets in a comprehensive manner
print("Eastern Region:")
print("Happiness Score: {:.2f}, {} keyword tweets, {} tweets in total for the region".format(data[0][0], data[0][1], data[0][2]))
print("Central Region:")
print("Happiness Score: {:.2f}, {} keyword tweets, {} tweets in total for the region".format(data[1][0], data[1][1], data[1][2]))
print("Mountain Region:")
print("Happiness Score: {:.2f}, {} keyword tweets, {} tweets in total for the region".format(data[2][0], data[2][1], data[2][2]))
print("Eastern Region:")
print("Happiness Score: {:.2f}, {} keyword tweets, {} tweets in total for the region".format(data[3][0], data[3][1], data[3][2]))

