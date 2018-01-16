# Speller

It takes a dictionary text of one liner words and a text file to check how many misspelled words are in the text. The dictionary text will be put into a trie data structure.
with each node points to another trie of 26 nodes and if the that particular children node is the end of the word then the is_word will become true.

For more information check out [CS50 Speller](https://docs.cs50.net/problems/speller/speller.html) 


## Getting Started


### Prerequisites

* clang
* make

### Compilation

Compile it with make 

Open your terminal and navigate to speller directory:

```
$ make
```

## Running the speller

Run it like this:

```
$ ./speller dictionaries/large texts/alice.txt
```

### Break down

./speller: is the name of the program that you are running

dictionaries/large: is one of the dictionaries that are necessary for running speller

texts/alice.txt: is the text file that speller checks for any misspelling words

