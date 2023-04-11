# Hanna Aamir
# Student Number: 251100204
# Registered with Accessible Education and got an extension from Prof Bauer till Friday, October 8 at 9 pm - therefore, please no late marks.

# This program calculates and displays the cost of electricity for any homeowner living in Ontario, using the user's input in the algorithms.
# This program evaluates the total consumption of electricity in kilowatt hours (kwh) during three different periods of usage; Off Peak
# (7pm-7am), Peak (7am-11am and 5pm-7pm), Mid-Peak (11am-5pm).
# Each period of usage has a different charge per kwh, which is coded below as constants.
# These constants for the price are coded outside the while loop so that if the price were to change, the constants could easily reflect the change by being edited
# - otherwise, if the prices were hardcoded into the loop, then you would have to change it for every loop condition which would be redundant/less efficient.

OffPeakPrice = 0.085
OnPeakPrice = 0.176
MidPeakPrice = 0.119

# The first user prompt is for the electricity consumed during the Off Peak period as this was the specified order as per the assignment instructions.

OffPeakConsumption = float(input("Enter kwh during Off Peak period:"))

# The prompt for user input for the electricity consumed during the Off Peak period is coded outside the while loop so that the program can halt if the user
# enters a value of 0.

while OffPeakConsumption != 0:
    OnPeakConsumption = float(input("Enter kwh during On Peak period:"))
    MidPeakConsumption = float(input("Enter kwh during Mid Peak period:"))
    senior = input("Is owner senior? (Y, y, N, n):")
    # All the other electricity consumption periods are coded in this specified order within the while loop, followed by the prompt for whether the homeowner
    # is a senior or not.
    # A formula for the total amount of electricity in kwh, is coded outside the the outer and inner loop below to avoid redundancy and ensure efficiency.
    totalConsumption = OffPeakConsumption + OnPeakConsumption + MidPeakConsumption
    # The outer loop is coded to evaluate the senior status of the homeowner, essentially a boolean value, to ensure readability and efficiency. A senior status results in the
    # Senior discount
    if senior == 'y' or senior == 'Y':
        if totalConsumption < 400:
            # The first branch of this inner loop evaluates if the Total Usage discount is applicable and calculates the consequent subtotal with the additional senior discount.
            subtotal = ((OffPeakConsumption * OffPeakPrice) + (OnPeakConsumption * OnPeakPrice) + (MidPeakConsumption * MidPeakPrice)) * 0.96
            subtotal *= 0.89
        elif OnPeakConsumption < 150:
            # The second elif-branch of this inner loop evaluates if the On Peak Discount is applicable, and calculates the consequent subtotal with the additional senior discount.
            # The elif branch in particular ensures that the On Peak Discount will only be applied if the Total Usage discount is not applied.
            subtotal = ((OffPeakConsumption * OffPeakPrice) + (OnPeakConsumption * OnPeakPrice * 0.95) + (MidPeakConsumption * MidPeakPrice))
            subtotal *= 0.89
        else:
            # The third and final else-branch of this inner loop only executes if the Total Usage and On Peak discounts were not applied, and it calculates the consequent subtotal
            # with the additional senior discount.
            subtotal = ((OffPeakConsumption * OffPeakPrice) + (OnPeakConsumption * OnPeakPrice) + (MidPeakConsumption * MidPeakPrice))
            subtotal *= 0.89
    # The second else-branch of the outer loop executes if there is no senior status of the homeowner - and consequently, no Senior Discount.
    else:
        if totalConsumption < 400:
            # The first branch of this inner loop evaluates if the Total Usage discount is applicable and calculates the consequent subtotal.
            subtotal = ((OffPeakConsumption * OffPeakPrice) + (OnPeakConsumption * OnPeakPrice) + (MidPeakConsumption * MidPeakPrice)) * 0.96
        elif OnPeakConsumption < 150:
            # The second elif-branch of this inner loop evaluates if the On Peak Discount is applicable, and calculates the consequent subtotal.
            # The elif branch in particular ensures that the On Peak discount will only be applied if the Total Usage discount is not applied.
            subtotal = ((OffPeakConsumption * OffPeakPrice) + (OnPeakConsumption * OnPeakPrice * 0.95) + (MidPeakConsumption * MidPeakPrice))
        else:
            # The third and final else-branch of this inner loop only executes if the Total Usage and On Peak discounts were not applied, and it calculates the consequent subtotal.
            subtotal = ((OffPeakConsumption * OffPeakPrice) + (OnPeakConsumption * OnPeakPrice) + (MidPeakConsumption * MidPeakPrice))
    # A formula for the total cost of electricity is coded outside of the outer and inner if-else loops, once, to ensure readability and efficiency.
    total = subtotal * 1.13
    # The output of the program describing the cost of electricity for any homeowner in Ontario, is coded below using the python formatting operators which print a value to two decimal places.
    print("Electricity cost: ${:.2f}".format(total))
    print()
    # The following code then prompts the user for the amount of electricity consumed in kwh during the Off Peak period, within the while loop, so that the program can continue to run and only
    # come to a halt if the user enters a value of 0.
    OffPeakConsumption = float(input("Enter kwh during Off Peak period:"))
