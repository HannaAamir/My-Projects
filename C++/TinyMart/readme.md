****
*  **Class**     :  CSCI 2312 Fall 2022
*  **Name        : Hanna Aamir**                                 
*  **HW#**       :  PA 6                
*  **Due Date**  :  Dec. 7, 2022
****
# Read Me

## Description of the program 

1. TinyMart is a product catalog system for a company which sells three major product types (Audio, Book, Video); Under the Book product category, there are two sub-products (e-book and paper book)
2. Each product is a seperate class, derived from the base class, Product.
3. The Cart class has-a Product class, to keep track of all the products.
4. Main.cpp uses these various classes to create different product objects and essentially, test out the catalog system.
5. No live user interaction is required.


##  Source files
- ***main.cpp***
  Main program.  This is the driver program that uses the various classes to compute, keep track of, and display all products. 

- ***AudioProduct.hpp***
  Function header program for Audio Product class. 
  
- ***AudioProduct.cpp***
  Implementation program for Audio Product class.
  
  ***VideoProduct.hpp***
  Function header program for Video Product class. 
  
- ***VideoProduct.cpp***
  Implementation program for Video Product class.
  
  ***BookProduct.hpp***
  Function header program for Book Product class. 
  
- ***BookProduct.cpp***
  Implementation program for Book Product class.
  
  ***EBookProduct.hpp***
  Function header program for EBook Product class. 
  
- ***EbookProduct.cpp***
  Implementation program for EBook Product class.
  
  ***PaperBookProduct.hpp***
  Function header program for Paper Book Product class. 
  
- ***PaperBookProduct.cpp***
  Implementation program for Paper Book Product class.

  ***Cart.hpp***
  Function header program for Cart class. 
  
- ***Cart.cpp***
  Implementation program for Cart class.

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
        AudioProduct.hpp
        AudioProduct.cpp
        VideoProduct.hpp
        VideoProduct.cpp
        BookProduct.hpp
        BookProduct.cpp
        EBookProduct.hpp
        EBookProduct.cpp
        PaperBookProduct.hpp
        PaperBook.cpp
        Cart.hpp
        Cart.cpp
        output.txt
   ```
** 2. Build the program.**

Reach the site that contains the file by:

  https://replit.com/join/jdadqjoovv-hannaaamir
 
   
    Compile the program by running make command:
    % make

** 3. Run the program by: **
   `% ./main`

** 4. Delete the obj files, executables, and core dump by **
   `% ./make clean`

