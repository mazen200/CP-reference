const int sqt = 320;
struct query
{
    int l, r, i;
    bool operator<(query &other)
    {
        int b1 = l / sqt;
        int b2 = other.l / sqt;
        if(b1 != b2) return b1 < b2;
        return r < other.r;
    }
};

int freq[N]{};
int n, q;
int answer = 0;
int arr[N]{};
void add(int idx)
{
    int val = arr[idx];
    if(val > N)
        return;
    answer -= (freq[val] == val);
    freq[val]++;
    answer += (freq[val] == val);
}
void rem(int idx)
{
    int val = arr[idx];
    if(val > N)
        return;
    
    answer -= (freq[val] == val);
    freq[val]--;
    answer += (freq[val] == val);
}

void MosAlgo(vector<query> &queries, vector<int> &ans)
{
    sort(all(queries));
    int l = 0, r = -1;
    for(auto &[L, R, idx] : queries)
    {
        while (r < R) add(++r);
        while(l > L) add(--l);
        while(r > R) rem(r--);
        while(l < L) rem(l++);
        ans[idx] = answer;
    }
}