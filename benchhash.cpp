#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define ALPHABET_SIZE 26

using namespace std;

//first hash function
unsigned int QuickHashing(std::string key, int tableSize) {
  unsigned int sum = 0;
  for (int i = 0; i < (int)key.length(); i++)
    sum = sum + key.at(i);
  return  sum % tableSize;
}

//second hash function
unsigned int UniqueHashing(std::string key, int tableSize){
  unsigned int seed = 121;
  unsigned long sum = 0;
  for(int i = 0; i < (int)key.length(); i++)
   {
      sum = (sum * seed) + key.at(i);
   }
   return sum % tableSize;
}

int main(int argc, char**argv) {
   
  // test with the accuracy of hash function with three different 
  // inputs and table sizes
  std::string word = "Hello";
  int tablesize = 10;
  unsigned int hashVal1 = QuickHashing(word, tablesize);
  unsigned int hashVal2 = UniqueHashing(word, tablesize);

  cout << "Hash Testing: \n";

  cout << "QuickHashing gives <Hello> value: " << hashVal1 << std::endl;
  cout << "UniqueHashing gives <Hello> value: " << hashVal2 << std::endl;
  cout << std::endl;

  word = "Whatever...";
  tablesize = 20;
  hashVal1 = QuickHashing(word, tablesize);
  hashVal2 = UniqueHashing(word, tablesize);

  cout << "QuickHashing gives <Whatever...> value: " << hashVal1 << std::endl;
  cout << "UniqueHashing gives <Whatever...> value: " << hashVal2 << std::endl;
  cout << std::endl;

  word = "sleep late";
  tablesize = 30;
  hashVal1 = QuickHashing(word, tablesize);
  hashVal2 = UniqueHashing(word, tablesize);

  cout << "QuickHashing gives <sleep late> value: " << hashVal1 << std::endl;
  cout << "UniqueHashing gives <sleep late> value: " << hashVal2 << std::endl;
  cout << std::endl;

  //then test with the hits and step comparison
  ifstream dictfile(argv[1]);
  int num_words = atoi(argv[2]);

  //implement table size twice as the input of the number of words
  int tableSize = num_words * 2;

  //create vector
  std::vector<std::string> allWords;
  unsigned int hash[tableSize];
  std::memset(hash,0,tableSize*sizeof(int));
  //load file to the vector
  Utils::load_vector(allWords, dictfile, num_words);

  //increment the count of hashes on each index on the table
  for ( int i = 0; i < num_words; i++){
     hash[QuickHashing(allWords.at(i),tableSize)]++;
  }

  //increment the count of hits on each index on the table
  int hits[tableSize];
  std::memset(hits,0,tableSize*sizeof(int));

  for ( int i = 0; i < tableSize; i++) {
     if ( hash[i] == 0) {
	hits[0]++;
     } else {
        int index = hash[i]-1;
        hits[index]++;
     }
  }

  cout << "Printing the statistics for QuickHashing with hash table size "
      << tableSize << std::endl;
  cout << std::endl;

  int num_steps = 0;
  int num_hits = 0;
  int num_worst = 0;

  //calculate the required statistics for the hits and slots 
  cout << "#hits #slots receiving the #hits" << std::endl;
  for ( int i =0; i < tableSize; i++){
     if (hits[i] != 0) {
      cout << i << "\t" << hits[i] << std::endl;
      if (i == 0) {
        num_steps++;
      }
      num_steps += i;
      num_hits++;
      if (i > num_worst) {
        num_worst = i;
      }
    }
  }

  //calculate the average steps to a successful search
  float avg_steps = (float) (num_steps) / (float) (num_hits);

  //print all the stats
  cout << "The average number of steps for a successful search for " 
      "QuickHashing would be " << avg_steps << std::endl;
  cout << std::endl;

  cout << "The worst case steps that would be needed to find a word is " <<
      num_worst << std::endl;
  cout << std::endl;

  cout << "Printing the statistics for UniqueHashing with hash table size "
       << tableSize << std::endl;

  cout << std::endl;

  //printing the stats for second hash function, same implementation as above
  std::vector<std::string> allWords2;
  unsigned int hash2[tableSize];
  memset(hash2,0,tableSize*sizeof(int));

  Utils::load_vector(allWords2, dictfile, num_words);
  for ( int i = 0; i < num_words; i++){
     hash2[UniqueHashing(allWords2.at(i),tableSize)]++;
  }

  int hits2[tableSize];
  memset(hits2,0,tableSize*sizeof(int));

  for ( int i = 0; i < tableSize; i++) {
     if ( hash2[i] == 0) {
	hits2[0]++;
     } else {
        int index = hash2[i]-1;
        hits2[index]++;
     }
  }


  int num_steps2 = 0;
  int num_hits2 = 0;
  int num_worst2 = 0;

  cout << "#hits #slots receiving the #hits" << std::endl;
  for ( int i =0; i < tableSize; i++){
     if (hits2[i] != 0) {
      cout << i << "\t" << hits2[i] << std::endl;
      if (i == 0) {
        num_steps2++;
      }
      num_steps2 += i;
      num_hits2++;
      if (i > num_worst2) {
        num_worst2 = i;
      }
    }
  }

  float avg_steps2 = (float) (num_steps2) / (float) (num_hits2);

  cout << "The average number of steps for a successful search for " 
      "UniqueHashing would be " << avg_steps2 << std::endl;
  cout << std::endl;

  cout << "The worst case steps that would be needed to find a word is " <<
      num_worst2 << std::endl;
  cout << std::endl;

 
  return 0; 
}
