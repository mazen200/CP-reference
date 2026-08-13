struct Trie {
    struct Node {
        int children[26]{};
        int f = 0;
    };
    vector<Node> trie;
    Trie() { trie.emplace_back(); }
    void insert(string &s) {
        int node = 0;
        for (auto &i : s) {
            int ch = (i - 'a');
            if (!trie[trie[node].children[ch]].f) {
                trie[node].children[ch] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].children[ch];
            trie[node].f++;
        }
    }
    void erase(string &s) {
        int node = 0;
        for (auto &i : s) {
            int ch = (i - 'a');
            node = trie[node].children[ch];
            trie[node].f--;
        }
    }
    int query(string &s) {
        int node = 0;
        for (auto &i : s) {
            int ch = (i - 'a');
            if (!trie[trie[node].children[ch]].f) return 0;
            node = trie[node].children[ch];
        }
        return trie[node].f;
    }
};