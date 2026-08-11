#include <bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
//#include<ext/pb_ds/tree_policy.hpp>
#define Mazen_Alaa ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define testcases int t = 1;cin >> t;while (t--)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//template<typename T>
//using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
using namespace std;
// سورة النجم Quran
//وَأَن لَّيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ (39) وَأَنَّ سَعْيَهُ سَوْفَ يُرَىٰ (40)

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
        while (j > 0 && v[i] != v[j]) j = pi[j-1];
        if (v[i] == v[j]) j++;
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
void solve() {
    string s;
    cin>>s;
    int n = s.size();
    auto pi = prefix_function(s);

    //compute freq for each prefix
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++)
        ans[pi[i]]++;
    for (int i = n-1; i > 0; i--)
        ans[pi[i-1]] += ans[i];
    for (int i = 0; i <= n; i++)
        ans[i]++;
    
}
int main()
{

    Mazen_Alaa
    testcases
    solve();
    return 0;
}