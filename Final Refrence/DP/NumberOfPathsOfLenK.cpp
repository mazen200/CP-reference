#include <bits/stdc++.h>
#define Mazen_Alaa ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
typedef long double ld;

using namespace std;


void solve() {
    int n,m,k;cin>>n>>m>>k;

    Matrix T(n+1,Row(n+1));
    // if u is parent to v => t[u][v] = 1;
    for(int i=0,u,v;i<m;i++){
        cin>>u>>v;
        T[u][v] = 1;
    }
    Row a(n+1);
    for(ll &i:a)    
        i = 1;
    Matrix v;
    v.push_back(a);
    T = power(T,k);
    Matrix res = mul(v,T);
    
    ll tot = 0;
    for(int i=1;i<=n;i++){
        tot += res[0][i];
        if(tot >= mod) 
            tot-= mod;
        if(tot < 0) 
            tot += mod;
    }
    cout<<tot<<'\n';
}