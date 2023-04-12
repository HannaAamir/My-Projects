#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

// constant size definition for constant distance table
const int CITY_SIZE = 15;

// cities are stored as enum value
enum CityType {
  INVALID = -1,
  ATLANTA,
  BOSTON,
  CHICAGO,
  DALLAS,
  DENVER,
  HOUSTON,
  LOS_ANGELES,
  MEMPHIS,
  MIAMI,
  NEW_YORK,
  PHILADELPHIA,
  PHOENIX,
  SAN_FRANCISCO,
  SEATTLE,
  WASHINGTON_DC
};

// constant distance table intialization
const int DistanceTable[CITY_SIZE][CITY_SIZE] = {
    {0, 1505, 944, 1157, 1945, 1126, 3108, 541, 973, 1200, 1070, 2555, 3434,
     3503, 871},
    {1505, 0, 1367, 2491, 2839, 2578, 4166, 1824, 2022, 306, 435, 3691, 4330,
     3997, 634},
    {944, 1366, 0, 1290, 1474, 1510, 2444, 773, 1912, 1145, 1069, 2332, 2981,
     2787, 956},
    {1157, 2491, 1290, 0, 1064, 362, 1990, 675, 1785, 2204, 2086, 1422, 2380,
     2701, 1900},
    {1945, 2838, 1474, 1064, 0, 1412, 1335, 1411, 2773, 2617, 2532, 942, 1524,
     1640, 2395},
    {1127, 2579, 1511, 362, 1412, 0, 2205, 778, 1544, 2279, 2154, 1631, 2641,
     3038, 1958},
    {3108, 4166, 2800, 1990, 1335, 2205, 0, 2573, 3755, 3933, 3918, 574, 559,
     1544, 3689},
    {541, 1824, 773, 675, 1411, 778, 2573, 0, 1404, 1533, 1413, 2026, 2893,
     2997, 1226},
    {973, 2022, 1912, 1785, 2773, 1544, 3755, 1404, 0, 1756, 1643, 3182, 4166,
     4392, 1487},
    {1200, 306, 1145, 2204, 2617, 2279, 3933, 1533, 1756, 0, 130, 3441, 4126,
     3863, 328},
    {1070, 435, 1069, 2086, 2532, 2154, 3918, 1413, 1643, 130, 0, 3342, 4047,
     3816, 199},
    {2555, 3691, 2332, 1422, 942, 1631, 574, 2026, 3182, 3441, 3342, 0, 1050,
     1792, 3180},
    {3434, 4330, 2981, 2380, 1524, 2641, 559, 2893, 4166, 4126, 4047, 1050, 0,
     1092, 3916},
    {3503, 3997, 2787, 2701, 1640, 3038, 1544, 2997, 4392, 3863, 3816, 1792,
     1092, 0, 3734},
    {871, 634, 956, 1900, 2395, 1958, 3689, 1226, 1487, 328, 199, 3180, 3916,
     3734, 0},
};

CityType cityStringToEnum(string city_string);
// Precondiiton: city_string is a string entered by the user.
// Postcondition: returns the enum value identifying a city and checks if the
// city input is valid.
void buildDistanceTable(int distance_array[][CITY_SIZE], int city_size);
// Precondition: a 2D integer array to store city distances and an integer
// paramater to determine how many cities will be stored in the array
// Postcondition: a 2D integer array to store city distances is computed using
// the global constant distance "table".
CityType distanceIntToEnum(int city_index);
// Precondition: an integer index of the 2D distance array is passed as a
// parameter Postcondition: the enum value to idenitfy the city represented by
// the index of the 2D distance array is returned. If no real city is identified
// by the index, then an "invalid" city is returned.
string enumToString(CityType enum_city);
// Precondition: enum_city must be of CityType enum value or else the function
// will return an "invalid city" Postcondition: the function returns a string
// which identifies the city enum value
double getTripCost(int distance_array[][CITY_SIZE], CityType departure_enum,
                   CityType arrival_enum);
