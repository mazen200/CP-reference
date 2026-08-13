
const int N = 1e5 + 3;
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
            if (v[i] == (char)('a' + c)) 
                nxt[i][c] = i + 1;
            else if (i > 0)
                 nxt[i][c] = nxt[pi[i-1]][c];
            else
                nxt[i][c] = 0;
        }
    }
}
vector<pair<int,string>>adj[N];
ll ans = 0;
int az = 0;
void dfs(int node, int stat){
    for(auto &i:adj[node]){ 
        int nextState = stat;
        for(char &c:i.second)
        {
            nextState = nxt[nextState][c-'a'];
            ans += (nextState == az);
        }  
        dfs(i.first,nextState);
    }
}

void solve()
{
    int n;cin>>n;
    for(int i=2,j;i<=n;i++){
        string s;
        cin>>j>>s;
        adj[j].push_back({i,s});
    }
    string a;
    cin>>a;
    build_automaton(a);
    az = a.size();
    dfs(1,0);
    cout<<ans<<'\n';
}