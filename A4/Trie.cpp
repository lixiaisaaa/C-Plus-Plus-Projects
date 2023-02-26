/*
* CS 3505 Assignment 3: 
*   Practice the C++ by implementing by design the trie.
* Trie.cpp Description:
*     The Trie class should have a root node, 
*        where nodes have internal storage for branches of the Trie 
*       and a flag determining whether or not that node represents the end of a valid word.
*
* Author: Wenlin Li && Robert Li
*/
#include "Trie.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief default constructor
 * 
 */
Trie::Trie() {
    validWord = false;
    Node newNode;
    root[97] = newNode;
}

/**
 * @brief accepts a std::string and returns void. 
 * The word passed into the method should be added to the Trie object. 
 * Duplicate adds should not change the Trie. 
 * 
 * @param word 
 */
void Trie::addAWord(string word) {
    //if the end of word return
	if (word.length() == 0)
	{
		return;
	}
    //create a iterator for root
    map<char, Node>::iterator it = root.begin();
    
    for(unsigned int i = 0; i < word.length(); i++) {
        //get every char in the word
        char wordChar = word[i];
         
        if (it->second.children.find(wordChar) == it->second.children.end()) {  
            //get rid of the first character, if not node, make new one
            Node newNode;        
            it->second.children[wordChar] = newNode;
        }
        it = it->second.children.find(wordChar);
    }
    //mark the node is a word
    it->second.isWord = true;
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
bool Trie::isAWord(string word) {
    //if the end of word return
	if (word.length() == 0)
	{
		return validWord;
	}
    map<char, Node>::iterator it = root.begin();
    for(unsigned int i = 0; i < word.length(); i++) {
        //get every char in the word
        char wordChar = word[i];
        //get rid of the first character, if has node, keep check every nodes 
        if(it->second.children.find(wordChar) == it->second.children.end()) {
            return false;
        }
        it = it->second.children.find(wordChar);
    }
    //return if it is a word
    return it->second.isWord;
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
vector<string> Trie::allWordsStartingWithPrefix(string prefix) {
    //get the object to store recursion value
    vector<string> wordVector;
    map<char, Node>::iterator it = root.begin();
    for(unsigned int i = 0; i < prefix.length(); i++) {
        char prefixChar = prefix[i];
        // if word end, we return the word verctor
        if(it->second.children.find(prefixChar) == it->second.children.end()) {
            return wordVector;
        }
        it = it->second.children.find(prefixChar);
    }
    // use word string to store every char and finally add them with prefix
    string wordString = "";
    // Recursively to find the words with node;
    searchWords(prefix, it->second, wordVector, wordString);
    return wordVector;
}


/**
 * @brief Helper method to check if it is node, 
 * and start the recursion and add them into the word string.
 * 
 * @param prefix 
 * @param node 
 * @param wordVector 
 * @param wordString 
 *
 */
void Trie::searchWords(string& prefix, Node node, vector<string>& wordVector, string wordString) {
    //If the node is end, put all the word with prefix into vector
    if(node.isWord) {
        wordVector.push_back(prefix + wordString);
    }
    // Recursively to find the words with node;
    for(unsigned int i = 0; i < alphabet.length(); i++) { 
        if (node.children.find('a' + i) != node.children.end())
        {
            searchWords(prefix, node.children.find('a' + i)->second, wordVector, wordString + alphabet[i]);
        }
    }
}