// Precondition: the departure_enum is an enum value that must be from the
// CityType enum. departure_enum and arrival_enum are
// converted to strings by calling enumToString() and then the resulting strings
// are converted back to enum values using cityStringToEnum, to check if they
// are valid cities (essentially perform error handling) prompts the user to
// enter the gas price and mileage. Postcondition: computes the total cost and
// returns it as a double.
double getAverageDistance(int distance_array[][CITY_SIZE], CityType city);
// Precondition: city must be an enum value of CityType
// and the distance array must be a 2D array. city is converted to a string by
// calling enumToString() and then the resulting string is converted back to an
// enum value using cityStringToEnum, to check if it is valid city (essentially
// perform error handling)
// Postcondition: computes and returns the average distance between the
// specified city and all other cities from the specified city as a double.

string getClosestCity(int distance_array[][CITY_SIZE], CityType departure);
// Precondition: departure must be an enum value of CityType and the distance
// array must be 2D Postcondition: returns a string describing the closest city
// to the departure city, and the distance in miles

string getFarthestCity(int distance_array[][CITY_SIZE], CityType departure);
// Precondition: departure must be an enum value of CityType and the distance
// array must be a 2D array. Postcondition: returns a string describing the
// farthest city to the departure city, and the distance in mile
string getFarthestTwoCities(int distance_array[][CITY_SIZE]);
// Precondition: the distance array must be 2D
// Postcondition: returns a string concatening the city names of the two
// farthest cities in the distance array and the distance between them
string getClosestTwoCities(int distance_array[][CITY_SIZE]);
// Precondition: the distance array must be 2D
// Postcondition: returns a string concatening the city names of the two
// farthest cities in the distance array and the distance between them

int main() {

  // all variables to be used within the main function and/or as other function
  // paramaters are declared
  string departure_city;
  string arrival_city;
  int distance_array[CITY_SIZE][CITY_SIZE];
  CityType departure_enum;
  CityType arrival_enum;
  string departure;
  string city;
  float total_cost;
  int distance = 0;
  double distance_average;

  string closestCityStr = "";
  string farthestCityStr = "";
  string closestTwoCitiesStr = "";
  string farthestTwoCitiesStr = "";

  // city-distance array is created through this function
  buildDistanceTable(distance_array, CITY_SIZE);

  // two do-while loops are used to continuously prompt the user to enter a
  // departure/arrival city if it is invalid
  do {
    cout << "Enter the departing city: " << endl;
    getline(cin, departure_city);
    departure_enum = cityStringToEnum(departure_city);
  } while (departure_enum == CityType ::INVALID);

  do {
    cout << "Enter the arrival city: " << endl;
    getline(cin, arrival_city);
    arrival_enum = cityStringToEnum(arrival_city);
  } while (arrival_enum == CityType ::INVALID);

  distance = distance_array[departure_enum][arrival_enum];
  // the total cost is computed using the getTripCost function
  total_cost = getTripCost(distance_array, departure_enum, arrival_enum);
  // the average distance from the departure city to all other cities is
  // computed using getAverageDistance function
  distance_average = getAverageDistance(distance_array, departure_enum);
  closestCityStr = getClosestCity(distance_array, departure_enum);
  farthestCityStr = getFarthestCity(distance_array, departure_enum);
  closestTwoCitiesStr = getClosestTwoCities(distance_array);
  farthestTwoCitiesStr = getFarthestTwoCities(distance_array);

  cout << endl << "Total distance between the two cities is " << distance << " miles."
       << endl << endl;
  cout << "The total cost of travel for your trip from " << departure_city
       << " to " << arrival_city << " is $" << total_cost << "." << endl << endl;
  cout << "The average distance from " << departure_city
       << " to all other cities is " << distance_average << " miles." << endl << endl;

  cout << "The closest city to " << departure_city << " is " << closestCityStr
       << endl
       << endl;
  cout << "The farthest city to " << departure_city << " is "  << farthestCityStr << endl << endl;
  cout << "The closest two cities are " << closestTwoCitiesStr << endl << endl;
  cout << "The farthest two cities are " << farthestTwoCitiesStr << endl << endl;
}

