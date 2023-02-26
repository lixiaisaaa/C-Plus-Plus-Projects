CC = g++
CFLAGS = -Wall --std=c++11
INCLUDE = .


TrieTest: Trie.o TrieTest.o
	$(CC) $(CFLAGS) -o TrieTest Trie.o TrieTest.o

Trie.o: Trie.cpp Trie.h
	$(CC) $(CFLAGS) -c Trie.cpp -I$(INCLUDE)

TrieTest.o: TrieTest.cpp
	$(CC) $(CFLAGS) -c TrieTest.cpp -I$(INCLUDE)
	
clean:
	rm TrieTest *.o 