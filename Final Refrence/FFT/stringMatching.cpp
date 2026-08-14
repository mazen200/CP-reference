string chars = "abcdefghijklmnopqrstuvxyz";

int match_all_chars(const string &T, const string &P)
{
    int n = T.size(), m = P.size();
    if (m > n)
        return {};

    int required_matches = 0;
    for (char c : P)
    {
        if (c != '?')
            required_matches++;
    }

    vector<int> total_matches(n + m, 0);

    // Loop over all possible alphabet characters
    for (char c = 'a'; c <= 'z'; c++)
    {
        // Skip character if not present in P to save FFT operations
        bool in_p = false;
        for (char pc : P)
        {
            if (pc == c)
            {
                in_p = true;
                break;
            }
        }
        if (!in_p)
            continue;

        vector<int> A(n, 0), B(m, 0);
        for (int i = 0; i < n; i++)
            if (T[i] == c)
                A[i] = 1;
        for (int i = 0; i < m; i++)
            if (P[m - 1 - i] == c)
                B[i] = 1;

        vector<ll> C = multiply(A, B);
        for (int i = 0; i < n + m; i++)
        {
            total_matches[i] += C[i];
        }
    }

    int cnt = 0;
    for (int i = 0; i <= n - m; i++)
        cnt += (total_matches[i + m - 1] == required_matches);

    return cnt;
}