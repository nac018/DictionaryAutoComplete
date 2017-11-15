/**
 * CSE 100 PA2 C++ Autocomplete
 * Authors: Jor-el Briones, Christine Alvarado
 * Name         : Hoi Wa Ng
 * 		  Nang Chen
 * Date         : 21/10/2017
 * PID          : cs100fcf
 * 		  cs100fao
 * Description  : Header file of DictionaryTrie.h
 * Assignment # : PA2
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#define ALPHABET_OFFSET 97
#define SPACE_INDEX 26
#define ARRAY_SIZE 27

#include <vector>
#include <string>
#include <algorithm>


class Node 
{
public:
  
  /* Create a new Node that uses to store information */
  Node();

  /* Marker to note whether current node is word node or not */
  bool wordNode;  

  /* Node ptr to its possible children nodes */ 
  Node* childptr[ARRAY_SIZE];
  
  void setFrequency(int freq);

  unsigned int getFrequency();

private: 

  unsigned int frequency;

};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here
  Node * root;

  void predictHelper(std::string prefix,
  Node* current, std::vector<std::pair<std::string,int>> *allWords);   
  void deleteAll(Node* current);

  };

  bool sortbysec(const std::pair<std::string,int> &a,
              const std::pair<std::string,int> &b);
#endif // DICTIONARY_TRIE_H
