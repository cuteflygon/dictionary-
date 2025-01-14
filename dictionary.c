// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Number of words in dictionary
unsigned int COUNT = 0;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens a dictionary file
    FILE* inptr = fopen(dictionary,"r");

    if (inptr == NULL)
    {
        return false;
    }

    //declare a variable buffer to store words from the dictionary after reading
    char buffer[LENGTH + 1];

    //initialises values of Hashtable to NUll;
    for (int n = 0; n <= N; n++)
    {
        table[n] = NULL;
    }

    //Read string from a file and store into a buffer
    while(fscanf(inptr,"%s",buffer) != EOF)
    {
        //Update the number of words in dictionary
        COUNT++;

        //Creation of a new Node to store the word
        node* n = malloc(sizeof(node));
        if ( n == NULL)
        {
            return 2;
        }
        strcpy(n->word,buffer);
        n->next = NULL;

        //getting the hash value
        int x = hash(n->word);

        //if hashed index is empty, this is the header node
        if (table[x] == NULL)
        {
            table[x] = n;
        }
        else
        {
            n->next = table[x];
            table[x] = n;

        }
        // iterates through the linked list

    }
    fclose(inptr);
    return true;
}

// Hashes word to a number based on the ASCII values
unsigned int hash(const char *word)
{
    int value = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //convert alphabet to lowercase for case insensitivity
        int x = tolower(word[i]);
        if (i%2==0)
        {
            value = value*x;
        }
        else if (i%2 != 0)
        {
            value = value+x;
        }
    }
    value = value%N;
    return value;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Retrieve a Hash code
    int x = hash(word);

    //Compare the word
    node* tmp = table[x];

    while (tmp != NULL)
    {
        if (strcasecmp(word,tmp->word) == 0)
        {
            return true;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return COUNT;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Counter variable which tracks the number of nodes freed
    int check = 0;

    // iterates through the linked list
    for (int i = 0; i < N; i++)
    {
        node* tmp = table[i];
        node* tracker;

        while (tmp != NULL)
        {
            tracker = tmp->next;
            free(tmp);
            tmp = tracker;
        }
        check++;
    }

    if (check == N)
    {
        return true;
    }
    return false;
}

void printDictionary ()
{
    for (int i = 0; i < N; i++)
    {
        node* tmp = table[i];

        while (tmp != NULL)
        {
            printf("%s ",tmp->word);
            tmp = tmp->next;
        }
        printf("\n");
    }
}
