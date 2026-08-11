#include <iostream>
#include <vector>
#include <string>

struct NODE {

    NODE *children[26];
    int cntEndWith = 0;
    int cntPrefix = 0;
    bool is_end=false;
};
class Trie {
private:
    NODE* root;

public:
    Trie() {//constructor
        root = new NODE();
    }
    void insert(const string& word) {
        NODE* node = root;
        for (auto c:word)
        {
            if (node->children[c - 'a'] == NULL)//check if exist
                node->children[c - 'a'] = new NODE();
        
            node = node->children[c - 'a'];
            node->cntPrefix++;
        }
        node->cntEndWith++;
        node->is_end = true;       
    }
    bool search(const string& word) {
        NODE* node = root;
        for (char c : word) {
            if (node->children[c - 'a'] == NULL)
                return false;
            node = node->children[c - 'a'];
        }
        return node->is_end;
    }
    bool startWith(const string& word) {
        NODE* node = root;
        for (char c : word) {
            if (node->children[c - 'a'] == NULL)
                return false;
            node = node->children[c - 'a'];
        }
        return true;
    }
    int CountWordsEqualTo(const string& word) {
        NODE* node = root;
        for (auto c : word) {
            if (node->children[c - 'a'] == NULL)
                return 0;
            node = node->children[c - 'a'];
        }
        return node->cntEndWith;
    }
    int CountWordsStartWith(const string& word) {
        NODE* node = root;
        for (auto c : word) {
            if (node->children[c - 'a'] == NULL)
                return 0;
            node = node->children[c - 'a'];
        }
        return node->cntPrefix;
    }
    void erase(string s) {
        NODE* node = root;
        for (auto c : s) {
            if (node->children[c - 'a'] == NULL)
                return;
            node = node->children[c - 'a'];
            node->cntPrefix--;
        }
        node->cntEndWith--;
    }
};