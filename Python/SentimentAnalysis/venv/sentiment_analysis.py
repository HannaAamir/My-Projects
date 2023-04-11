# Hanna Aamir
# Student Number: 251100204
# This module contains different functions to ultimately perform sentimental analysis on Twitter Data
# The Twitter data spans the continental United States - the objective is to determine which timezone/region is the "happiest"


# Python's built in punctuation tuple is imported to aid in removing punctuation else-where
from string import punctuation


def compute_tweets(file_tweets, file_keywords):
    """ Returns a list with four tuples - each tuple contains the sentimental
    analysis (ie. happiness score, number of keyword tweets and total number of tweets) for one of the four timezones."""

    # a list of keywords is initialized to be referenced later for determining the happiness score
    keywords_list = []
    # a list of tweets for each of the regions is initialized to allocate each tweet to its respective regions for analysis
    eastern_tweets = []
    central_tweets = []
    mountain_tweets = []
    pacific_tweets = []

    # using a try-except loop to identify and generate an exception for a FileNotFoundError and consequently return an empty list
    try:
        # files containing the keywords and tweets are assigned variables for future reference and opened, to read, while avoiding encoding errors
        tweets_file = open(file_tweets, "r", encoding="utf-8", errors='ignore')
        keywords_file = open(file_keywords, "r", encoding='utf-8', errors='ignore')

        # for loop iterating over every line in the keywords file splits each keyword from its score and stores them in a list for computation
        for line in keywords_file:
            keywords_list.append(line.strip().split(","))

        # for loop to iterate over every tweet in the tweets file to essentially determine it's region, by formatting it into an iterable list, using the functions "format_tweet()"
        # and "determine_region()"
        for tweet in tweets_file:
            tweet = format_tweet(tweet)
            region = determine_region(tweet)
            # if the "determine_region()" function returns a location for a tweet, that tweet is stored in the appropriate list
            if region == "Eastern":
                eastern_tweets.append(tweet)
            elif region == "Central":
                central_tweets.append(tweet)
            elif region == "Mountain":
                mountain_tweets.append(tweet)
            elif region == "Pacific":
                pacific_tweets.append(tweet)

        # a variable is assigned for each of the timezones, which calls a function (ie. "happiness_score_per_region()"), to determine the happiness_score for that timezone
        eastern = happiness_score_per_region(file_keywords, eastern_tweets)
        central = happiness_score_per_region(file_keywords, central_tweets)
        mountain = happiness_score_per_region(file_keywords, mountain_tweets)
        pacific = happiness_score_per_region(file_keywords, pacific_tweets)

        # the files opened, are closed to reduce the risk of being unwarrantedly modified or read
        tweets_file.close()
        keywords_file.close()
        # the list containing the keywords and their designated scores is cleared to re-use the same list object for new data
        keywords_list.clear()

        # ultimately, all the data is computed to return the happiness score, number of keyword tweets and number of tweets in total for each region in the form of a list
        return [eastern, central, mountain, pacific]

    # if the file containing the tweets and/or keywords is not found, this except loop generates an exception and returns an empty list
    except IOError or FileNotFoundError:
        print("File cannot be found.")
        return []


def format_tweet(tweet):
    """Returns a single tweet after it has been formatted into an iterable list, with the latitude and longitude being converted into floats, and each of the remaining
    words being stripped of punctuation in the beginning and end, and converted to lowercase."""

    # once the tweet is split into an iterable list, it is assigned a new variable to further compute
    formatted_tweet = tweet.split()

    # since the latitude and longitude are only the first two indices of each tweet, this for loop uses a certain range to access those first two indices and strip them of the square brackets for computation
    for i in range(0, 2):
        formatted_tweet[i] = formatted_tweet[i].strip("[],")

    # the latitude and longitude are converted to floats for computation
    formatted_tweet[0] = float(formatted_tweet[0])
    formatted_tweet[1] = float(formatted_tweet[1])

    # the part of the iterable tweet-list containing words begins at the fifth index, therefore the for loop's uses this range to to convert all the words in the tweet into lowercase and strip, only the beginning
    # and end of, each word of punctuation
    for i in range(5, len(formatted_tweet)):
        formatted_tweet[i] = formatted_tweet[i].lower().strip(punctuation)

    # the function returns the tweet completely, appropriately formatted
    return formatted_tweet


