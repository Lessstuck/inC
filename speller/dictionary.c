// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
const unsigned int N = 5;

// Hash table
node *table[N];

int wordCount;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // convert to lower case
    char *lookupWord = malloc(strlen(word));
    if (lookupWord == NULL)
    {
        return false;
    }
    lookupWord = strcpy(lookupWord, word);
    for (int i = 0; i < strlen(lookupWord); i++)
    {
        lookupWord[i] = tolower(word[i]);
    }
    // calculate hash of word and search corresponding linked list
    int h = hash(lookupWord);
    if (table[h] == NULL)
    {
        free(lookupWord);
        return false;
    }
    // lookup node used to go through linked list
    node *lookup = malloc(sizeof(node));
    if (lookup == NULL)
    {
        printf("Out of memory!\n");
        return false;
    }
    if (table[h]->next == NULL) // nothing stored at this hash
    {
        free(lookup);
        free(lookupWord);
        return false;
    }
    lookup = table[h]->next;
    do
    {
        // printf("hash: %i, lookup->word: %s, lookupWord: %s\n", h, lookup->word, lookupWord);
        if (strncmp(lookup->word, lookupWord, LENGTH + 1) == 0)
        {
            free(lookupWord);
            // free(lookup);
            return true;
        }
    }
    while ((lookup = lookup->next) != NULL);

    free(lookupWord);
    free(lookup);
    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    // sourced from CS50 video
    int sum = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += word[j];
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Error opening dictionary\n");
        return false;
    }
    char *newWord = malloc(sizeof(char) * LENGTH);
    int h;
    wordCount = 0;

    while (fgets(newWord, LENGTH, fp) != NULL)
    {
        newWord = strtok(newWord, "\n");   // removes newline from string
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        else
        {
            strcpy(n->word, newWord);
            n->next = NULL;
            h = hash(newWord);
            if (table[h] == NULL) // first item in linked list at this hash
            {
                node *head = malloc(sizeof(node));
                if (head == NULL)
                {
                    return false;
                }
                head->next = n;
                table[h] = head;
                // printf("first table[%i]->next->word: %s\n", h, table[h]->next->word);
            }
            else // new item to be inserted at the beginning of the list
            {
                node *head = malloc(sizeof(node));
                if (head == NULL)
                {
                    return false;
                }
                head = table[h]->next;
                n->next = head;
                table[h]->next = n;
                // printf("additional table[%i]->next->word: %s\n", h, table[h]->next->word);
            }
            wordCount++;
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        else
        {
            node *temp = malloc(sizeof(node));
            node *head = malloc(sizeof(node));
            // delete links from head, code ideas from stackoverflow by insumity (June 20, 2011)
            head = table[i];
            while (head != NULL)
            {
                temp = head;
                head = head->next;
                // free(temp);
            }
            free(head);
        }
    }

    return true;
}
