/**
 * @file TrieTests.cpp
 * @author Robert Li and WenLin Li
 * @brief This is a unit test class for googletest on A4 for refactoring.
 * @version 0.1 implemented basic tests.
 *          0.2 added some edged situation and debugged from failed test
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gtest/gtest.h"
#include "Trie.h"

using namespace std;

/**
 * @brief Construct a test make sure the addAWord works
 * 
 */
TEST(AddAWordTest, AddWordsBasic) {
  Trie t;
  t.addAWord("");
  t.addAWord("robert");
  t.addAWord("wenlin");
  t.addAWord("midterm");
}

/**
 * @brief Construct Test addAWord empty cases
 * 
 */
TEST(AddAWordTest, EmptyTrie) {
  Trie t;
  t.addAWord("robert");
  t.addAWord("wenlin");
  t.addAWord("");
  ASSERT_FALSE(t.isAWord(""));
}


/**
 * @brief Construct Test addAWord with duplicate inputs
 * 
 */
TEST(AddAWordTest, HandlesDuplicateInput) {
  Trie t;
  t.addAWord("robert");
  t.addAWord("robbt");
  t.addAWord("wenlin");
  t.addAWord("robert");
  ASSERT_TRUE(t.isAWord("robert"));
}

/**
 * @brief Construct Test isAWord basic
 * 
 */
TEST(IsaWordTest,IsWordBasic){
  Trie t;
  t.addAWord("midterm");
  ASSERT_TRUE(t.isAWord("midterm"));
}

/**
 * @brief Construct Test isAWord correct determine the words
 * 
 */
TEST(IsAWordTest, HandlesBasicInput) {
  Trie t;
  t.addAWord("robert");
  ASSERT_TRUE(t.isAWord("robert"));
  ASSERT_FALSE(t.isAWord("wenlin"));
 
}

/**
 * @brief Construct Test isAWord avoid empty
 * 
 */
TEST(IsAWordTest, TestAddAWord) {
  Trie t;
  ASSERT_FALSE(t.isAWord("robert"));
  t.addAWord("robert");
  ASSERT_TRUE(t.isAWord("robert"));
}

// Test EmptyPrefix
TEST(PrefixTest, EmptyPrefixTest) {
  Trie t;
  vector<string> words;
  ASSERT_EQ(t.allWordsStartingWithPrefix(""), words);
}

/**
 * @brief Construct basic prefix test
 * 
 */
TEST(PrefixTest, BasicTestPrefix) {
  Trie t;
  vector<string> words;
  t.addAWord("r");
  t.addAWord("rubber");
  t.addAWord("robert");
  t.addAWord("wenlin");
  t.addAWord("when");
  t.addAWord("midterm");
  t.addAWord("mormon");
  words.push_back("r");
  words.push_back("robert");
  words.push_back("rubber");
  ASSERT_EQ(t.allWordsStartingWithPrefix("r"), words);
}


/**
 * @brief Construct test for all same words pushed back.
 * 
 */
TEST(PrefixTest, allSamePrefixTest) {
  Trie t;
  vector<string> words;
  t.addAWord("robert");
  t.addAWord("midterm");
  t.addAWord("wenlin");
  words.push_back("midterm");
  words.push_back("robert");
  words.push_back("wenlin");

  ASSERT_EQ(t.allWordsStartingWithPrefix(""), words);
}

/**
 * @brief Construct a test for inapporiate prefix situation
 * 
 */
TEST(PrefixTest, InapporiatePrefix) {

  vector<string> words;
  Trie t;
  t.addAWord("midterm");
  t.addAWord("robert");
  t.addAWord("Wenlin");


  ASSERT_EQ(t.allWordsStartingWithPrefix("lplchampion"), words);
}

/**
 * @brief Construct a test for duplicated situation
 * 
 */
TEST(PrefixTest, DuplicatedPrefix) {
  Trie t;
  vector<string> words;
  t.addAWord("robert");
  t.addAWord("robert");
  t.addAWord("midterm");
  t.addAWord("midterm");
  t.addAWord("wenlin");
  words.push_back("midterm");
  words.push_back("robert");
  words.push_back("wenlin");

  ASSERT_EQ(t.allWordsStartingWithPrefix(""), words);
}