def happiness_score_per_tweet(file_keywords, tweet):

    """Returns the happiness score of each tweet based on the file of keywords provided.
    THe happiness score is simply the sum of the “sentiment values” for keywords found in the tweet divided by the number of keywords found in the tweet."""

    # all the variables are initialized for further computation
    happiness_score = 0
    keyword_count = 0
    keywords_list = []
    # the file containing the keywords is assigned a variable for future reference and opened, to read, while avoiding encoding errors
    kwf = open(file_keywords, "r", encoding='utf-8', errors='ignore')
    # for loop iterating over every line in the keywords file splits each keyword from its score and stores them in a list for computation
    for line in kwf:
        keywords_list.append(line.strip().split(","))

    # two nested for loops to iterate over the tweet and list of keywords and check if a keyword is present in the tweet
    for i in range(len(tweet)):
        for j in range(len(keywords_list)):
            # nested if-branch executes if there is a keyword in the tweet to compute the happiness score and number of tweets with keywords
            if keywords_list[j][0] == tweet[i]:
                happiness_score += int(keywords_list[j][1])
                keyword_count += 1
    # to avoid a division-by-zero error, the if-branch executes if the number of tweets is not equal to 0 and returns the happiness_score, else it returns zer0
    if keyword_count != 0:
        return happiness_score / keyword_count
    else:
        return 0


def determine_region(tweet):

    """Returns the region of a single tweet using the defining latitude and longitude coordinates of each region."""

    # since the latitude coordinates across each region are consistent, there are only two variables representing the constants for the bottom and top latitude
    TOP_LATITUDE = float(49.189787)
    BOTTOM_LATITUDE = float(24.660845)
    # certain longitude coordinates are coded as constant floats to identify the regions in conjunction with the latitude coordinates
    P2_LONGITUDE = float(-67.444574)
    P4_LONGITUDE = float(-87.518395)
    P6_LONGITUDE = float(-101.998892)
    P8_LONGITUDE = float(-115.236428)
    P10_LONGITUDE = float(-125.242264)

    # outer if-branch used to check if the tweet is even within the latitude containing any of the regions - this enables the program to immediately decipher if the tweet does not
    # belong to any of the regions
    if BOTTOM_LATITUDE <= float(tweet[0]) <= TOP_LATITUDE:
        # inner nested if-branches to allocate the tweet to one of the four regions by determining if its longitude coordinates are within the range of a certain region
        if P4_LONGITUDE <= float(tweet[1]) <= P2_LONGITUDE:
            return "Eastern"
        elif P6_LONGITUDE <= float(tweet[1]) <= P4_LONGITUDE:
            return "Central"
        elif P8_LONGITUDE <= float(tweet[1]) <= P6_LONGITUDE:
            return "Mountain"
        elif P10_LONGITUDE <= float(tweet[1]) <= P8_LONGITUDE:
            return "Pacific"


def happiness_score_per_region(keyword_list, region_tweets):

    """Returns a tuple of the sentimental analysis of tweets per region which consists of the happiness score, the number of tweets containing keywords
     and the number of tweets in total in the region."""

    # variables for the number of keyword tweets, total number of tweets and the total happiness score are initialized
    count_of_keyword_tweets = 0
    # since region_tweets is a list, the amount of tweets in total is the length of the list
    count_of_tweets = len(region_tweets)
    total_score = 0

    # for loop iterates over ever single tweet and calls the "happiness_score_per_tweet()" function
    for i in range(count_of_tweets):
        score_per_tweet = happiness_score_per_tweet(keyword_list, region_tweets[i])
        # if the happiness score for a tweet is not equal to 0, then the number of keyword tweets and total happiness score increases
        if score_per_tweet != 0:
            count_of_keyword_tweets += 1
            total_score += score_per_tweet
    # to avoid a division-by-zero error, the if-branch only executes if the number of keyword tweets is not equal to zero
    if count_of_keyword_tweets != 0:
        # consequently, a tuple containing the sentimental analysis of all the tweets in region are returned
        return total_score/count_of_keyword_tweets, count_of_keyword_tweets, count_of_tweets
    else:
        return 0, 0, count_of_tweets
