// Wavelet Tree — O(n log σ) build, O(log σ) query
// Positions 1-indexed [L,R]. Build: WT(arr+1, arr+n+1, lo, hi)
//
// Derivable (not in code):
//   lt(L,R,v)            = lte(L,R,v-1)
//   range_count(L,R,a,b) = lte(L,R,b) - lte(L,R,a-1)
//   range_sum(L,R,a,b)   = sum_lte(L,R,b) - sum_lte(L,R,a-1)
//   sum_k(L,R,k)         = sum_lte(L,R, kth(L,R,k))
//                           - kth(L,R,k) * (lte(L,R,kth(L,R,k)) - k)
//   prev_value(L,R,v)    = kth(L,R, lte(L,R,v))       — -1 if lte==0
//   next_value(L,R,v)    = kth(L,R, lte(L,R,v-1)+1)   — -1 if lte==R-L+1
struct WT {
    int lo, hi;
    vector<int> b;
    vector<ll> t; // b[i]=prefix count left, t[i]=prefix sum left
    WT *l = NULL, *r = NULL;

    WT(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (lo == hi || from == to)
            return;
        int mid = lo + (hi - lo) / 2;
        int n = to - from;
        b.assign(n + 1, 0);
        t.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            b[i + 1] = b[i] + (from[i] <= mid);
            t[i + 1] = t[i] + (from[i] <= mid ? from[i] : 0);
        }
        auto f = [mid](int v) { return v <= mid; };
        auto pivot = stable_partition(from, to, f);
        if (from != pivot)
            l = new WT(from, pivot, lo, mid);
        if (pivot != to)
            r = new WT(pivot, to, mid + 1, hi);
    }

    // # values <= k in [L,R]
    int lte(int L, int R, int k) {
        if (L > R || k < lo)
            return 0;
        if (hi <= k)
            return R - L + 1;
        int lb = b[L - 1], rb = b[R];
        int mid = lo + (hi - lo) / 2;
        if (k <= mid) {
            if (l)
                return l->lte(lb + 1, rb, k);
            return 0;
        }
        int left_count = rb - lb;
        if (r)
            return left_count + r->lte(L - lb, R - rb, k);
        return left_count;
    }

    // k-th smallest in [L,R], 1-indexed
    int kth(int L, int R, int k) {
        if (lo == hi)
            return lo;
        int lb = b[L - 1], rb = b[R], inL = rb - lb;
        if (k <= inL)
            return l->kth(lb + 1, rb, k);
        return r->kth(L - lb, R - rb, k - inL);
    }

    // sum of values <= v in [L,R]
    ll sum_lte(int L, int R, int v) {
        if (L > R || v < lo)
            return 0;

        // Base case: leaf node
        if (lo == hi) {
            return 1LL * (R - L + 1) * lo;
        }

        int lb = b[L - 1], rb = b[R];
        int mid = lo + (hi - lo) / 2;

        // Traverse left
        if (v <= mid) {
            if (l)
                return l->sum_lte(lb + 1, rb, v);
            return 0;
        }

        // Traverse right (this naturally handles the hi <= v case)
        ll left_sum = t[R] - t[L - 1];
        if (r)
            return left_sum + r->sum_lte(L - lb, R - rb, v);
        return left_sum;
    }

    // # distinct values in [L,R]
    int count_distinct(int L, int R) {
        if (L > R)
            return 0;
        if (lo == hi)
            return 1;
        int lb = b[L - 1], rb = b[R];
        int res = 0;
        if (lb < rb)
            res += l->count_distinct(lb + 1, rb);
        if (L - lb <= R - rb)
            res += r->count_distinct(L - lb, R - rb);
        return res;
    }

    ~WT() {
        delete l;
        delete r;
    }
};