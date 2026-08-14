struct BinaryTrie
{
    static constexpr int BITS = 30;
    struct Node
    {
        int go[2]{};
        int f[2]{};
    };
    vector<Node> trie;
    BinaryTrie()
    {
        trie.emplace_back();
    }
    void insert(int x)
    {
        int cur = 0;
        for (int i = BITS - 1; i >= 0; i--)
        {
            bool ch = x >> i & 1;
            if (!trie[cur].go[ch])
                trie[cur].go[ch] = trie.size(), trie.emplace_back();
            trie[cur].f[ch]++;
            cur = trie[cur].go[ch];
        }
    }
    void erase(int x)
    {
        int cur = 0;
        for (int i = BITS - 1; i >= 0; i--)
        {
            bool ch = x >> i & 1;
            trie[cur].f[ch]--;
            cur = trie[cur].go[ch];
        }
    }

    int get(int x)
    {
        // TODO : Logic Here
        int cur = 0;
        int ret = 0;
        for (int i = BITS - 1; i >= 0; i--)
        {
            bool ch = x >> i & 1;
            (trie[cur].f[ch ^ 1]) ? ret |= (1 << i) : ret;
            (trie[cur].f[ch ^ 1]) ? cur = trie[cur].go[ch ^ 1] : cur = trie[cur].go[ch];
        }
        return ret;
    }
};