#include "util.h"
#include "DictionaryBST.h"
#include <set>

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
   return mydict.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
   
   if (mydict.find(word) == mydict.end()) {
      return false;
   }
   return true;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
	mydict.clear();
}
