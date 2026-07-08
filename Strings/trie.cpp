#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Trie {
private:
    struct Node {
        vector<int> next;
        bool is_end;
        // Count how many words pass through this node
        int pass_count; 

        Node() : next(26, 0), is_end(false), pass_count(0) {}
    };

    vector<Node> trie;

public:
    Trie() {
        trie.emplace_back(); // Root
    }

    void insert(const std::string& word) {
        int curr = 0;
        for (char c : word) {
            int idx = c - 'a';
            if (trie[curr].next[idx] == 0) {
                trie[curr].next[idx] = trie.size();
                trie.emplace_back();
            }
            curr = trie[curr].next[idx];
            trie[curr].pass_count++; // Track usage
        }
        trie[curr].is_end = true;
    }

    bool erase(const std::string& word) {
        if (!search(word)) return false; // Word doesn't exist

        int curr = 0;
        for (char c : word) {
            int idx = c - 'a';
            int next_node = trie[curr].next[idx];
            
            trie[next_node].pass_count--;
            
            // Optimization: If no more words use this path, 
            // we can "sever" the link to prune the branch.
            if (trie[next_node].pass_count == 0) {
                trie[curr].next[idx] = 0;
                return true; 
            }
            curr = next_node;
        }
        
        trie[curr].is_end = false;
        return true;
    }

    bool search(const std::string& word) {
        int curr = 0;
        for (char c : word) {
            int idx = c - 'a';
            if (trie[curr].next[idx] == 0) return false;
            curr = trie[curr].next[idx];
        }
        return trie[curr].is_end;
    }
};