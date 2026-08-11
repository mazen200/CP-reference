
```cpp
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
bool match(string s , string t) {
    string cur = t + '#' + s;

    vector<int> pi = prefix_function(cur);
 
    for (int &i : pi)
        if ( i == t.size()) 
            return true;
    return false;
}

const int N=1e3;
int nxt[N][26];
void build_automaton(string& v) {
    
    int m = v.size();

    vector<int> pi(m);
    
    for (int i = 1; i < m; i++) {
        int j = pi[i-1];
        while (j > 0 && v[i] != v[j]) 
            j = pi[j-1];

        if (v[i] == v[j])
            j++;
        pi[i] = j;
    }

    for (int i = 0; i <= m; i++) {
        for (int c = 0; c < 26; c++) {
            if (v[i] == (char)('A' + c)) nxt[i][c] = i + 1;
            else if (i > 0) nxt[i][c] = nxt[pi[i-1]][c];
            else nxt[i][c] = 0;
        }
    }
}

```