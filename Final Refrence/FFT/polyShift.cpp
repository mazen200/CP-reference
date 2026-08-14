vector<int> poly_shift(vector<int> &p, int k)
{
    int deg = p.size() - 1;
    vector<int> p1(deg + 1), p2(deg + 1);
    for (int i = 0; i <= deg; i++)
    {
        p1[i] = mul(p[i], fact[i]);
        p2[deg - i] = mul(fp(k, i), ifact[i]);
    }
    auto res = conv(p1, p2);
    vector<int> ans(deg + 1);
    for(int i= 0;i <= deg; i++)
        ans[i] = mul(res[i + deg], ifact[i]);
    return ans;
}