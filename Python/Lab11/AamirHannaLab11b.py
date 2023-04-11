
"""
Author: Hanna Aamir
Date; November 2, 2022
"""

def main():
    text = input("Your File: ")
    try:
        file = open(text,"r")
        word_count = 0
        word_input = input("Enter a word to count: ")
        linea = file.readline()

        while linea != "":
            line_list = linea.split()
            for word in line_list:
                if word == word_input:
                    word_count += 1
            linea = file.readline()
        print("Word count: ", word_count)
    except FileNotFoundError:
        print("File " + text +" not found. Try again.")

        
