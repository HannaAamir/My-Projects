"""
Hanna Aamir
November 1, 2022
This program calculates the discount for a user who purchases packages from a software company.
"""


def discountPercentage(quantity):
    if quantity <= 10:
        discount = 0
    elif quantity <= 19:
        discount = 2
    elif quantity <= 49:
        discount = 30
    elif quantity <= 99:
        discount = 40
    elif quantity >= 100:
        discount = 50

    return discount

def main():

    try:

        print("This program will calculate the discount on a purchase based on an entered quantity")
        quantity = int(input("Please enter the quantity to purchase: "))
        if quantity >=0:
            discount = discountPercentage(quantity)
            amount = quantity*99
            if discount > 0:
                discount_amount = amount * (discount/100)
            else:
                discount_amount = 0
            total = amount - discount_amount

            print("Your disocunt percentage is {0:0.2f}%\nYour discount amount is ${1:0.2f}\nand your total is ${2:0.2f}".format(discount, discount_amount, total))

        else:
            print("Invalid package quantity")

    except:
        print("Unknown error")
