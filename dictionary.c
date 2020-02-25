// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10 ;

// Hash table
node *table[N];

int wordCount;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h = hash(word);
    node *lookup = table[h];
    do
    {
        lookup = lookup->next;
    }
    while (lookup->word != word && lookup != NULL);
    // check
    if (lookup->word == word)
    {
        return true;
    }
    else
    {
        return false;
    }
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

    while (fgets(newWord, LENGTH, fp) != NULL) //should I be using fscanf?
    {
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
            }
            else // new item to be inserted at the beginning of the list
            {
                n->next = table[h]->next;
                table[h]->next = n;
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
        while (table[i] != NULL)
        {
            // search non-empty members of hash table
            node *search = table[i];
            while (search != NULL)
            {
                search = search->next;
            }
            // TODO work backwards to free all nodes
            free(search);
        }
    }

    return true;
}
