# Name: Wenlin Li and Robert Li
# Class: CS3505
# A4: Makefile compiler

CC = g++
CFLAGS = -Wall -std=c++11
GOOGLETEST = ../googletest/googletest

TrieTests: Trie.o TrieTests.o
	$(CC) $(CFLAGS) -o TrieTests TrieTests.o Trie.o -I$(GOOGLETEST)/include -L$(GOOGLETEST)/lib -lgtest -lgtest_main -lpthread
Trie.o: Trie.cpp Trie.h
	$(CC) $(CFLAGS) -c Trie.cpp -I$(GOOGLETEST)/include
TrieTests.o: TrieTests.cpp Trie.h
	$(CC) $(CFLAGS) -c TrieTests.cpp -I$(GOOGLETEST)/include
clean:
	rm -f *.o TrieTests
test: TrieTests
	./TrieTests