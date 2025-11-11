#include "Trie.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

void displayPrefixStats(const vector<string>& words, const string& prefix) {
    if (words.empty()) {
        cout << "No words found with prefix '" << prefix << "'" << endl;
        return;
    }

    unordered_map<char, int> firstLetterCount;
    unordered_map<int, int> lengthCount;

    cout << "Words with prefix '" << prefix << "':" << endl;
    for (const string& word : words) {
        cout << "  " << word << endl;
        if (!word.empty()) {
            firstLetterCount[word[0]]++;
            lengthCount[word.size()]++;
        }
    }

    cout << "\nStatistics for prefix '" << prefix << "':" << endl;
    cout << "Total words: " << words.size() << endl;

    cout << "\nFirst letter distribution:" << endl;
    for (const auto& pair : firstLetterCount) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }

    cout << "\nWord length distribution:" << endl;
    for (const auto& pair : lengthCount) {
        cout << "  Length " << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    Trie myTrie;

    // Belize town names dataset (sample)
    vector<string> townNames = {
        "belmopan",
        "benque",
        "corozal",
        "caye caulker",
        "ambergris caye",
        "san ignacio",
        "orange walk",
        "dangriga",
        "belize city",
        "placencia",
        "san pedro",
        "punta gorda",
        "stan creek",
        "cayo",
        "toledo"
    };

    // Insert town names into trie
    for (const string& name : townNames) {
        myTrie.insert(name);
    }

    cout << "Belize Town Names inserted into Trie." << endl;
    cout << "Enter commands (type 'help' for available commands):" << endl;

    string command;
    while (true) {
        cout << "\n> ";
        getline(cin, command);

        stringstream ss(command);
        string cmd;
        ss >> cmd;

        if (cmd == "help") {
            cout << "Available commands:" << endl;
            cout << "  search <word>     - Search for a specific word" << endl;
            cout << "  prefix <prefix>   - Get words with prefix and statistics" << endl;
            cout << "  insert <word>     - Insert a new word" << endl;
            cout << "  delete <word>     - Delete a word" << endl;
            cout << "  stats <prefix>    - Show statistics for prefix (alias for prefix)" << endl;
            cout << "  list              - List all town names in the dataset" << endl;
            cout << "  quit              - Exit the program" << endl;
        } else if (cmd == "search") {
            string word;
            ss >> word;
            if (word.empty()) {
                cout << "Usage: search <word>" << endl;
            } else {
                cout << "Searching for '" << word << "': " << (myTrie.search(word) ? "Found" : "Not Found") << endl;
            }
        } else if (cmd == "prefix" || cmd == "stats") {
            string prefix;
            ss >> prefix;
            if (prefix.empty()) {
                cout << "Usage: " << cmd << " <prefix>" << endl;
            } else {
                vector<string> words = myTrie.getWordsWithPrefix(prefix);
                displayPrefixStats(words, prefix);
            }
        } else if (cmd == "insert") {
            string word;
            ss >> word;
            if (word.empty()) {
                cout << "Usage: insert <word>" << endl;
            } else {
                myTrie.insert(word);
                cout << "Inserted '" << word << "'" << endl;
            }
        } else if (cmd == "delete") {
            string word;
            ss >> word;
            if (word.empty()) {
                cout << "Usage: delete <word>" << endl;
            } else {
                myTrie.deleteWord(word);
                cout << "Deleted '" << word << "' (if it existed)" << endl;
            }
        } else if (cmd == "list") {
            cout << "Belize town names in dataset:" << endl;
            for (const string& name : townNames) {
                cout << "  " << name << endl;
            }
        } else if (cmd == "quit" || cmd == "exit") {
            cout << "Goodbye!" << endl;
            break;
        } else if (!cmd.empty()) {
            cout << "Unknown command. Type 'help' for available commands." << endl;
        }
    }

    return 0;
}