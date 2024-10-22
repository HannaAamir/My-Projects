#include <iostream>
using namespace std;

int main() {
  // declaring user input variables
  double hourly_rate, retirement_contribution;
  int hours_worked;

  cout << "Enter hourly rate: ";
  cin >> hourly_rate;
  cout << "Enter the number of hours worked in this week: ";
  cin >> hours_worked;
  cout << "Enter the retirement deduction for this week: ";
  cin >> retirement_contribution;

  // declaring variables to be used in computing the paycheck
  double overtime_rate;
  double regular_pay;
  double weekly_gross_pay;
  double overtime_pay;
  int overtime_hours;

  // calculating overtime and/or regular pay to attain weekly gross pay
  if (hours_worked > 40) {
    overtime_rate = (1.5 * hourly_rate);
    overtime_hours = (hours_worked - 40);
    regular_pay = (hourly_rate * 40);
    overtime_pay = (overtime_hours * overtime_rate);
    weekly_gross_pay = (regular_pay + overtime_pay);
  } else {
    weekly_gross_pay = (hours_worked * hourly_rate);
  }

  // defining and calculating annual gross pay
  double annual_gross_pay = (weekly_gross_pay * 52);

  // declaring and defining social security withdrawal variables
  const double SOCIAL = 0.062; // social security witholding tax percentage
  double social_witholding;

  // calculating social security withdrawal per week
  if (annual_gross_pay > 137700) {
    social_witholding = ((SOCIAL * 137700) / 52);
  } else {
    social_witholding = ((SOCIAL * annual_gross_pay) / 52);
  }

  // declaring, defining and calculating medicare withdrawal per week
  const double MEDICARE = 0.0145; // medicare withdrawal tax percentage
  double medicare_witholding = ((MEDICARE * annual_gross_pay) / 52);

  // declaring federal tax variable
  double federal_tax;

  // declaring and defining constant variables for annual income tax brackets
  const double BRACKET_1 = 9875.0;
  const double BRACKET_2_AND_3 = 54125.0;

  // calculating weekly federal tax payment using annual income tax brackets
  if (annual_gross_pay <= BRACKET_1) {
    federal_tax = ((0.1 * annual_gross_pay) / 52);
  } else if (annual_gross_pay > BRACKET_1 &&
             annual_gross_pay <= BRACKET_2_AND_3) {
    federal_tax = (987 + (0.12 * (annual_gross_pay - 9875))) / 52;
  } else if (annual_gross_pay > BRACKET_2_AND_3) {
    federal_tax = (6297 + (0.22 * (annual_gross_pay - 54125))) / 52;
  }

  // declaring and defining Colorado State tax variable
  double co_state_tax = ((annual_gross_pay * 0.0455) / 52);

  // declaring, defining and calculating weekly deducation total and weekly net
  // pay
  double deduction_total = social_witholding + medicare_witholding +
                           federal_tax + co_state_tax + retirement_contribution;
  double net_pay = weekly_gross_pay - deduction_total;

  // formatting all output to be fixed to two decimal places
  cout.setf(std::ios::fixed); // decimal point and trailing zeros
  cout.setf(std::ios::showpoint);
  cout.precision(2);

  // formatting all output layout to resemble paycheck summary
  cout << "\nThis weeks's wage details:\n";
  cout << "=========================== \n";
  cout << "Gross pay: $" << weekly_gross_pay << "  (Overtime pay: $"
       << overtime_pay << ")\n";
  cout << "\nTaxes and deductions:\n";
  cout << "====================== \n";
  cout << "Social security withdrawal: $" << social_witholding << endl;
  cout << "Medicare withdrawal: $" << medicare_witholding << endl;
  cout << "Federal tax: $" << federal_tax << endl;
  cout << "Colorado state tax: $" << co_state_tax << endl;
  cout << "Retirement contribution: $" << retirement_contribution << endl;
  cout << "\n";
  cout << "--------------------------------- \n";
  cout << "Deduction total: $" << deduction_total << endl;
  cout << "--------------------------------- \n";
  cout << "Net pay: $" << net_pay << endl;

  return 0;
}
