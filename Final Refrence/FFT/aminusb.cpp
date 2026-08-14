vector<int> A_Minus_B(vector<int> a, vector<int> b)
{
    int shift = b.size() - 1;
    reverse(all(b));
    // or
    // for (int i = 0; i < b.size() / 2; i++)
    //     swap(b[i], b[shift - i]);
    vector<int> ans = conv(a, b);
    return {ans.begin() + shift, ans.end()};
}