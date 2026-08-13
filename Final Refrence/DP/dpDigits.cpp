const int mod = 998244353;
ll add(ll a, ll b) {
    return ( a + b + mod) % mod;
}
ll mul(ll a, ll b) {
    return (a * b) % mod;
}
struct Node{
    ll cnt,sum;
};
bool memo[2][2][(1<<10)][20];
Node dp [2][2][(1<<10)][20]; //ru,rd,lz,msk (taken digits) , i = n 
string l,r;
int n,k;
 
ll pow10[20];
Node rec(bool ru,bool rd,int msk,int i){
 
    if(i == n){
        //
        return {1,0};
    }
 
    Node &ret = dp[ru][rd][msk][i];
    if(memo[ru][rd][msk][i])
        return ret;
    
    short up = ru ? r[i] - '0' : 9;
    short down = rd ? l[i] - '0' : 0;

    ret = { 0 , 0};
    
    for(ll d=down ; d<=up ; d++){
        ll nexMsk = msk;
        if( !(msk == 0 && d == 0)) // not leading zeros
            nexMsk = msk | (1<<d);
            
        if( __builtin_popcount(nexMsk) <= k ){
            Node temp = rec(ru && d==up , rd && d==down , nexMsk ,i+1);
 
            ret.cnt = add(ret.cnt , temp.cnt);
            ll dig_val = mul(mul(d , pow10[n-i-1]) , temp.cnt );
            ret.sum =  add ( add(ret.sum,dig_val) , temp.sum);
        }
    }
    memo[ru][rd][msk][i] = true;
    return ret;
}
void solve() {
    cin>>l>>r >> k;
    n = r.size();
    while(l.size()!=n)
        l = "0" + l;
    
    memset(dp,-1,sizeof dp);
    
    pow10[0] = 1;
    for(int i=1;i<20;i++)
        pow10[i] = mul(pow10[i-1],10);
    
    cout<<rec(1,1,0,0).sum <<'\n';
}