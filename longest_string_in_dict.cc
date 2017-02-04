#include <iostream>
#include <string>
using namespace std;

/* Given a string and a string dictionary, find the longest string in dictionary
 * which can be formed by deleting some characters of the given string.
 * e.g. S = "abpcplea", Dict = {"ale", "apple", "monkey", "plea"}, return "apple"
 */

struct TrieNode {
    bool is_word;
    TrieNode *children[26];
};

struct Trie {
    TrieNode *root;
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        int len = word.length();
        TrieNode *cur = root;
        for (int i = 0; i < len; i++) {
            int idx = word[i] - 'a';
            if (cur->children[idx] == NULL)
                cur->children[idx] = new TrieNode();
            cur = cur->children[idx];
        }
        cur->is_word = true;
    }

    bool search(string word) {
        int len = word.length();
        TrieNode *cur = root;
        for (int i = 0; i < len; i++) {
            if (cur == NULL) return false;
            cur = cur->children[word[i] - 'a'];
        }
        return cur && cur->is_word;
    }

    /* Doesn't work (maximal munch)
    string get_longest_substr(string word) {
        string s = "";
        string current_longest = "";
        int index = 0;
        int len = word.length();
        TrieNode *cur = root;

        while (index + current_longest.length() < len) {
            string longest = "";
            for (int i = 0; i < len; i++) {
                int idx = word[i] - 'a';
                if (cur->children[idx] == NULL) continue;
                else {
                    cur = cur->children[idx];
                    longest += word[i];
                }
            }
            if (longest.length() > current_longest.length())
                current_longest = longest;
            index++;
        }
        return current_longest;
    }
    */

    bool is_prefix(string prefix) {
        TrieNode *cur = root;
        int len = prefix.length();
        for (int i = 0; i < len; i++) {
            if (cur == NULL) return false;
            cur = cur->children[prefix[i] - 'a'];
        }
        return cur != NULL;
    }

    string get_longest_word(string prefix, string remaining) {
        string max_str = "";
        for (int i = 0; i < remaining.length(); i++) {
            char c = remaining[i];
            if (!is_prefix(prefix + c)) continue;
            if (search(prefix + c) && max_str.length() < prefix.length() + 1) max_str = prefix + c;
            string new_remaining = remaining.substr(0,i) + remaining.substr(i + 1, remaining.length());
            string new_longest = get_longest_word(prefix + c, new_remaining);
            if (max_str.length() < new_longest.length()) max_str = new_longest;
        }
        return max_str;
    }

    string longest_word(string s) {
        return get_longest_word("", s);
    }
};

int main() {
    Trie *trie = new Trie();
    trie->insert("ale");
    trie->insert("able");
    trie->insert("apple");
    trie->insert("monkey");
    trie->insert("plea");
    cout << trie->longest_word("abpcplea") << endl;
    return 0;
}
