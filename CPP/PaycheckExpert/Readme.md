****
*  **Class**     :  CSCI 2312 Fall 2022
*  **Name        : Hanna Aamir**                                 
*  **HW#**       :  PA 2 (problem 1)                
*  **Due Date**  :  Sep. 20, 2022
****
# Read Me

## Description of the program 

1. The program takes a set of payroll information and computes the weekly net payment of an hourly employee’s wage.
2. The user only inputs 3 pieces of information: hourly wage, hours worked per week, retirement contribution every week.
3. The first if-else loop is used to compute overtime pay (if applicable), followed by the weekly gross pay.
4. Next, the annual gross pay is computed, using a designated variable.
5. Withdrawals, such as medicare and social security, are computed, using their own assigned variables. The withdrawal is converted into a weekly deduction amount.
6. Then, the federal tax is computed, based on the annual gross pay and it’s tax bracket, through if-else loops. The federal tax is further converted into a weekly amount.
7. Finally, the Colorado state tax is computed at a specified flat rate and converted into.a weekly amount.
8. The deduction total is computed by adding the social security withdrawal, medicare withdrawal, federal tax, Colorado state tax and retirement contribution.
9. The net pay is computed by subtracting the deduction total from the weekly gross pay.
10. At last, all the wage details which have been computed (except for the annual gross pay) are output to the screen, in an orderly fashion. 


##  Source files
- ***main.cpp***
  Main program.  This is the driver program that uses multiple if-else loops and arithmetic expressions to compute wage details and output them to the screen.


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
	https://replit.com/@hannaaamir/PA2-Paycheck-Expert#main.cpp
 
   
    Compile the program by running make command:
    % make

** 3. Run the program by: **
   `% ./main`

** 4. Delete the obj files, executables, and core dump by **
   `% ./make clean`


              