// Implements a dictionary's functionality
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N]; //an array of node pointers (linked lists); 
//where every element is a pointer to a node (buckets)

int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node *n = table[hash_value];
    
    while (n != NULL) {
        if (strcasecmp(n->word, word) == 0)
            return true;
        n = n->next;
    }
    return false;
}

// Hashes word to a number
/*unsigned int hash(const char *word)
{
    int hash = 401;
    
    //while (*word != '\0') {
      //  char *hash_word = tolower(*word)
       // word++;
    
    while (*hash_word != '\0') {
        hash = ((hash << 4) + (int)(*hash_word)) % MAX_TABLE;
        hash_word++;
    }

    return hash % MAX_TABLE;
}*/


unsigned int hash(const char *word)
{
  /* credits to...
     *https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
     */
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open dictionary in dict_pointer
    FILE *dict_pointer = fopen(dictionary, "r");
    //check if there is something in that pointer
    if(dict_pointer == NULL)
    {return false;}
    //go through the table and mark all buckets NULL
    for(int i = 0; i<N; i++)
    {
        table[i] = NULL;
    }
    //create a character array that will temporarily store the word from the dictionary before you make a hash and store it in the hash.
    char current_word[LENGTH + 1];
    //while you can scan for a word, (which is already putting it in current_word(hidden as a condition)
    while(fscanf(dict_pointer, "%s\n", current_word) != EOF) {
        //create space for the NODE that you will insert into the hash table
        node* n = malloc(sizeof(node));
        if(n == NULL){
                printf("Not enough memory to load dictionary file"); 
                return 1;
            }
        //copy the word in the temp (current_word) into the node we are working on currently ( n->word)
        strcpy(n->word, current_word);
        //find the hash for the current_word
        int hash_value = hash(n->word);// can use n->word or current_word
        //insert the node into the hash file by doing the switcheroo thingy
        n->next = table[hash_value];//point to eh second to be node
        table[hash_value] = n;//then point the bucket name to the new node//now the bucket points to the NEW START of the nod
        dict_size++;//add dict_size because we can do it right now and not later.
    }
    fclose(dict_pointer);    
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{ //loop each value fo the hash table
    for(int i = 0; i<N; i++){
        //create a new cursor for the start of each hash value we work on.
        node* cursor = table[i];
        
        while(cursor != NULL){// while cursor still equals something
           node* tmp = cursor;//give the tmp value of the cursopr because we need something to reference what node we are still on.
           cursor = tmp->next;//make cursor equal the next thing in the node so we can delete tmp later.
           free(tmp); //free the tmp value, 
        }
        table [i] = NULL; //make the bucket names also equal NULL.
    }
    return true;
}
