# Hanna Aamir
# Student Number: 251100204
# Extended deadline via Accessible Education is October 26th

# This program verifies different types of identification (ID) numbers/codes and their corresponding check digits using functions that are imported from a separate file (ie. code_check)
# It specifically executes to identify three types of codes - basic, positional and universal product code (UPC). For all the codes which are entered by the user, the program executes a summary at the end
# and whichever code could not be identified as one of the three types, the program will indicate that it belongs to no category (ie. "None"). Some ID numbers could be more than one type or could be none.


# Lists meant to store each each user-entered ID number are initialized before the while loop to ensure proper allocation for each ID number.
basic = []
position = []
upc = []
none = []

# The functions from the code_check file are imported to evaluate and identify each user-entered ID number.
from code_check import *

# THe program prompts the user to enter an ID number as per assignment requirements. The strip() function is used to identify the ID number exclusively for the digits that it contains
# - by removing leading and trailing spaces.
user_input = input("Please enter code (digits only) (enter 0 to quit) ").strip()

# This while loop is used to evaluate what type of ID number the user has entered. It is conditional to the user entering '0', so that the program can be terminated.
while user_input != '0':
    # Multiple if branches are coded to evaluate the type of ID number entered. The first three if branches each call a specific function to identify the type of ID number (eg. basic_code(user_input)).
    # If the function for a type of ID number returns True, then that number is consequently added to the list that it identifies with (eg. basic = []), through the statement "basic.append(user_input)" .
    if basic_code(user_input) is True:
        basic.append(user_input)
        print("‐‐ code: {} valid Basic code.".format(user_input))
    if positional_code(user_input) is True:
        position.append(user_input)
        print("‐‐ code: {} valid Position code.".format(user_input))
    if universal_product_code(user_input) is True:
        upc.append(user_input)
        print("‐‐ code: {} valid UPC code.".format(user_input))
    # The last if branch of this while loop evaluates if the ID number does not belong to any of the three types by calling all three functions used to identify.
    # If none of the functions return True, then it is evident that the ID number is not any one of the three types, and it is added to the designated list of codes as such (ie. None = []).
    if basic_code(user_input) is not True and positional_code(user_input) is not True and universal_product_code(user_input) is not True:
        none.append(user_input)
        print("‐‐ code: {} not Basic, Position or UPC code.".format(user_input))

    # The algorithm prompts the user for input again within the while loop so that if the user enters '0', the program can terminate as per the condition of the while loop.
    user_input = input("Please enter code (digits only) (enter 0 to quit) ").strip()


# Since every user-entered string was converted to an integer list within the functions used to identify the type of number, all the codes, in each list, must be converted back to strings
# to give the desired output for the Summary as per assignment requirements (eg. convert_basic).
convert_basic = [str(int) for int in basic]
# Once the codes in each list have been converted to strings, a new variable is initiated to extract each code from a certain list and be joined with a comma (eg. string_basic). This enables
# each category of code to be presented in the Summary without being in a python list format - it enhances clarity of output for the user.
string_basic = ", ".join(convert_basic)
convert_position = [str(int) for int in position]
string_position = ", ".join(convert_position)
convert_upc = [str(int) for int in upc]
string_upc = ", ".join(convert_upc)
convert_none = [str(int) for int in none]
string_none = ", ".join(convert_none)

# Each if branch below is used to determine if any category of codes is empty by checking for the length of the category's corresponding list (eg. convert_upc). If the length of the list is 0,
# then it is evident that none of the codes entered by the user belong to that specfic category. Consequently, that category is declared to be empty (eg. string_upc = "None").
if len(convert_basic) == 0:
    string_basic = "None"
if len(convert_position) == 0:
    string_position = "None"
if len(convert_upc) == 0:
    string_upc = "None"
if len(convert_none) == 0:
    string_none = "None"

# The summary statement contains a newline to match the desired output.
print("\nSummary")
# Each ID number entered by the user is presented with the category it belongs to.
print("Basic : {}".format(string_basic))
print("Position : {}".format(string_position))
print("UPC : {}".format(string_upc))
print("None : {}".format(string_none))

