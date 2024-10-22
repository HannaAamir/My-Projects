
#include <iostream>
using namespace std;

// Hanna Aamir
// Student ID: 110692143
// This is a basic "Hello World!" program and in addition, prompts the user for the weather and date and suggests an
// activity.
int main()
{
    cout << "Hello reader.\n"
         << "Welcome to C++.\n";

    string name;
    char weather;
    int date;
    bool weekday = true;

    cout << "Please enter your name: ";
    cin >> name;
    cout << "Please enter today's weather [S]unny, [R]ainy, [W]indy: ";
    cin >> weather;
    cout << "Please enter today's day [Sunday:0 .. Saturday:6]: ";
    cin >> date;

    // depending on the integer entered by the user, the date can be categorized as either a weekday or weekend
    if (date == 0 || date == 6){
        weekday = false;
    }

    cout << "Hello " << name << "!\n";
    if (weekday) {
        if (weather == 'S'){
            cout << "You may play tennis.\n";
        } else if (weather == 'R'){
            cout << "You may stay home.\n";
        } else {
            cout << "You may go kiting.\n";
        }
    } else{
        if (weather == 'S'){
            cout << "You may go hiking.\n";
        } else if (weather == 'R') {
            cout << "You may go bowling.\n";
        } else {
            cout << "You may go hand-gliding.\n";
        }
    }

    return 0;
}

