# Hanna Aamir
# Student Number: 251100204

# This file contains three different functions. Each function evaluates the code entered by the user and qualifies it as a certain type (eg. Basic).

def basic_code(user_input):
    """ Returns True or False to indicate if the code entered by the user is Basic.
    Each digit of the code is evaluated using a list. To qualify as a Basic code, the check digit/last digit must be
    equivalent to the remainder of the sum, of all digits, being divided by 10. """

    code = [int(i) for i in user_input]  # each digit in the string entered by the user is converted to an integer and passed as an element of a
    # list containing the entire code
    check_digit = (sum(code[0:-1])) % 10  # calculating the sum of all digits in the code, and then performing modulo operation of 10
    if check_digit == code[-1]:  # evaluates if the code is basic
        return True
    else:
        return False


def positional_code(user_input):
    """ Returns True or False to indicate if the code entered by the user is Positional.
    Each digit of the code is evaluated using a list. To qualify as a Position code, the check digit/last digit must be
    equivalent to the remainder of the sum, of multiplying each digit by its position in the code, being divided by 10."""

    code = [int(i) for i in user_input]  # each digit in the string entered by the user is converted to an integer and passed as an element of a
    # list containing the entire code
    sum_of_digits = 0  # sum of all digits which are multiplied by their position in the code is initialized as 0 outside of the loop to ensure accuracy
    i = 1  # position of the first digit in the code is initialized as 1, outside of the for loop to ensure accuracy
    for num in code[0:-1]:  # a for loop is used to iterate over every digit in the code except for the last one/check_digit
        x = num * i  # each digit in the code is multiplied by its position and is assigned to a new variable 'x' for better readability
        sum_of_digits += x  # the sum of the digits is expressed to constantly include the product of each digit times its position
        i += 1  # position of each digit increases by 1 to correspond with the next digit being iterated in the list
    check_digit = sum_of_digits % 10  # the essential qualification for positional code
    if check_digit == code[-1]:  # evaluates if the code is positional
        return True
    else:
        return False


def universal_product_code(user_input):
    """ Returns True or False to indicate if the code entered by the user is UPC. Each digit of the code is evaluated using a list.
    To qualify as a UPC code, the check digit must be the result of three sequential processes; first, the sum of multiplying each odd position digit by 3 and each even position digit by 1;
    secondly, the resulting remainder of this sum being divided by 10; lastly, if the resulting remainder is between 1 and 9, it is subtracted from 10 and this becomes the check digit,
    and if the resulting remainder is 0, this becomes the check digit. If the last digit of the code is equivalent to the check digit, the code qualifies as UPC."""

    code = [int(i) for i in user_input]  # each digit in the string entered by the user is converted to an integer and passed as an element of a
    # list containing the entire code
    sum_list = []  # the sum of the digits is initialized as a list to easily enable further mathematical evaluations
    for x, y in enumerate(code[:-1]):  # a for loop is used to iterate over every digit and its corresponding position in the code, except the last one
        sum = 0  # the sum is initialized (apart from the above list of sums) to 0, inside the for loop, to account for the differing sums of even vs. odd positional digits
        if (x + 1) % 2 == 1:  # evaluates if the position is odd, (x + 1) accounts for the actual position of each digit rather than accounting for the position as an index.
            #  for example, adding 1 to x allows the position of the first digit to equal one instead of zero (ie. its list index)
            m = y * 3  # the digit corresponding to the odd position is multiplied by 3 and assigned to a new variable m for better readability
            sum += + m  # the sum evaluates with each iteration of this if branch to include every odd position digit
        else:  # executes for an even position digit
            sum += + y  # the sum evolves with each iteration of this else branch to include ever even position digit
        sum_list.append(sum) # the sum of each iteration of the for loop is added to the previous list of sums
    sum_total = 0  # a new variable is assigned for the total of all the sums and is set to 0 before the corresponding for loop below for accuracy
    for i in sum_list:  # this for loop iterates over every sum in the list of sums to provide the total of all the sums
        sum_total += i   # the total of the sums evolves with each iteration of this for loop to ensure every sum is accounted for
    sum = sum_total  # finally, the sum of multiplying each odd position digit by 3 and each even position digit by 1 is assigned to a new, single variable (ie. sum)
    check_digit = sum % 10  # the remainder of the sum divided by 10 is the first half of the formulation of the check_digit
    if 1 <= check_digit <= 9:  # if the check digit is between 1 and 9, then it is subtracted from 10 and that is the final version of the check digit
        last_digit = 10 - check_digit
    else:  # else, the check digit is 0
        last_digit = 0

    if last_digit == code[-1]:  # if the check digit is equivalent to the last digit of the code entered by the user, then the code qualifies as a UPC code
        return True
    else:
        return False
