/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"



// Head of Trie
node *ROOT = NULL;


// To reduce the load time of sizeof in loops, store it in a variable
long int node_size = (long int) sizeof (node);


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

  // Function prototype
  int char_position (char c);


  // The location of each character from zero in array children[]
  int char_place = 0;
  // Don't use the head of trie to itterate
  node *traverse = ROOT;


  if ( !traverse )
    {
      printf ("Root in Trie is empty.\n");
      return false;
    }


  for (int i = 0, length = strlen(word); i < length; i++)
    {


      char_place = char_position ( word[i] );

      if (char_place == -1)
        continue;


      // If this children node was never loaded with a character then ...
      if (  !traverse -> children[char_place] )
        return false;

      // "else" dive into the characters of the word
      traverse = traverse -> children[char_place];
    }

  return traverse -> is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // Function's prototype
    int char_position (char c);
    node *create_node (void);


    FILE *dict_file = fopen (dictionary, "r");

    if ( dict_file == NULL)
    {
        fprintf ( stderr, "%s cannot be opened!.\n", dictionary);
        exit (1);
    }


    // Initilialize the HEAD of Trie for the first time
    ROOT = create_node();

    // The location of each character from zero in array children[]
    int char_place = 0;
    // Don't use the head of trie to itterate
    node *traverse = NULL;


    // to fill array with words from dictionary file
    char line [ LENGTH ];




    while ( fscanf (dict_file, "%s", line) != EOF )
    {
      // for not touching ROOT and doing itteration with another pointer
      traverse = ROOT;
      for (int i = 0, length = strlen(line); i < length; i++)
        {

          char_place = char_position ( line[i] );

/*
          if (char_place == -1)
          {
            printf ("%c Out of order character!\n", line[i]);
            continue;
          }
*/

          // If this children node was never loaded with a character then create one
          if ( !traverse -> children[char_place] )
            traverse -> children[char_place] = create_node();

          /**
           * There's no need for "else" we either loaded the node and now we need
           * to traverese to it or we had the node loaded from before and we need
           * to dive into it.
           */
          traverse = traverse -> children[char_place];

        }

      traverse -> is_word = true;
    }

    // Close the file
    fclose (dict_file);

    /**
     * if their pointer location is equal it means that
     *  dictionary file never loaded into memory.
     */

    return traverse != ROOT;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  // Function's prototype
  unsigned int count_all (node *root);

  // Don't use the head of trie to itterate
  node *traverse = ROOT;

  return count_all(traverse);

  // return total_words;
}

/**
 * count all the node that has a character
 */

unsigned int count_all (node *root)
{

  unsigned int sum = 0;

  if ( !root )
    return 0;


  if ( root -> is_word )
    sum++;


  for (int i = 0; i <= 26; i++)
    sum += count_all (root -> children[i]);


  return sum;

}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
  // Function's prototype
  bool free_all (node *root);

  // Don't use the head of trie to itterate
  node *traverse = ROOT;

  return free_all(traverse);

}

bool free_all (node *root)
{


  if ( !root ) // OR root == NULL
    return false;

  for (int i = 0; i <= 26; i++)
    free_all (root -> children[i]);

  free(root);
  return true;
}



/**
 * To make sure that the character would be put in
 * its rightful place in children[i] node array and
 * since children[i] starts from zero therefore we
 * need to subtract 65 ( ASCII character: 'A') or
 * 97 ( ASCII character:'a') from the character or
 * simply return it if it's a apostrophe (')
 * and if it's none of the above case then simply
 * return -1
  */
int char_position (char c)
{


  if (c == '\'')
    return 26;

  // If it's upper case
  else if( c >= 'A' && c <= 'Z')
    return c - 'A';

  // If it's lower case
  else if (c >= 'a' && c <= 'z')
    return c - 'a';

  // If the char is out of place
  else
    return -1;

}

/**
 * Create a new node
 */
node *create_node (void)
{
  node *new_node = (node *) malloc ( node_size );

  if (!new_node)
    return NULL;

  // fill up the children with NULL
  for (int i = 0; i <= 26; i++)
    new_node -> children[i] = NULL;

  // There is no character yet in this new node so it's false
  new_node -> is_word = false;

  return new_node;
}