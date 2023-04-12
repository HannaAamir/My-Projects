### Purpose of this programming exercise
- An example of using string class and its string operations.
- An example of functions
  An example of struct and array data type
- reading user inputs from the command line
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