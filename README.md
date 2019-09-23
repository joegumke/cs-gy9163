# cs-gy9163

Welcome to the CS-GY 9163 README Page. This is for Fall2019 NYU course CS-GY 9163 from Professor Gallagher. 
The intent is to publish a spell checker application based in C.

There are 3 main functions : 

What the spell checker does is take two inputs (1 - dictionary, and 2 - list of words), and the spell checker makes a hash table of the dictionary provided by input 1. The hash table is built by processing the word to be stored in the dictionary and runs the hash function against this to build an index for the hash table. The hash table will be a list of linked nodes which could be linked lists if there are words that have the same index. 

Function Load Dictionary takes the dictionary input and builds the hash table mentioned above.

Function check word processes each individual word and verifies if the word is properly spelt by returning true if it is seen within the build dictionary by the previous load dictionary function.

Function check words ties these two previous functions together by taking a list of words and processes them into individual words, so that these can be run against the check word function above.

SpellChecker Application
Description Takes two inputs (1- dictionary, 2- list of words)
What the spell checker does is take two inputs (1 - dictionary, and 2 - list of words), and the spell checker makes a hash table of the dictionary provided by input 1. The hash table is built by processing the word to be stored in the dictionary and runs the hash function against this to build an index for the hash table. The hash table will be a list of linked nodes which could be linked lists if there are words that have the same index. 
Function Load Dictionary takes the dictionary input and builds the hash table mentioned above.
Function Load Dictionary Low Level Detail:
Line 57 starts the function by opening and reading a file input from the user, and line 60 validates whether this is a valid file or not. We instantiate out dictionary list by setting all the values in this table to NULL on line 63. Line 66 and 69 are declaring variables used for placing the generated hash value and the Length of a word (char line). We start to read the input dictionary file on line 72 by using fgets and use the length variable declared in dictionary.h to dictate how long a word should be, with the last value of the dict_file itself to read from. We strip newlines from the values read at the line by stripping newlines from them on line 74. We use line 77 to read through every character of every string read into the input and convert them to lower case. Line 79 places the value of the generated hash value, and is checked for if valid(NULL) on line 81. If it passes the null check it will then pass onto generating the dictionary by creating a curr variable which is allocated memory on line 84 by using the size of the node to allocate. We copy the input to the currently placed node pointer from the input of the word on line 86, and then set the next pointer to null on line 88. We place the value of the hashtable on line 90 using the current node pointer curr. If the hashvalue on the current node is not null, we can assume that this is already in the hash table and build up a linked list to build hashes ontop of the existing hash table node, lines 95 >101 do this.
 
Function Check Word Low Level Detail:
Function check word processes each individual word and verifies if the word is properly spelt by returning true if it is seen within the build dictionary by the previous load dictionary function. It initially takes the word (line 30) and checks to verify if any of the inputs are valid by checking for NULL, if not the function returns 0. If the inputs are not NULL, we create a bucket variable to store the hash that we generate from the input word passed from check_words, and create a node named curr in which we store this value. We then loop / iterate through the hash table created in the load_dictionary function and iterate through until we find a match (line 43), if we do not find a match, we set the curr pointer to the next node in the hash table. 
 

Function Check_Words Low Level Detail:
Function check words ties these two previous functions together by taking a list of words and processes them into individual words, so that these can be run against the check word function above. We check if the file is valid by checking for NULL, if the file is non-existent, we return 1 (line 114). We then setup variables for processing from (line 116 > 122). At line 125 we build a loop through the file and read using fgets by using a placeholder (wordbuffer variable) to copy the data read into, a character limitation of 5,000, and use the file pointer to read from. Line 131 provides the syntax for using string tokenization by instantiating the value of NULL and empty arguments to it. We start the loop for processing the data at line 133, by stripping newline characters and null terminators at line 134/135. We strip the punctuation at the end of a word on lines 140>143. Line 156 creates a true/false (bool) variable to hold and return the value passed onto check_word which returns if the value is actually in the dictionary of not. We process the result by looking at line 160 by seeing if the result if FALSE or 0, if it is we can verify that this is improperly spelled and add this to the misspelled words list and increment our misspelled counter. 
 
