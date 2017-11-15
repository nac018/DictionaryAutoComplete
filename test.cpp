/* Authors      : Hoi Wa Ng
 * 		  Nang Chen
 * Date         : 21/10/2017
 * PID          : cs100fcf
 * 		  cs100fao
 * Description  : Tester file to test the insert, find of different data 
 * structures. It also tests the predictCompletion method.
 * Assignment # : PA2
 */


#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<fstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  
  DictionaryBST d_bst2;
  DictionaryHashtable d_ht2;
  DictionaryTrie dt2;

  int t_bst, t_ht, tt;
  
  //insert words
  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  words.push_back("harry potter");
  words.push_back("giant");
  words.push_back("google");
  words.push_back("goggle");
  words.push_back("vim");
  words.push_back("hover");

  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;
  
  //find test cases
  if(dt.find("harry potter")){
    cout << "harry potter exists!" << endl;
  } else {
    cout << "harry potter does not exist!" << endl;
  }

  if(dt.find("sahoo")){
    cout << "sahoo exists!" << endl;
  } else {
    cout << "sahoo does not exist!" << endl;
  }

  if(dt.find("Harry")){
    cout << "Harry exists!" << endl;
  } else {
    cout << "Harry does not exist!" << endl;
  }

  //extra insert test case
  if(dt.insert("PARTY", 777)){
    cout << "PARTY inserted!" << endl;
  } else {
    cout << "PARTY can't be inserted!" << endl;
  }

  ifstream read("freq_dict.txt");
  
  //load freq_dict.txt with BST
  Utils::load_dict(d_bst, read);
  read.close();

  read.open("freq_dict.txt");
  cout << "successfully loaded words from freq_dict.txt \n";
  //load freq_dict.txt with Hashtable
  Utils::load_dict(d_ht, read);
  read.close();

  read.open("freq_dict.txt");
  cout << "successfully loaded words from freq_dict.txt \n";
  //load freq_dict.txt with Trie
  Utils::load_dict(dt2, read);

  cout << "successfully loaded words from freq_dict.txt \n";
  read.close();
  

  int num_completion;
  std::string prefix;
  //read prefix and number of completion
  std::vector<std::string> topWords;
  std::cout << "Enter the prefix: " << endl;
  std::getline(cin,prefix);
  std::cout << "Enter the number of completion: " << endl;
  std::cin>>num_completion;
  //
  topWords = dt2.predictCompletions(prefix, num_completion);

  cout <<"Top completions are: " << endl;
  for (int i = 0; i < (int) topWords.size(); i++) {
     std::cout << topWords.at(i) << endl;
  }
/*You are supposed to add more test cases in this file */
  
  return 0;
}
