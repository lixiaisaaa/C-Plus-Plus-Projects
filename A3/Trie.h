/**
 * @file Trie.h
 * @author Robert Li u1212360
 * @brief The Trie class should have a root node, where nodes have internal storage 
 * for branches of the Trie and a flag determining whether or not that node represents the end of a valid word.
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TRIE_H
#define TRI_H
#include <string>
#include <vector>
using namespace std;
class Trie {
	/**
	 * @brief private members to help public function works
	 * 
	 */
	private:
		const int branchLimit = 26;
		Trie* branches[26] = {};
		bool validWord;
		vector<string> addWordToVector(vector<string> wordToBeAdd, string passedArgStr, int i, string prefix);
		vector<string> recursion(vector<string> wordToBeAdd, string passedArgStr, int i, string prefix);
	/**
	 * @brief main functions to implement the tries.
	 * 
	 */
	public:
		Trie();
		~Trie();
		Trie(const Trie& other);
		Trie& operator=(Trie other);
		void addAWord(string word);
		bool isAWord(string word);
		vector<string> allWordsStartingWithPrefix(string prefix);
};
#endif