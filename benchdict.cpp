/* Author       : Hoi Wa Ng
 * 		  Nang Chen
 * Date         : 21/10/2017
 * PID          : cs100fcf
 * 		  cs100fao
 * Description  : This class searches a hundred words through the shuffled 
 * 		  dictionary. It utilizes three different data structures 
 * 		  (BST,HT,MWT) and calculate the time to searches these 
 * 		  words over our inputed size dictionary
 * 
 * Assignment # : PA2
 */


#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"

#define HUNDRED 100
using namespace std;

int main(int argc, char** argv) 
{

  if ( argc < 5 || argc > 5) {
     std::cerr << "illegal arguments entered" << std::endl;
     return 1;
  }

  int min_size = atoi(argv[1]);
  int step_size = atoi(argv[2]);
  int num_iterations = atoi(argv[3]);

  std::vector<std::string> word_BST;
  std::vector<std::string> word_Hashtable;
  std::vector<std::string> word_Trie;

  long long runTime_BST;
  long long runTime_Hashtable;
  long long runTime_Trie;

  Timer clock_BST;
  Timer clock_Hashtable;
  Timer clock_Trie;

  auto bst = new DictionaryBST();
  auto bh = new DictionaryHashtable();
  auto bt = new DictionaryTrie();

  //BST
  
  std::cout << "Benchmarking BST dictionary..." << std::endl;
  
  for (int i = 0; i < num_iterations; i++) {
     ifstream file1(argv[4]);
     //load dictionary to bst
     Utils::load_dict(*(bst), file1, min_size + (i*step_size));
     //EOF CHECK	
     if (file1.eof()){
	std::cout << "input size exceeds the size of dictionary \n";
     }
     file1.close();
     
     ifstream file2(argv[4]);
     //load next hundred words to the bst vector
     Utils::load_vector(word_BST, file2, min_size+ (i*step_size) + HUNDRED);
     //EOF CHECK
     if (file2.eof()){
	std::cout << "input size exceeds the size of dictionary \n";
     }

     file2.close();
     //start the timer
     clock_BST.begin_timer();
     for (int j = min_size+(i*step_size); j < min_size 
	+ (i*step_size) + HUNDRED; j++) {
	(void) bst->find(word_BST.at(j));
     }
     //get the time of the find method
     runTime_BST = clock_BST.end_timer();

     //print out size and runtime
     cout << min_size + (i*step_size) << "\t";
     cout << runTime_BST << "\n";
  }

  //Hashtable

  std::cout << "Benchmarking Hashtable dictionary..." << std::endl;
  
  for (int i = 0; i < num_iterations; i++) {
     ifstream file3(argv[4]);
     //load dictionary to hashtable
     Utils::load_dict(*(bh), file3, min_size + (i*step_size));
     //EOF CHECK
     if (file3.eof()){
        std::cout <<"[input size exceeds the size of dict]\n";
     }
     file3.close();
     
     ifstream file4(argv[4]);
     //load next hundred words to the hashtable vector
     Utils::load_vector(word_Hashtable, file4, min_size+ (i*step_size) + HUNDRED);
     //EOF CHECK
     if (file4.eof()){
        std::cout << "[input size exceeds the size of dict]\n";
     }
     file4.close();
     //start the timer
     clock_Hashtable.begin_timer();
     for (int j = min_size+(i*step_size); j < min_size 
	+ (i*step_size) + HUNDRED; j++) {
	(void) bh->find(word_Hashtable.at(j));
     }
     //get the time of the find method
     runTime_Hashtable = clock_Hashtable.end_timer();

     //print out size and runtime
     cout << min_size + (i*step_size) << "\t";
     cout << runTime_Hashtable << "\n";
  }

  	
  //Trie

  std::cout << "Benchmarking Trie dictionary..." << std::endl;
  
  for (int i = 0; i < num_iterations; i++) {
     ifstream file5(argv[4]);
     //load dictionary to MWT
     Utils::load_dict(*(bt), file5, min_size + (i*step_size));
     //EOF CHECK
     if (file5.eof()){
        std::cout << "[input size exceeds the size of dict]\n";
     }
     file5.close();
     
     ifstream file6(argv[4]);
     //load next hundred words to the MWT vector
     Utils::load_vector(word_Trie, file6, min_size+ (i*step_size) + HUNDRED);
     //EOF CHECK
     if (file6.eof()){
        std::cout << "[input size exceeds the size of dict]\n";
     }
     file6.close();

     //start the timer
     clock_Trie.begin_timer();
     for (int j = min_size+(i*step_size); j < min_size 
	+ (i*step_size) + HUNDRED; j++) {
	(void) bt->find(word_Trie.at(j));
     }
     //get the time of the find method
     runTime_Trie = clock_Trie.end_timer();

     //print out size and runtime
     cout << min_size + (i*step_size) << "\t";
     cout << runTime_Trie << "\n";
  }

  //delete object on heap
  delete bst;
  delete bh;
  delete bt;

  return 0;
}  
