****
*  **Class**     :  CSCI 2312 Fall 2022
*  **Name        : Hanna Aamir**                                 
*  **HW#**       :  PA 2 (problem 2)                
*  **Due Date**  :  Sep. 20, 2022
****
# Read Me

## Description of the program 

1. The game begins immediately upon running the program, by executing the outer while loop which is designated for running the game, and prompts the user to input their guess number.
2. An inner nested while loop is executed to count the number of tries for each game. Additionally, the inner while loop is used to evaluate the user's inputted
	guess and alert the user if their guess is greater than or lower than the random number.
3. If the user's guess is correct, the third and final branch of the nested inner while loop executes and alerts the user that their guess is correct and also outputs how many tries
	it took.
4. The outer nested while loop executes, prompting the user to play again. If the user's input signifies wanting to play again, then the beginning of the outer while loop executes.
5. Another random number is generated  and the game starts again.
6. This process continues and is only terminated once the user indicates not wanting to play again.


##  Source files
- ***main.cpp***
  Main program.  This is the driver program that uses nested while loops
   to read guesses inputted by the user and evaluate how correct they are. 

.   
##  Circumstances of programs

 
The program runs successfully.  
   
   The program was developed and tested on replit.com.  It was 
   compiled, run, and tested on replit.com .

## How to build and run the program

** 1. Source Files**  

   Now you should see a directory named homework with the files:
   ```
        main.cpp
        
   ```
** 2. Build the program.**

Reach the site that contains the file by:
	https://replit.com/@hannaaamir/PA2-Number-Guessing-Game#main.cpp
 
   
    Compile the program by running make command:
    % make

** 3. Run the program by: **
   `% ./main`

** 4. Delete the obj files, executables, and core dump by **
   `% ./make clean`


              