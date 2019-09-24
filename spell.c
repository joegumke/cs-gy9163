// Class: NYU CS-GY 9163
// Assignment 1 - Spell checker
// Author: Joe Gumke
// Date : 9-7-19
// Filename : spell.c
// Description : Spell Checker -- checks correctness of the words provided. should be based on hash maps
// should populate a hash map with words from the dictionary. 
// When checking if word is spelled correctly, you can check to see if it exists an entry in the hash map

#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// compile gcc -o main dictionary.c dictionary.h spell.c main.c
// gcc -o main dictionary.c dictionary.h spell.c test_main.c  -lcheck -lm -lrt -lpthread -lsubunit
// gcc -o main dictionary.c dictionary.h spell.c test_main.c -Wall -lcheck -lm  -lrt -lpthread -lsubunit;./main
// ulimit -c unlimited
// gdb progrname core

// 3 functions
//extern int hash_function(const char* word);

// 1 - function to check if a word is spelled correctly (check_word)
// check word is using check words to check every word of the input file
// check word if it exists in the hash map -- called after load dictionary  
bool check_word(const char* word, hashmap_t hashtable[])
{
    if((word == NULL || hashtable == NULL || strlen(word) >LENGTH)){return 0;}
    else{
    // To search the hashmap, you will want to:

    //printf("%s\n",word);

    //wordBuffer
    char wordBuffer[LENGTH+1];

    //lowercase the word:
    for(int b=0;b<=strlen(word);b++){wordBuffer[b] = tolower(word[b]);}
    //printf("WORDBUFFER: [%s]\n",wordBuffer);

    //  1) Calculate the hash
    int bucket = hash_function(wordBuffer);

    //  2) look at the node * at hashtable[tempHash], let's call it curr.
    node * curr =hashtable[bucket];
    //  3) while curr is not null:
    while(curr){   
        // 1) if curr->word is equal to word, return true
        //printf("[%s][%s]", word,  curr->word);
        if(strcmp(curr->word,wordBuffer)==0){return 1;}

        // 2) curr = curr->next
        else (curr = curr->next);
    }
    // 4) return false      
    return 0;
    }
}

// 2 - function to load list of words into the hash map (load_dictionary)
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{   
    // Open dict_file from path stored in dictionary.
    FILE *dict_file = fopen(dictionary_file, "r");

    //If dict_file is NULL -- return false
    if(!dict_file){return false;}

    //Initialize all values in hash table to NULL.
    for(int w=0; w<=HASH_SIZE;w++){hashtable[w]=NULL;}

    // Declare variable for hash value
    int hashvalue;

    // Assign the read line a character Array with Length as size
    char line[LENGTH];

    //While word in dict_file is not EOF (end of file):
    while(fgets(line,LENGTH,dict_file)){
        // strip newline 
        if(line[strlen(line)-1] =='\n'){line[strlen(line)-1]='\0';}
        
        //convert dictionary to lower
        for(int a=0;a<=strlen(line);a++){line[a]= tolower(line[a]);}
        
        hashvalue = hash_function(line);
        //  1) get an index by calling hash_function(word), as you did above.
        if(hashtable[hashvalue] == NULL){
        //  2) if hashtable[hashvalue] == NULL, then:
        //      1) create a new node *. Let's call it curr. (malloc, etc)
                node * curr = malloc(sizeof(node));
        //      2) set curr->word = word (might need strncopy here).
                strncpy(curr->word,line,LENGTH);
        //      3) set curr->next = NULL
                curr->next = NULL;
        //      4) set hashtable[hashvalue] = curr
                hashtable[hashvalue] = curr;
        }
        else{
        //  3) else:
        //      1) create a new node *. Let's call it curr (malloc, etc)
                node * curr = malloc(sizeof(node));
        //      2) set curr->word = word (might need strncopy here).
                strncpy(curr->word,line,LENGTH);
        //      3) set curr->next = hashtable[index]
                curr->next =hashtable[hashvalue];
        //      4) set hashtable[hashvalue] = curr
                hashtable[hashvalue] = curr;
            }
    }
    //Close dict_file.
    fclose(dict_file);
    return 1;
}

// 3 - function to tie the above 2 together (check_words)
// parameter to check_words will be a file pointer containing lines of words seperated by spaces,punctuation, etc
// word defined as seperated by spaces && if punctuation in a word, then mispelled
int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[1000]){ 

    //Check and close if File not correct
    if(!fp){return 1;}
    // set int num_misspelled to 0.
    int num_misspelled = 0 ;

    //initialize wordBuffer to read file into
    char wordBuffer[500000];

    // variable to instantiate placeholder for individual word
    char* token = strtok(wordBuffer," ");

    //For loop for reading file
    while(fgets(wordBuffer,500000,fp)){

        //printf("Sentence: %s\n",wordBuffer);
        //printf("TOKENBEFORE: %s\n",token);
        token = strtok(NULL," ");
        
        while(token != NULL){
            if(token[strlen(token)-1] =='\n'){token[strlen(token)-1]='\0';}
            token[strlen(token)]='\0';           
            //printf("TOKEN:  %s \n",token);
            
            //Punctuation strip RIGHT of word          
            bool afterPUNC = ispunct(token[strlen(token)-1]);
            if(afterPUNC){while(afterPUNC){
                token[strlen(token)-1]='\0';
                afterPUNC = ispunct(token[strlen(token)-1]);
                    }
                }
            
            // Punctuation strip LEFT of word
            bool beforePUNC = ispunct(token[0]);
            if(beforePUNC){while(beforePUNC){
                    token++;
                    beforePUNC = ispunct(token[0]);
                    }
                }

            //printf("TOKENPROCESSED: %s\n",token);

            // Check if the word exists in the dictionary
            bool wordCheckResult = check_word(token,hashtable);
            //printf("%d",wordCheckResult);
            //printf("wordCheckResult: %i\n", wordCheckResult);
            // If word exists, increment num_misspelled
            if(!(wordCheckResult == 1)){
                //malloc space in the misspelled element strcopy in?
                misspelled[num_misspelled] = malloc(strlen(token));
                strcpy(misspelled[num_misspelled], token);
                num_misspelled ++;
                }
            token = strtok(NULL," ");
            }
        }
    //printf("MISSPELLED: %i\n",num_misspelled);
    return num_misspelled;
}

//int main(){}

