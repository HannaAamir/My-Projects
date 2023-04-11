"""
Author: Hanna Aamir
Date: November 1, 2022
This program will perform the following tasks:
   1) It will ask user for three test score
   2) It will calculate the meand of the three test score
   3) It will convert the mean into a letter grade (See
      find_letter_grade function for the the mapping)
   4) It will display the mean score and letter grade
It will display an error message if the enterd score is non-numerical 
"""

def calculate_mean (score1, score2, score3):
    """
    Function Name: calculate_mean
    Description: Calculate mean of three test scores
    Parameter: score1 - Score for test 1
               score2 - Score for test 2
               score3 - Score for test 3
    Returns mean of the three test scores
    """
    mean = (score1 + score2 + score3) /3

    return mean
def find_letter_grade (mean):
    """
    Function Name: find_letter_grade
    Description: Convert the mean into letter grade as follows:
              Mean                     Letter Grade
              90 to 100                    A
              80 to 89                     B
              70 to 79                     C
              60 to 69                     D
               0 to 59                     F
    If the acore is above 100 or below 0 then it will return
    letter grade to be "undefined"
    Parameter: mean- mean of the test score
    Returns list of numbers
    """

    if mean > 100:
      letter_grade = 'Undefined'  
    elif mean >= 90:
        letter_grade = 'A'
    elif mean >= 80:
        letter_grade = 'B'
    elif mean >= 70:
        letter_grade = 'C'
    elif mean >= 60:
        letter_grade = 'D'
    elif mean >= 0:
        letter_grade = 'F'
    else:
        letter_grade = 'Undefined'

    return letter_grade
def main():
    """
    Function Name: main
    Description: Ask the user for three test score, use calculate_mean
                 function to calculate the mean, use find_letter_grade
                 function to conver mean into letter grade, and disply
                 mean and letter grade.
                 It uses try/except construct to catch any errors and
                 displays appropriate error messages
    Parameter: None
    Returns None
    """

    print ('This program will calculate the mean of three test grades and')
    print ('convert the mean into a letter grade')
    print ('=============================================================')

    # Use tr/except block to catch errors
    try:
        score1 = int (input ('Enter score 1: '))
        score2 = int (input ('Enter score 2: '))
        score3 = int (input ('Enter score 3: '))

        mean = calculate_mean (score1, score2, score3)

        letter_grade = find_letter_grade (mean)

        print ('Your mean score is {0:0.3f}'.format (mean))

        print ('Your letter grade is:', letter_grade)

    # If the input is a non-numerical string then display an error message
    except ValueError as err:
        print ('One of you score is non-numerical')
        print ('Please try again with correct scotes')
    # Catch unexpected errors
    except:
        print ('Unknown error')
