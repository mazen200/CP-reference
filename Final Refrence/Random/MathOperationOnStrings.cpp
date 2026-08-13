string multiply(const string &a, const string &b)
{
    if (a.size() < b.size())
        swap(a, b);
    int n = a.size(), m = b.size();
    vector<int> ans(n + m + 1);
    for (int i = n - 1; ~i; i--)
    {
        for (int j = m - 1; ~j; j--)
        {
            int idx = i + j;
            int cur = (a[i] - '0') * (b[j] - '0');
            ans[idx] += cur;
            if (ans[idx] >= 10)
            {
                if (idx)
                {
                    ans[idx - 1] += (ans[idx] / 10);
                    ans[idx] %= 10;
                }
            }
        }
    }
    string ret;
    int q = 0;
    if (ans[0] >= 10)
    {
        q = 1;
        ret += char('0' + ans[0] / 10);
        ans[0] %= 10;
    }
    int cnt = 1;
    for (int i = 0; i < n + m - 1; i++)
    {
        if (q || ans[i] != 0)
        {
            for (int j = i; j < n + m - 1; j++)
                ret += char('0' + ans[j]);
            cnt = 0;
            break;
        }
    }
    if (cnt)
        ret = "0";
    return ret;
}

string stringStringAddition(string a, string b)
{
    string ret, other;
    if (a.size() > b.size())
        ret = a, other = b;
    else
        ret = b, other = a;
    reverse(ret.begin(), ret.end());
    reverse(other.begin(), other.end());
    int diff = ret.size() - other.size();
    other += string(diff, '0');
    for (int i = ret.size() - 1; i >= 0; i--)
    {
        int cur = (ret[i] - '0') + (other[i] - '0');
        ret[i] = (cur % 10) + '0';
        cur /= 10;
        int currentIdx = i;
        while (cur > 0)
        {
            currentIdx++;
            if (currentIdx == ret.size())
                ret += '0';
            cur += (ret[currentIdx] - '0');
            ret[currentIdx] = (cur % 10) + '0';
            cur /= 10;
        }
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

string longDivision(string num, ll divisor)
{
    string ans;
    ll idx = 0;
    ll temp = num[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (num[++idx] - '0');
    while (num.size() > idx)
    {
        ans += (temp / divisor) + '0';
        temp = (temp % divisor) * 10 + num[++idx] -
               '0';
    }
    if (ans.length() == 0)
        return "0";
    return ans;
}