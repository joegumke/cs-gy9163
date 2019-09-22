# cs-gy9163

Welcome to the CS-GY 9163 README Page. This is for Fall2019 NYU course CS-GY 9163 from Professor Gallagher. 
The intent is to publish a spell checker application based in C.

Description Takes two inputs (1- dictionary, 2- list of words)

There are 3 main functions : 

What the spell checker does is take two inputs (1 - dictionary, and 2 - list of words), and the spell checker makes a hash table of the dictionary provided by input 1. The hash table is built by processing the word to be stored in the dictionary and runs the hash function against this to build an index for the hash table. The hash table will be a list of linked nodes which could be linked lists if there are words that have the same index. 

Function Load Dictionary takes the dictionary input and builds the hash table mentioned above.

Function check word processes each individual word and verifies if the word is properly spelt by returning true if it is seen within the build dictionary by the previous load dictionary function.

Function check words ties these two previous functions together by taking a list of words and processes them into individual words, so that these can be run against the check word function above.
