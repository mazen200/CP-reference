
```CPP
struct FenwickTree {
    int n;
    vector<long long> tree;

    // 1. Empty Constructor: O(N)
    FenwickTree(int n) : n(n) {
        tree.assign(n + 1, 0); // 1-indexed
    }

    // 2. Fast Build Constructor: O(N) instead of O(N log N)
    // Use this if you have an initial array to populate the tree.
    FenwickTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(n + 1, 0);
        
        // Copy initial values (1-indexed)
        for (int i = 0; i < n; i++) {
            tree[i + 1] = arr[i];
        }
        
        // Propagate values to parents in O(N)
        for (int i = 1; i <= n; i++) {
            int parent = i + (i & -i);
            if (parent <= n) {
                tree[parent] += tree[i]; 
                // Note: Change '+' to '^' (XOR) or '*' if using other invertible operations
            }
        }
    }

    // 3. Point Update: O(log N)
    // Adds 'val' to the element at index 'i' (1-based)
    void add(int i, long long val) {
        for (; i <= n; i += (i & -i)) {
            tree[i] += val; 
            // Note: Change '+' to '^' for XOR
        }
    }

    // 4. Prefix Query: O(log N)
    // Returns the sum of elements from index 1 to 'i' (1-based)
    long long query(int i) const {
        long long sum = 0; // Note: Use 0 for sum/XOR, 1 for multiplication
        for (; i > 0; i -= (i & -i)) {
            sum += tree[i]; 
            // Note: Change '+' to '^' for XOR
        }
        return sum;
    }

    // 5. Range Query: O(log N)
    // Returns the sum of elements from index 'l' to 'r' inclusive (1-based)
    long long query(int l, int r) const {
        if (l > r) return 0;
        return query(r) - query(l - 1); 
        // Note: Change '-' to '^' for XOR, or modular inverse for multiplication
    }

    // 6. Binary Lifting / Lower Bound: O(log N)
    // Finds the FIRST index where the prefix sum is >= 'targetSum'.
    // CRITICAL: This only works if all elements in the array are non-negative!
    // Highly useful for finding the k-th smallest element in a frequency array.
    int lowerBound(long long targetSum) const {
        int pos = 0;
        long long currentSum = 0;
        
        // Get the highest power of 2 less than or equal to n
        int msb = 1;
        while ((msb << 1) <= n) {
            msb <<= 1;
        }
        
        for (int i = msb; i > 0; i >>= 1) {
            int nextPos = pos + i;
            if (nextPos <= n && currentSum + tree[nextPos] < targetSum) {
                currentSum += tree[nextPos];
                pos = nextPos;
            }
        }
        return pos + 1; 
    }
};
```