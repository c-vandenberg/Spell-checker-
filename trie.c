#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

// Decalre trie node struct
typedef struct trie
{
    bool isLeaf;
    struct trie* children[Alphabet_size];
}
trie;

// Function that gets new trie node
struct trie* getNewTrieNode(void)
{
    // Malloc memory for new trie node and check pointer != NULL
    struct trie* node = malloc(sizeof(trie));
    if (node != NULL)
    {
        // Set isLeaf Boolean to false
        node->isLeaf = false;
        // Initialise all 26 child pointers to NULL
        for (int i = 0; i < Alphabet_size; i++)
        {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Hash function to hash to correct trie index for each letter in word
unsigned int hash(const char word)
{
    // assign the last position to the apostrophe
    if (word == '\'')
    {
        return Alphabet_size - 1;
    }

    // ignore case by converting the given letter to lowercase
    return tolower(word) - 97;
}

// Function to insert a new node into the trie at the correct child for letters of word
bool insert_trie(trie_ptr root, const char *word)
{
    // Initialise current node as root node
    trie_ptr current_node = root;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        // Hash current letter of word
        unsigned int h = hash(word[i]);
        // Create a new node if needed
        if (current_node->children[h] == NULL)
        {
            current_node->children[h] = getNewTrieNode();
        }
        // Move to next node
        current_node = current_node->children[h];
    }
    // Once we have reached the last letter of word, set current nodes isLeaf Boolean to true
    current_node->isLeaf = true;
    return true;
}

// Function to search the trie for a given word, starting at root node
bool search_trie(trie_ptr root, const char *word)
{
    // Initialise current node as root node
    trie_ptr current_node = root;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        // Hash current letter of word
        unsigned int h = hash(word[i]);
        // Go to next node
        current_node = current_node->children[h];
        // If current node pointer is NULL we have reached the end of the path and the word has not been found
        if (current_node == NULL)
        {
            return false;
        }
    }
    // If we have gotten through the whole word. the current node must be the Leaf node corresponding to that word
    return (current_node->isLeaf);
}

// Destroys entire trie data structure recursively and frees dynamically allocated memory
void destroy(struct trie* root)
{
    // Initialise current node to point to root node to traverse trie data structure
    struct trie* current_node = root;
    // Recursively delete entire trie data structure
    for (int i = 0; i < Alphabet_size; i++)
    {
        if (current_node->children[i] != NULL)
        {
            destroy(current_node->children[i]);
        }
    }
    free(current_node);
}