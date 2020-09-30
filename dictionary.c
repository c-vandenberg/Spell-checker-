// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Define node in hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Keep track of number of words in dictionary
int dict_size = 0;

// Number of buckets in hash table
const unsigned int HASHTABLE_SIZE = 65536;

// Declare Hash table
node *hashtable[HASHTABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash lowercase word to obtain index
    int hash_index = hash(word);
    // Create pointer to node that points to the linked list at that element
    node *trav = hashtable[hash_index];
    // Traverse/search linked list for desired word
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char lowercase_word[LENGTH + 1];
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        lowercase_word[i] = tolower(word[i]);
        hash = (hash << 2) ^ lowercase_word[i];
    }
    return hash % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary.h file
    FILE *dict_ptr = fopen(dictionary, "r");
    // Check to see if dictionary.h file pointer is NULL
    if (dict_ptr == NULL)
    {
        fprintf(stderr, "Error: Could not open %s", dictionary);
        return false;
    }
    // Create array of chars into which we can temporarily store each word
    char buffer[LENGTH + 1];
    // Loop over each word to copy each into the buffer until we reach end of file (EOF)
    while (fscanf(dict_ptr, "%s", buffer) != EOF)
    {
        // Create temporary node for current word
        node *current = malloc(sizeof(node));
        // Check if pointer to temporary node equals NULL
        if (current == NULL)
        {
            return false;
        }
        // Copy current word into string field of node
        strcpy(current->word, buffer);
        // Implement hash function on current word to obtain hash table index value for current word
        int index = hash(buffer);
        // Add current word node to hashtable array
        // If there are no nodes at that element, simply add node to that element
        if (hashtable[index] == NULL)
        {
            current->next = NULL;
            hashtable[index] = current;
            dict_size++;
        }
        // Else add current node to beginning of linked list at that element
        else
        {
            current->next = hashtable[index];
            hashtable[index] = current;
            dict_size++;
        }
    }
    fclose(dict_ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Decalre destroy function
void destroy(struct node *list);

// Destroy function deletes an entire linked list recursively

void destroy(struct node *list)
{
    // Initialise current node pointer to point to head of list
    node *current_node = list;
    // Recursion base case
    if (current_node == NULL)
    {
        return;
    }
    destroy(current_node->next);
    free(current_node);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        if (hashtable[i] == NULL)
        {
            continue;
        }
        destroy(hashtable[i]);
    }
    return true;
}