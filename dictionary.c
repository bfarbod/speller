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


      // If this children node was never loaded with a character
      if (  traverse -> children[char_place] == NULL)
        return false;

      else
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

    // The location of each character from zero in array children[]
    int char_place = 0;
    // Don't use the head of trie to itterate
    node *traverse = NULL;



    FILE *dict_file = fopen (dictionary, "r");

    if ( dict_file == NULL)
    {
        fprintf ( stderr, "%s cannot be opened!.\n", dictionary);
        exit (1);
    }


    // Initilialize the HEAD of Trie for the first time
    // ---------------------------------------------
    // which one is better?
    ROOT = (node *) malloc (node_size);
    //ROOT = create_node();
    // ---------------------------------------------


    // to fill array with words from dictionary file
    char word [ LENGTH ] = {};
    // for not touching ROOT and doing itteration with another pointer
    traverse = ROOT;
    // to put new char into one of nodes's chldren[i]
    node *new_char = NULL;


    while ( fscanf (dict_file, "%s", word) != EOF )
    {
      //printf (">> %s\n", word);
      for (int i = 0, length = strlen(word); i < length; i++)
        {

          //printf ("Char place: %i, Char (alpha): %c\n", char_place, word[i]);

          char_place = char_position ( word[i] );

          //printf ("Char place: %i, Char (alpha): %c\n", char_place, word[i]);

          // If this children node was never loaded with a character
          if ( traverse -> children[char_place] == NULL)
            {
              // ---------------------------------------------
              // which one is better?
              new_char = (node *) malloc (node_size);
              //new_char = create_node();
              // ---------------------------------------------
              traverse -> children[char_place] = new_char;
            }

          else
            traverse = traverse -> children[char_place];

        }

     // traverse -> is_word = true;
    }

    // Close the file
    fclose (dict_file);

    /**
     * if their pointer location is equal it means that
     *  dictionary file never loaded into memory.
     */

    if ( traverse == ROOT)
      return false;
    else
      return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  // Function's prototype
  int count_all (node *root);

  // Don't use the head of trie to itterate
  node *traverse = ROOT;

  return count_all(traverse);
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
 * count all the node that has a character
 */

int count_all (node *root)
{

  int sum = 0;

  if ( !root )
    return 0;


  if ( root -> is_word )
    return 1;


  for (int i = 0; i <= 26; i++)
    sum += count_all (root -> children[i]);


  return sum;

}

/**
 * To make sure that the character would be put in
 * its rightful place in children[i] node array and
 * since children[i] starts from zero therefore we
 * need to subtract 65 ( ASCII character: 'A') or
 * 97 ( ASCII character:'a') from the character or
 * simply return it if it's a apostrophe (')
  */
int char_position (char c)
{


  if (c == '\'')
    return 26;

  // If it's upper case
  else if( c >= 'A' && c <= 'Z')
    return c - 'A';

  // If it's lower case
  else if (c >= 'a' && c <= 'a')
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