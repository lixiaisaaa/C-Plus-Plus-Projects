/**
 * @file TrieTest.cpp
 * @author Robert Li u1212360
 * @brief  a test program TrieTest.cpp that exercises Trie.cpp
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Trie.h"
using namespace std;

int main(int argc, char *argv[])
{
	/**
	 * @brief get the args for files
	 * 
	 */
	Trie firstNode;
	string testWord;
	ifstream wordsFile(argv[1]);
	ifstream queriesFile(argv[2]);
	vector<string> vectors;

	/**
 * @brief test words
 * 
 */
	if (wordsFile.is_open())
	{
		while (getline(wordsFile, testWord))
		{
			firstNode.addAWord(testWord);
		}
		wordsFile.close();
	}

	/**
    * @brief Test queries
    * 
    */
	
	Trie copy_root = firstNode;
	if (queriesFile.is_open())
	{
		while (getline(queriesFile, testWord))
		{
			if (firstNode.isAWord(testWord))
			{
				cout << testWord << " is found" << endl;
			}
			else
			{
				cout << testWord << " word is not found, did you mean:" << endl;
				vectors = firstNode.allWordsStartingWithPrefix(testWord);
				if (vectors.empty())
				{
					cout << " no alternatives found" << endl;
				}
				for (string word : vectors)
				{
					cout << word << endl;
				}
			}
		}
		queriesFile.close();
	}
	
	//Rule of Three Test
	Trie trie;
	Trie other(trie);
	other = trie;
}