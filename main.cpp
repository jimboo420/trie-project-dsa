#include "Trie.h"
#include <iostream>

using namespace std;

int main() {
    Trie trie;

    // Insert words
    trie.insert("hello");
    trie.insert("world");
    trie.insert("hell");
    trie.insert("heaven");

    // Search for words
    cout << "Search 'hello': " << (trie.search("hello") ? "Found" : "Not Found") << endl;
    cout << "Search 'world': " << (trie.search("world") ? "Found" : "Not Found") << endl;
    cout << "Search 'hell': " << (trie.search("hell") ? "Found" : "Not Found") << endl;
    cout << "Search 'heaven': " << (trie.search("heaven") ? "Found" : "Not Found") << endl;
    cout << "Search 'help': " << (trie.search("help") ? "Found" : "Not Found") << endl;

    // Delete a word
    trie.deleteWord("hell");
    cout << "After deleting 'hell', search 'hell': " << (trie.search("hell") ? "Found" : "Not Found") << endl;

    return 0;
}