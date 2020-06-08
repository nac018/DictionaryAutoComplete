#include "util.h"
#include "DictionaryTrie.h"

Node::Node(){
  wordNode = false;
  for(int i = 0; i < ARRAY_SIZE; ++i) {
     this->childptr[i] = NULL;
  }
  this->setFrequency(0);
}

void Node::setFrequency(int freq){
   this->frequency = freq;
}

unsigned int Node::getFrequency(){
   return this->frequency;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){ root = nullptr;  }

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  //return false if empty string
  if ( word.length() == 0) {
     return false; 
  }

  // base case when there's no element in trie
  if ( root == nullptr) {
     root = new Node();
     Node* current = root;
     for (int i = 0; i < (int)word.length(); i++ ) {
	if ( word.at(i) == ' ') {
	   //we are changing space into "{" ("{" has value 123)
           word.replace(i,1,"{");
        }
        if ( word.at(i) < ALPHABET_OFFSET || word.at(i) > (ALPHABET_OFFSET
	   + SPACE_INDEX))  {
	   return false;
        }

	int index = word.at(i) - ALPHABET_OFFSET;

        Node* newHost = new Node();
	current->childptr[index] = newHost;
	current = newHost;
     }
     current->setFrequency(freq);
     current->wordNode = true;
     return true;
  }

  // general cases
  Node* current = root;
  for (int j = 0; j < (int)word.length(); j++){
     if ( word.at(j) == ' ') {
	//we are changing space into "{" ("{" has value 123)
        word.replace(j,1,"{");
     }
     if ( word.at(j) < ALPHABET_OFFSET || word.at(j) > (ALPHABET_OFFSET
	 + SPACE_INDEX))  {
	return false;
     }

     int index = word.at(j) - ALPHABET_OFFSET;
     
     //first case: if childptr[index] already had ptr
     if( current->childptr[index] != nullptr ) {
	current = current->childptr[index];
     }
     else
     {  //second case: if childptr[index] is empty
        Node* newHost = new Node();
	current->childptr[index] = newHost;
	current = newHost;
     }
  }
  //check if the word is duplicate
  if ( current->wordNode == true) {
     if ( freq >= current->getFrequency() ) {
	current->setFrequency(freq);
     }
     return false;
  }
  current->wordNode = true;
  current->setFrequency(freq);
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  //return false right away if word is empty
  if ( (int) word.length() == 0) {
     return false; 
  }


  //if the trie is empty, return false
  if ( root == nullptr) {
     return false;
  }

  Node* current = root;
  for ( int i = 0; i < (int) word.length(); i++){
     if ( word.at(i) == ' '){
        word.replace(i,1,"{");
     }

     if ( word.at(i) < ALPHABET_OFFSET || word.at(i) > (ALPHABET_OFFSET
	 + SPACE_INDEX))  {
	return false;
     }
     
          int index = word.at(i) - ALPHABET_OFFSET;
 
     if( current->childptr[index] == nullptr) {
	return false;
     }
     current = current->childptr[index];
     
     /*if ( word.at(i) == '{') {
        word.replace(i,1," ");
     }*/
  }
  if( current->wordNode == true) {
     return true;
  }
  return false;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
 unsigned int num_completions)
{
  std::vector<std::string> words;    //to store up to num_completions top word
  if ((num_completions <= 0) || (int)(prefix.length() == 0)) {
	return words;	
  }
  std::vector<std::pair<std::string,int>> allWords;  //to store all Word pair
  Node* current = root;

  //traverse throught the path that represent the prefix
  for ( int i = 0; i < (int) prefix.length(); i++){
    if ( prefix.at(i) == ' '){
       if( current->childptr[SPACE_INDEX] == nullptr){
	  return words;       //return empty vector
       }
       current = current->childptr[SPACE_INDEX];
    }
    else
    {
      int index = prefix.at(i) - ALPHABET_OFFSET;
 
      if( current->childptr[index] == nullptr) {
  	  return words;       //return empty vector
      }
      current = current->childptr[index];
    }
  }
  // case if the prefix itself is a valid word
  if (current->wordNode == true) {
    std::pair<std::string,int> npair (prefix, current->getFrequency());
    allWords.push_back(npair);
  }

  //start searching all the possible words
  for ( int j = 0; j < ARRAY_SIZE; j++) {
     if ( current->childptr[j] != nullptr) {
	std::string str = prefix;
        if (j == SPACE_INDEX) {
	   str.append(1, ' ');
        } else {
           str.append(1, j+ ALPHABET_OFFSET);
        }
        predictHelper(str, current->childptr[j], &allWords);
     }
  }

  //start sorting the list of all possible words
  std::sort(allWords.begin(), allWords.end(),sortbysec);

  //if num_completions > size of allWords vector, return up to the size of it
  int topWords = num_completions;
  if (num_completions > allWords.size()) {
    topWords = (int) (allWords.size());
  }

  for (int i = 0; i < topWords;i++) {
     words.push_back(allWords.at(i).first);
     
     if (i == topWords -1) {
        while ( i+1 < (int)allWords.size() &&
           (allWords.at(i).second == allWords.at(i+1).second)) {
	   words.push_back(allWords.at(i+1).first);
           i++;
        }
     }
  }
  
  return words;
}

/* A helper method for predictCompletion() to recurssively
 * search throught the whole tries so to find all possible
 * words
 */
void DictionaryTrie::predictHelper(std::string prefix,
 Node* current, std::vector<std::pair<std::string,int>> *allWords)
{
   // check if the current prefix is a word already
   if ( current->wordNode == true ) {
     std::pair<std::string,int> npair (prefix, current->getFrequency());

     allWords->push_back(npair);
   }

   for ( int i = 0; i < ARRAY_SIZE; i++){
     if ( current->childptr[i] != nullptr) {	
	std::string str = prefix;
        if ( i == SPACE_INDEX){ //replace the '{' back to space
           str.append(1,' ');
        } else {
	   str.append(1, i+ ALPHABET_OFFSET);
        }
	predictHelper(str,current->childptr[i], allWords);
     }
   }
}

/* A compare function to help sort() method sort the element
 * in descending order
 */
  bool sortbysec(const std::pair<std::string,int> &a,
              const std::pair<std::string,int> &b){
   return (a.second > b.second);
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
}
/*  */
void DictionaryTrie::deleteAll(Node* current){
	if (current == nullptr){
		return;
	}
	for (int i = 0; i < ARRAY_SIZE; i++){	
		Node* curr = current->childptr[i];
		deleteAll(curr);
	}
	delete current;
	current = nullptr;
}