// can be used to validate input too
CityType cityStringToEnum(string city_string) {

  // city_enum is declared to reference CityType enum value
  CityType city_enum;

  // for loop iterates through every character of the city string and converts
  // it to uppercase to identify the city string with a stored city enum value
  for (int i = 0; i < city_string.length(); i++) {
    city_string[i] = toupper(city_string[i]);
  } // every if/else-if branch identifies a certain city string paramater with a
    // stored city enum value
  if (city_string == "ATLANTA") {
    city_enum = CityType ::ATLANTA;
  } else if (city_string == "BOSTON") {
    city_enum = CityType::BOSTON;
  } else if (city_string == "CHICAGO") {
    city_enum = CityType ::CHICAGO;
  } else if (city_string == "DALLAS") {
    city_enum = CityType ::DALLAS;
  } else if (city_string == "DENVER") {
    city_enum = CityType ::DENVER;
  } else if (city_string == "HOUSTON") {
    city_enum = CityType ::HOUSTON;
  } else if (city_string == "LOS ANGELES") {
    city_enum = CityType ::LOS_ANGELES;
  } else if (city_string == "MEMPHIS") {
    city_enum = CityType ::MEMPHIS;
  } else if (city_string == "MIAMI") {
    city_enum = CityType ::MIAMI;
  } else if (city_string == "NEW YORK") {
    city_enum = CityType ::NEW_YORK;
  } else if (city_string == "PHILADELPHIA") {
    city_enum = CityType ::PHILADELPHIA;
  } else if (city_string == "PHOENIX") {
    city_enum = CityType ::PHOENIX;
  } else if (city_string == "SEATTLE") {
    city_enum = CityType ::SEATTLE;
  } else if (city_string == "SAN FRANCISCO") {
    city_enum = CityType ::SAN_FRANCISCO;
  } else if (city_string == "WASHINGTON DC") {
    city_enum = CityType ::WASHINGTON_DC;
  } else // if none of the previous city enum values were identified in the city
         // string, then the city string references an invalid city
    return CityType::INVALID;

  // a city enum value is returned
  return city_enum;
}

void buildDistanceTable(int distance_array[][CITY_SIZE], int city_size) {
  // two nested for loops are used to iterate through every row*column index
  for (int i = 0; i < city_size; i++) {
    for (int j = 0; j < city_size; j++) {
      // the ith and jth element of the constant globally declared Distance
      // Table is assigned to the ith and jth element of the 2D distance array
      distance_array[i][j] = DistanceTable[i][j];
    }
  }
  cout << endl;

  // a variable is declared to increment cities affected by the weather
  int weather_alert = 75;

  // only cities west of denver are incremented by weather_alert
  distance_array[cityStringToEnum("denver")][cityStringToEnum("seattle")] +=
      weather_alert;
  distance_array[cityStringToEnum("denver")][cityStringToEnum("los angeles")] +=
      weather_alert;
  distance_array[cityStringToEnum("denver")]
                [cityStringToEnum("san francisco")] += weather_alert;
  distance_array[cityStringToEnum("seattle")][cityStringToEnum("denver")] +=
      weather_alert;
  distance_array[cityStringToEnum("los angeles")][cityStringToEnum("denver")] +=
      weather_alert;
  distance_array[cityStringToEnum("san francisco")]
                [cityStringToEnum("denver")] += weather_alert;
}

