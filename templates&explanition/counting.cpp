#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;   // adjust as needed

ll fact[MAXN], invfact[MAXN];


// 🔹 Fast Power (a^b % MOD)
ll fastPow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 🔹 Modular Inverse (MOD must be prime)
ll modinv(ll a) {
    return fastPow(a, MOD - 2);
}

// 🔹 Precompute factorials and inverse factorials
void init_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invfact[MAXN - 1] = modinv(fact[MAXN - 1]);
    for (int i = MAXN - 2; i >= 0; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

// 🔹 nCr (Combination)
ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

// 🔹 nPr (Permutation)
ll nPr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[n - r] % MOD;
}

// 🔹 Combination with Repetition
// (n multichoose r) = (n+r-1)Cr
ll nCr_rep(ll n, ll r) {
    return nCr(n + r - 1, r);
}

// 🔹 Stars and Bars
// Distribute k identical items into n distinct boxes
ll stars_and_bars(ll n, ll k) {
    // (k + n - 1)C(n - 1)
    return nCr(k + n - 1, n - 1);
}

// 🔹 Stars and Bars (at least 1 in each box)
ll stars_and_bars_at_least_one(ll n, ll k) {
    // Give 1 to each first
    if (k < n) return 0;
    return nCr(k - 1, n - 1);
}


// 🔹 Example usage
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_factorials();

    // Examples
    cout << "5C2 = " << nCr(5, 2) << "\n";          // 10
    cout << "5P2 = " << nPr(5, 2) << "\n";          // 20
    cout << "2^10 = " << fastPow(2, 10) << "\n";     // 1024
    cout << "Stars & Bars (n=3, k=5): "
         << stars_and_bars(3, 5) << "\n";           // 21

    return 0;
}
