/* 
 * ============================================================================
 * CATALAN NUMBERS: CLASSIC SUB-PROBLEMS
 * The nth Catalan number (C_n) solves several classic combinatorial problems:
 * 
 * 1. Valid Parentheses (Dyck Words): 
 *    Number of correctly matched bracket sequences consisting of 'n' pairs 
 *    of parentheses.
 *    Example (n=3): ((())), ()(()), ()()(), (())(), (()()) -> C_3 = 5
 * 
 * 2. Binary Search Trees (BSTs):
 *    Number of structurally unique BSTs that can store 'n' distinct keys.
 * 
 * 3. Polygon Triangulation:
 *    Number of ways to divide a convex polygon with 'n+2' sides into triangles 
 *    by drawing non-intersecting diagonals.
 * 
 * 4. Grid Paths (Dyck Paths):
 *    Number of monotonic paths on an n x n grid from bottom-left (0,0) to 
 *    top-right (n,n) that never cross above the main diagonal.
 * 
 * 5. Non-crossing Chords:
 *    Number of ways to connect 2n points on a circle to form 'n' chords 
 *    such that no two chords intersect.
 * 
 * 6. Full Binary Trees:
 *    Number of full binary trees (where every vertex has either 0 or 2 children) 
 *    that have exactly 'n' internal nodes (and n+1 leaves).
 * ============================================================================
 */

long long catalanMod(int n) {
    if (n <= 1) return 1;

    long long numerator = 1;
    long long denominator = 1;

    // Calculate (2n)! / (n! * n!) % MOD
    for (int i = 0; i < n; i++) {
        numerator = (numerator * (2LL * n - i)) % MOD;
        denominator = (denominator * (i + 1)) % MOD;
    }

    // Multiply numerator by the modular inverse of the denominator
    long long combinations = (numerator * modInverse(denominator)) % MOD;

    // Multiply by the modular inverse of (n + 1)
    long long result = (combinations * modInverse(n + 1)) % MOD;
    
    return result;
}

long long catalan(int n) {
    if (n <= 1) return 1;
    
    long long res = 1;
    
    // Calculate nCr(2n, n) safely
    // Note: This relies on exact divisibility at each step to avoid early truncation
    for (int i = 0; i < n; ++i) {
        res *= (2LL * n - i);
        res /= (i + 1);
    }
    
    // Divide by (n + 1) to get the Catalan number
    return res / (n + 1);
}