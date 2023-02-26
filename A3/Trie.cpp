/**
 * @file Trie.cpp
 * @author Robert Li u1212360
 * @brief CS 3505 Assignment 03, The Trie class should have a root node, 
 * where nodes have internal storage for branches of the Trie and a flag 
 * determining whether or not that node represents the end of a valid word
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string>
#include <vector>
#include "Trie.h"
using namespace std;

///////////////////
//Rule of Three///
//////////////////

/**
 * @brief default constructor
 * 
 */
Trie::Trie()
{
	validWord = false;
}

/**
 * @brief Destroy the Trie:: Trie object
 * 
 */
Trie::~Trie()
{
	for (int i = 0; i < branchLimit; i++)
	{
		delete branches[i];
	}
}

/**
 * @brief copy a new Trie:: Trie object
 * 
 * @param other 
 */
Trie::Trie(const Trie &other)
{
	validWord = other.validWord;
	for (int i = 0; i < branchLimit; i++)
	{
		if (other.branches[i])
		{
			branches[i] = new Trie(*(other.branches[i]));
		}
	}
}

/**
 * @brief an assignment= operator using the approaches from the Rule-Of-Three slides
 * 
 * @param other 
 * @return Trie& 
 */
Trie &Trie::operator=(Trie other)
{
	for (int i = 0; i < branchLimit; i++)
	{
		swap(branches[i], other.branches[i]);
	}
	swap(validWord, other.validWord);
	return *this;
}

///////////////////
//Public Method///
//////////////////

/**
 * @brief accepts a std::string and returns void. 
 * The word passed into the method should be added to the Trie object. 
 * Duplicate adds should not change the Trie. 
 * 
 * @param word 
 */
void Trie::addAWord(string word)
{
	/**
	 * @brief if the end of word return
	 * 
	 */
	if (word.length() == 0)
	{
		validWord = true;
		return;
	}
	/**
	 * @brief get rid of the first character, if not node, make new one
	 * 
	 */
	int index = int(word[0]) - 'a';
	word = word.substr(1);
	if (!branches[index])
	{
		branches[index] = new Trie;
	}
	/**
	 * @brief recursion, add value to every node.
	 * 
	 */
	branches[index]->addAWord(word);
}

/**
 * @brief accepts a std::string and returns bool. 
 * The argument is a string assumed to be made up of 
 * characters 'a'-'z'. If the word is found in the Trie, 
 * the method should return true, otherwise return false.
 * 
 * @param word 
 * @return true 
 * @return false 
 */
bool Trie::isAWord(string word)
{
	/**
	 * @brief if the end of word return
	 * 
	 */
	if (word.length() == 0)
	{
		return validWord;
	}
	/**
	 * @brief get rid of the first character, if has node, keep check
	 * every nodes 
	 */
	int index = int(word[0]) - 'a';
	word = word.substr(1);
	if (!branches[index])
	{
		return false;
	}
	else
	{
		return branches[index]->isAWord(word);
		
	}
}

/**
 * @brief accepts a std::string and returns a vector<std::string> that contains all the words 
 *  in the Trie that start with the passed in argument prefix string.
 *  If the prefix is a word, that should be included. An empty prefix 
 *  should return all words in the Trie.
 * 
 * @param prefix 
 * @return vector<string> 
 */
vector<string> Trie::allWordsStartingWithPrefix(string prefix)
{
	/**
	 * @brief get the object to store recursion value
	 * 
	 */
	vector<string> vector;
	string passedArgStr;
	/**
	 * @brief if word end, we add prefix
	 * 
	 */
	if (prefix.length() == 0)
	{
		//branch in fixed size array
		for (int i = 0; i < branchLimit; i++)
		{
			passedArgStr = char(i + 'a');
			vector = addWordToVector(vector, passedArgStr, i, prefix);
		}
	}
	else//if not, we start from first one
	{
		int node = int(prefix[0]) - 'a';
		passedArgStr = prefix[0];
		prefix = prefix.substr(1);
		vector = addWordToVector(vector, passedArgStr, node, prefix);
	}
	return vector;
}

///////////////////
//Helper Method///
//////////////////

/**
 * @brief First helper method to check if it is node, and start the recursion
 * 
 * @param wordToBeAdded 
 * @param passedArgStr 
 * @param i 
 * @param prefix 
 * @return vector<string> 
 */
vector<string> Trie::addWordToVector(vector<string> wordToBeAdded, string passedArgStr, int i, string prefix)
{
	if (!branches[i])
		return wordToBeAdded;
	else
		return recursion(wordToBeAdded, passedArgStr, i, prefix);
}


/**
 * @brief The 2nd helper method to really process the recursion process.
 * 
 * @param wordToBeAdded 
 * @param passedArgStr 
 * @param i 
 * @param prefix 
 * @return vector<string> 
 */
vector<string> Trie::recursion(vector<string> wordToBeAdded, string passedArgStr, int i, string prefix)
{
	vector<string> prefixList;
	string temp;
	if (branches[i]->validWord)
	{
		wordToBeAdded.push_back(passedArgStr);
	}
	prefixList = branches[i]->allWordsStartingWithPrefix(prefix);
	while (prefixList.empty() == false)
	{
		temp = prefixList.back();
		prefixList.pop_back();
		temp.insert(0, passedArgStr);
		wordToBeAdded.push_back(temp);
	}
	return wordToBeAdded;
}