CityType distanceIntToEnum(int city_index) {

  // a variable to assign the CityType enum is declared
  CityType city;

  // switch statment is used to sort through the different enum types
  // representing cities
  switch (city_index) {
  case CityType::ATLANTA:
    city = CityType::ATLANTA;
    break;
  case CityType::BOSTON:
    city = CityType::BOSTON;
    break;
  case CityType::CHICAGO:
    city = CityType ::CHICAGO;
    break;
  case CityType::DALLAS:
    city = CityType::DALLAS;
    break;
  case CityType::DENVER:
    city = CityType::DENVER;
    break;
  case CityType::HOUSTON:
    city = CityType::HOUSTON;
    break;
  case CityType::LOS_ANGELES:
    city = CityType::LOS_ANGELES;
    break;
  case CityType::MEMPHIS:
    city = CityType::MEMPHIS;
    break;
  case CityType::MIAMI:
    city = CityType::MIAMI;
    break;
  case CityType::NEW_YORK:
    city = CityType ::NEW_YORK;
    break;
  case CityType::PHILADELPHIA:
    city = CityType ::PHILADELPHIA;
    break;
  case CityType::PHOENIX:
    city = CityType ::PHOENIX;
    break;
  case CityType::SAN_FRANCISCO:
    city = CityType::SAN_FRANCISCO;
    break;
  case CityType::SEATTLE:
    city = CityType::SEATTLE;
    break;
  default:
    // if none of the previous enum values could be identified for the
    // user-entered city_index, then the city must be invalid
    city = CityType::INVALID;
  }

  // function returns the city represented by the integer city_index
  return city;
}

string enumToString(CityType enum_city) {
  // a city string is declared and intialized to be empty, to be later assigned
  // the name of city which identifies with the enum value
  string city = "";
  // a switch statement is used to sort through the different enum city values
  switch (enum_city) {
  case CityType::ATLANTA:
    city = "Atlanta";
    break;
  case CityType::BOSTON:
    city = "Boston";
    break;
  case CityType::CHICAGO:
    city = "Chicago";
    break;
  case CityType::DALLAS:
    city = "Dallas";
    break;
  case CityType::DENVER:
    city = "Denver";
    break;
  case CityType::HOUSTON:
    city = "Houston";
    break;
  case CityType::LOS_ANGELES:
    city = "Los Angeles";
    break;
  case CityType::MEMPHIS:
    city = "Memphis";
    break;
  case CityType::MIAMI:
    city = "Miami";
    break;
  case CityType::NEW_YORK:
    city = "New York";
    break;
  case CityType::PHILADELPHIA:
    city = "Philadelphia";
    break;
  case CityType::PHOENIX:
    city = "Phoenix";
    break;
  case CityType::SAN_FRANCISCO:
    city = "San Francisco";
    break;
  case CityType::SEATTLE:
    city = "Seattle";
    break;
  default:
    // if none of the previous enum values could be identified for the
    // user-entered city_index, then the city must be invalid
    city = "an invalid city";
  }
  // a string representing the city of the enum value is returned
  return city;
}

double getTripCost(int distance_array[][CITY_SIZE], CityType departure_enum,
                   CityType arrival_enum) {

  // two string variables for the departure/arrival enum, are declared and
  // assigned to the enumToString() function to be converted and evaluated for
  // error handling
  string departure_string = enumToString(departure_enum);
  string arrival_string = enumToString(arrival_enum);
  // if the departure/arrival string is invalid, the function returns -1
  if (cityStringToEnum(arrival_string) == CityType ::INVALID) {
    return -1;
  } else if (cityStringToEnum(departure_string) == CityType ::INVALID) {
    return -1;
  } else {
    // if the arrival/departure cities are valid, then the total cost is
    // computed
    float total_distance = distance_array[departure_enum][arrival_enum];
    float gas_price, mileage, total_cost;
    cout << "Enter the current price of gas per gallon: " << endl;
    cin >> gas_price;
    cout << "Enter the mileage per gallon of your vehicle: " << endl;
    cin >> mileage;
    total_cost = gas_price * (total_distance / mileage);
    return total_cost;
  }
}

