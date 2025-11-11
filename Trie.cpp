#include "Trie.h"

using namespace std;

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    deleteTrie(root);
}

void Trie::deleteTrie(TrieNode* node) {
    if (node == nullptr) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            deleteTrie(node->children[i]);
        }
    }
    delete node;
}

void Trie::insert(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) continue; // Ignore non-lowercase letters
        if (node->children[index] == nullptr) {
            node->children[index] = new TrieNode();
        }
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

bool Trie::search(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        int index = ch - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || node->children[index] == nullptr) {
            return false;
        }
        node = node->children[index];
    }
    return node->isEndOfWord;
}

void Trie::deleteWord(const string& word) {
    deleteHelper(root, word, 0);
}

bool Trie::deleteHelper(TrieNode* node, const string& word, int index) {
    if (index == word.size()) {
        if (!node->isEndOfWord) return false;
        node->isEndOfWord = false;
        return true;
    }
    int chIndex = word[index] - 'a';
    if (chIndex < 0 || chIndex >= ALPHABET_SIZE || node->children[chIndex] == nullptr) {
        return false;
    }
    bool shouldDeleteChild = deleteHelper(node->children[chIndex], word, index + 1);
    if (shouldDeleteChild) {
        delete node->children[chIndex];
        node->children[chIndex] = nullptr;
        // Check if node has no other children and is not end of another word
        bool hasChildren = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                hasChildren = true;
                break;
            }
        }
        if (!hasChildren && !node->isEndOfWord) {
            return true;
        }
    }
    return false;
}

vector<string> Trie::getWordsWithPrefix(const string& prefix) {
    vector<string> words;
    TrieNode* node = root;
    for (char ch : prefix) {
        int index = ch - 'a';
        if (index < 0 || index >= ALPHABET_SIZE || node->children[index] == nullptr) {
            return words; // Return empty vector if prefix not found
        }
        node = node->children[index];
    }
    // Now collect all words from this node
    collectWords(node, prefix, words);
    return words;
}

void Trie::collectWords(TrieNode* node, string current, vector<string>& words) {
    if (node->isEndOfWord) {
        words.push_back(current);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            collectWords(node->children[i], current + (char)('a' + i), words);
        }
    }
}