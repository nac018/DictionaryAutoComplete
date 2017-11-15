/* Author       : Hoi Wa Ng
 * 		  Nang Chen
 * Date         : 21/10/2017
 * PID          : cs100fcf
 * 		  cs100fao
 * Description  : This cpp class define a Dictionary class, which uses the
 * 		  Hashtable as its data structure to store words.
 * Assignment # : PA2
 */


#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
   return myHash.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
   if ( myHash.find(word) == myHash.end()) {
      return false;
   }
   return true;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
	myHash.clear();
}