double getAverageDistance(int distance_array[][CITY_SIZE], CityType city) {

  // the paramter city is converted to and assigned a string type for preceeding
  // error handling
  string string_city = enumToString(city);
  // the city string is converted to to an enum value, if the enum value cannot
  // be identified with a city, the city is invalid and the function returns -1
  if (cityStringToEnum(string_city) == CityType ::INVALID) {
    return -1;
  }

  double average;
  // a variable for the total distance is intialized to 0, so that it can be
  // incremented with the distance of each city through the for loop
  int totalDistanceAdded = 0;
  for (int x = 0; x < CITY_SIZE; x++) {
    totalDistanceAdded += distance_array[city][x];
  }
  // the average distance is the total distance divded by the number of cities
  average = totalDistanceAdded / CITY_SIZE;
  return average;
}

string getClosestCity(int distance_array[][CITY_SIZE], CityType departure) {
  // the maximum distance between any two cities is 3000 miles, so nearest city is intialized to 3000 in order to be decremented through the preceding for loop
  int nearestCity = 3000;
  //closest_city_enum is declared to eventually convert the index of the 2D array to an enum, ultimately identifying the city associated with that particular array index
  CityType closest_city_enum;
  //closest_city_string is declared to convert the enum into a string representing the closest city
  string closest_city_string; 
  for (int i = 0; i < CITY_SIZE; i++) {
    // the 
    if (distance_array[departure][i] < nearestCity && departure != i) {
      nearestCity = distance_array[departure][i];
      closest_city_enum = distanceIntToEnum(i);
      closest_city_string = enumToString(closest_city_enum);
    }
  }
  return closest_city_string + " [" + to_string(nearestCity) + "] miles";
}

string getFarthestCity(int distance_array[][CITY_SIZE], CityType departure) {
  int farthest_city = 0;
  
  CityType distant_city_enum;
  string distant_city_string;
  
  for (int i = 0; i < CITY_SIZE; i++) {
    if (distance_array[departure][i] > farthest_city && departure != i) {
      farthest_city = distance_array[departure][i];
      distant_city_enum = distanceIntToEnum(i);
      distant_city_string = enumToString(distant_city_enum);
    }
  }
  return distant_city_string + " [" + to_string(farthest_city) + "] miles";
}

string getClosestTwoCities(int distance_array[][CITY_SIZE]) {

  int closest_city = 3000;
  CityType closest_city_enum_one;
  CityType closest_city_enum_two;
  string closest_city_string_one;
  string closest_city_string_two;

  for (int i = 0; i < CITY_SIZE; i++) {
    for (int j = 0; j < CITY_SIZE; j++) {
      if (distance_array[i][j] < closest_city && i != j) {
        closest_city = distance_array[i][j];
        closest_city_enum_one = distanceIntToEnum(i);
        closest_city_enum_two = distanceIntToEnum(j);
        closest_city_string_one = enumToString(closest_city_enum_one);
        closest_city_string_two = enumToString(closest_city_enum_two);
      }
    }
  }
  return closest_city_string_one + "/" + closest_city_string_two + " [" +
         to_string(closest_city) + "] " + "miles";
}
string getFarthestTwoCities(int distance_array[][CITY_SIZE]) {
  int farthest_city = 0;
  CityType farthest_city_enum_one;
  CityType farthest_city_enum_two;
  string distant_city_string_one;
  string distant_city_string_two;

  for (int i = 0; i < CITY_SIZE; i++) {
    for (int j = 0; j < CITY_SIZE; j++) {
      if (distance_array[i][j] > farthest_city) {
        farthest_city = distance_array[i][j];
        farthest_city_enum_one = distanceIntToEnum(i);
        farthest_city_enum_two = distanceIntToEnum(j);
        distant_city_string_one = enumToString(farthest_city_enum_one);
        distant_city_string_two = enumToString(farthest_city_enum_two);
      }
    }
  }
  return distant_city_string_one + "/" + distant_city_string_two + " [" +
         to_string(farthest_city) + "] " + "miles";
}
