#ifndef TRIE_H
#define TRIE_H

/*
* CS 3505 Assignment 3:
*   The head file for the Trie class.  
*
* Author: Wenlin Li && Robert Li
*/

#include <vector>
#include <string>
#include <map>

using namespace std;

class Trie {
    /*
    * Node class for Trie
    */
    class Node
    {  
    public:
        map<char, Node> children;
        bool isWord;
        // default constructor      
        Node()
        {
            isWord = false;
        }
    };
private:
    map<char, Node> root;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    /**
     * Helper method for allWordsStartingWithPrefix to look for all the children node push into vector
     */
    void searchWords(string& prefix, Node node, vector<string>& wordVector, string wordString);

public:
    bool validWord;

    Trie();
    /**
     * The word passed into the method should be added to the Trie object.
     */
    void addAWord(string word);
    /**
     * If the word is found in the Trie, the method should return true, otherwise return false.
     */
    bool isAWord(string word);
    /**
     * Returns a vector<std::string> that contains all the words in the Trie that start with the passed in argument prefix string. 
     */
    vector<string> allWordsStartingWithPrefix(string prefix);
    
};

#endif