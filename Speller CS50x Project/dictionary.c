// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; //length of the word + 1 for unsigned integer (/0)
    struct node *next;
} node;



// TODO: Choose number of buckets in hash table
const unsigned int N = 2000; // this bucket holds the variables a to z as well as aa, ae, ai, ao, au, ba, be, bi, bo, bu, and so on and so forth

// Hash table
node *table[N];

// Number of words in the dictionary
unsigned int dict_size;

void print_buckets(void)
{
    unsigned long sum_sq = 0;
    int num_words = (int)size();

    // use dynamic memory allocation instead of the stack for these arrays,
    // in order to prevent a possible stack overflow
    int *collisionCount = calloc(num_words, sizeof *collisionCount);
    int *bucketCounter  = calloc(N, sizeof *bucketCounter);
    if (bucketCounter == NULL || collisionCount == NULL)
    {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }

    // fill bucketCounter array
    for (int i = 0; i < N; i++)
    {
        for (node *p = table[i]; p != NULL; p = p->next)
        {
            bucketCounter[i]++;
        }
    }

    // fill collisionCount array
    for (int i = 0; i < N; i++)
    {
        collisionCount[bucketCounter[i]]++;
    }

    // print content of collisionCount array and update sum_sq
    for (int i = 0; i < num_words; i++)
    {
        if (collisionCount[i])
        {
            sum_sq += (long) i * i * collisionCount[i];
            printf("Buckets with %i nodes: %i\n", i, collisionCount[i]);
        }
    }

    // print final information
    printf("\n");
    printf("Sum  of squares: %lu\n",  sum_sq);
    printf("Mean of squares: %.3f\n", (double)sum_sq / num_words);

    // Exit the program prematurely, so that you can see the diagnostic output
    // instead of the misspelled words. Exiting prematurely will cause memory leaks,
    // so don't run this function with valgrind.
    exit(EXIT_SUCCESS);
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int n = hash(word);
    node *cursor = table[n];

    for (cursor = table[n]; cursor != NULL; cursor = cursor->next) // Iterates through the linked list of the word's hash value
    {
        if (strcasecmp(word, cursor->word) == 0)                   // Compares if the given word(char *word) is equal to the word element that the cursor is currently pointing to in the node array
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int len = strlen(word);
    int sum = 0;
    int hashed_value = 0;

    for (int i = 0; i < len; i++)
    {
        if (isalpha(word[i]) != 0)
        {
            char letter = toupper(word[i]); // Get the sum of all the words in the string
            int value = letter - 'A';
            sum = sum + value;              // Add the current value to the accumulator
        }
    }
    hashed_value = sum % 2000;          // Modulo the sum by whatever amount
    return hashed_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // Initialize the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Opens the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Temporary buffer for fscanf
    char letters[LENGTH + 1];
    unsigned int no_words = 0;

    // Read words from the dictionary file and create memory for each of them
    while(fscanf(file, "%s", letters) != EOF)
    {
        node *ptr = malloc(sizeof(node));
        if (ptr == NULL)
        {
            return false;
        }

        strcpy(ptr->word, letters);
        unsigned int n = hash(ptr->word);   // Stores the hash value to an unsigned int called n
        ptr->next = table[n];               // Sets the pointer of the new node to the first element of the linked list which is table [n]
        table[n] = ptr;                     // Reset the first element of the linked list to be the new node
        no_words++;                         // Adds one to the total number of words loaded from the dictionary
    }
    dict_size = no_words;
    fclose(file); // ALWAYS CLOSE THE FILE
    return true;
    //print_buckets();
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *tmp;

    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while(cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    return true;
}
