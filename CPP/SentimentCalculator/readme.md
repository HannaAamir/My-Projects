### Purpose of this programming exercise
- An example of using string class and its string operations.
- An example of functions
- An example of struct and array data type
- Reading user inputs from the command line
- More exercise on for and while loops

### What does it do?

This program reads a ***socialsent*** scores from the file(*socialsent.csv*) provided by [the reference listed at the bottom of this page](#socialsent).

It builds a table of a **struct** which consists of two pieces of information ***[word, score]*** where *word* is a key to the socialsent *score*

Then the program reads a review file and maps each word in the file to a corresponding score in the SSS (**S**ocial **S**entiment **S**core) table. Then, it computes and displays the final score summed up from the scores of all the words in the entire file.

> **Usage:** &nbsp; ./main {file name}, where {file name} is optional. (e.g., bad.txt, good.txt)
<br><br>If a file name is not provided, "**review.txt**" will be used

### C string functions used. 
Click the link to get more information about the functions.
- [getline()](https://www.cplusplus.com/reference/string/string/getline/)
- [find()](https://www.cplusplus.com/reference/string/string/find/)
- [substr()](https://www.cplusplus.com/reference/string/basic_string/substr/)
- [c_str()](https://www.cplusplus.com/reference/string/basic_string/c_str/)
- [stof()](https://www.cplusplus.com/reference/string/stof/)

------
<a name="socialsent"/>  

[>> More info on socialsent](https://nlp.stanford.edu/projects/socialsent/)

##  Source files
- ***main.cpp***
  Main program.  This is the driver program that uses multiple functions and error handling to read a file and compute a sentient score of words from various reviews.

***functions.cpp***
  This file contains all the function definitions used by the driver program. Additionally, it contains the structure for sentient words and their assigned scores.
  
***implementation.cpp***
  This file contains the implementations of each function and the global variables used in the functions.

***output.txt***
  Contains the output of the driver program in a native text file.


##  Circumstances of programs

 
The program runs successfully.  
   
   The program was developed and tested on replit.com.  It was 
   compiled, run, and tested on replit.com .

## How to build and run the program

** 1. Source Files**  

   Under Files on Replit:
   ```
        main.cpp
        functions.hpp
        implemenation.cpp
   ```
** 2. Build the program.**

Reach the site that contains the file by:

  https://replit.com/join/kyitkfyhpi-hannaaamir
 
   
    Compile the program by running make command:
    % make

** 3. Run the program by: **
   `% ./main`

** 4. Delete the obj files, executables, and core dump by **
   `% ./make clean`


              