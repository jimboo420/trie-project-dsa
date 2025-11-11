#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
    void deleteTrie(TrieNode* node);
    bool deleteHelper(TrieNode* node, const string& word, int index);
    void collectWords(TrieNode* node, string current, vector<string>& words);

public:
    Trie();
    ~Trie();
    void insert(const string& word);
    bool search(const string& word);
    void deleteWord(const string& word);
    vector<string> getWordsWithPrefix(const string& prefix);
};

#endif