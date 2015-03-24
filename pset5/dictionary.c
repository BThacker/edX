/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
// tracking words loaded
int wordCount;
// pointer to root
node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int ind = 0;
    int node_index;
    struct node* cursor = root;
    
    // per letter in input word
    while (word[ind] != '\0')
    {
        if (isalpha(word[ind]))
        {
            if (isupper(word[ind]))
            {
                node_index = word[ind] - 'A';
            }
            else
            {
                node_index = word[ind] - 'a';
            }
        }
        else
        {
            node_index = 26;
        }
        if (cursor->node[node_index] == NULL)
        {
            return false;
        }
        // if it isn't null continue
        else
        {
            // next letter
            cursor = cursor->node[node_index];
        }
        ind++;
    }
    if (cursor->is_word == true)
    {
        return true;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open file
    FILE* dict = fopen(dictionary, "r");
    
    char word[LENGTH + 1];
    int ind = 0;
    char char_word;
    wordCount = 0;
    
    root = (struct node*) malloc(sizeof(node));
    
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        if (c == '\n')
        {
            word[ind] = c;
            wordCount++;
            struct node* cursor = root;
            for (int i = 0; i <= ind; i++)
            {
                char_word = word[i];
                if (isalpha(char_word))
                {
                    if (cursor->node[char_word - 'a'] == NULL)
                    {
                        cursor->node[char_word - 'a'] = (struct node*) malloc(sizeof(node));
                    }
                    cursor = cursor->node[char_word - 'a'];
                }
                else if (char_word == '\'')
                {
                    if (cursor->node[26] == NULL)
                    {
                        cursor->node[26] = (struct node*) malloc(sizeof(node));
                    }
                    cursor = cursor->node[26];
                }
               else if (char_word == '\n')
               {
                    cursor->is_word = true;
               }  
            }
            ind = 0;   
        }
        else
        {
            word[ind] = c;
            ind++;
        }
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // returns the word count if loaded
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
 
// to free nodes and all nodes under
bool nodefree(struct node* node)
{
    for (int i = 0; i < 27; i++)
    {
        if (node->node[i] != NULL)
        {
            nodefree(node->node[i]);
        }
    }
    free(node);
    
    return true;
}

bool unload(void)
{
    if (nodefree(root))
    {
        return true;
    }
    return false;
}


