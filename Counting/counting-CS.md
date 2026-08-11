# 🧮 Counting & Combinatorics – Cheat Sheet

## 🔹 1. Core Rules

### ➕ Addition Rule (OR)

Use when **only one case happens** and cases are **disjoint**.

```
Total = A + B + C
```

⚠️ If cases overlap → use **Inclusion–Exclusion**

---

### ✖️ Product Rule (AND)

Use when choices happen **in sequence**.

```
Total = a × b × c
```

Ask: *How many choices at each step?*

---

## 🔹 2. Factorials

```
n! = n × (n−1) × ... × 1
```

Used for **arranging distinct objects**.

---

## 🔹 3. Permutations (Order matters)

### Without repetition

```
nPr = n! / (n−r)!
```

### With repetition

```
n^r
```

Keywords:

> arrange, order, positions, ranking

---

## 🔹 4. Combinations (Order does NOT matter)

### Without repetition

```
nCr = n! / (r!(n−r)!)
```

### With repetition

```
(n+r−1)Cr
```

Keywords:

> choose, select, group

---

## 🔹 5. Inclusion–Exclusion (Add–Subtract)

### Two sets

```
|A ∪ B| = A + B − (A ∩ B)
```

### Three sets

```
A + B + C
− (AB + AC + BC)
+ ABC
```

Used when:

* OR conditions
* Overlapping cases
* Forbidden elements

---

## 🔹 6. Complement Counting

Count **everything**, subtract **bad cases**.

```
Valid = Total − Invalid
```

Use when:

* “at least one”
* “not all”
* “contains”

---

## 🔹 7. Stars and Bars ⭐

Distribute **k identical items** into **n distinct boxes**.

### No restriction:

```
(k+n−1)C(n−1)
```

### At least one per box:

```
(k−n+n−1)C(n−1) = (k−1)C(n−1)
```

Used for:

```
x1 + x2 + ... + xn = k
```

---

## 🔹 8. Case Analysis

Split into **exhaustive & disjoint** cases.

```
Total = case1 + case2 + ...
```

Fix something:

* first position
* smallest / largest value
* number of occurrences

---

## 🔹 9. Common Patterns

| Problem Statement    | Technique           |
| -------------------- | ------------------- |
| OR conditions        | Inclusion–Exclusion |
| At least one         | Complement          |
| Sequence of steps    | Product Rule        |
| Order matters        | Permutation         |
| Order doesn’t matter | Combination         |
| Identical objects    | Stars & Bars        |
| Constraints          | Case analysis       |

---

## 🔹 10. Quick Decision Guide (10-Second Rule)

Ask in order:
1️⃣ What am I counting?
2️⃣ Order matters?
3️⃣ Repetition allowed?
4️⃣ Constraints?
5️⃣ Overlaps?

Then choose.

---

## ⚠️ Common Mistakes

❌ Using nPr instead of nCr
❌ Overlapping cases without subtracting
❌ Forgetting edge cases (0, 1)
❌ Double counting due to symmetry

---

## 🔥 Competitive Programming Tips

* Precompute **factorials & inverse factorials**
* Watch for **mod = 1e9+7**
* If constraints are large → think **math, not brute force**
* If stuck → try **complement** or **fix one element**



Assuming the sticks are identical and the boxes are distinct, this is a classic combinatorics problem solved using the **Stars and Bars** method.

Here are the formulas and the reasoning for both scenarios.

## 1. Each box must have at least 1 stick

If every box needs at least one stick, you are looking for the number of positive integer solutions to the equation:
$x_1 + x_2 + \dots + x_F = N$ (where $x_i \ge 1$)

**The Formula:**


$$\binom{N-1}{F-1}$$

**Why it works:**
Imagine lining up all $N$ sticks in a row. There are $N - 1$ gaps between these sticks. To divide the sticks into $F$ groups (boxes), you need to place $F - 1$ dividers (bars) into those gaps. Because you can only place one divider per gap, no box can be empty.

*(Note: If $N < F$, the answer is **0** because you don't have enough sticks to put one in each box.)*

---

## 2. Each box must have at least K sticks

This is a generalization of the problem where each box must contain a minimum of $K$ sticks ($x_i \ge K$, where $K \ge 0$).

**The Formula:**


$$\binom{N - F \times K + F - 1}{F - 1}$$

**Why it works:**

1. **Fulfill the minimum requirement first:** Place $K$ sticks into each of the $F$ boxes. You have now used up $F \times K$ sticks.
2. **Find the remaining sticks:** You have $N' = N - (F \times K)$ sticks left to distribute.
3. **Distribute the rest with no restrictions:** Now you just need to distribute the remaining $N'$ sticks into the $F$ boxes, where boxes are allowed to receive **0** of the remaining sticks.
4. The standard Stars and Bars formula for non-negative integers (allowing empty boxes) is choosing $F-1$ dividers among $N'$ sticks and $F-1$ dividers total: $\binom{N' + F - 1}{F - 1}$. Substituting $N'$ gives the final formula.

*(Note: If $N < F \times K$, the answer is **0** because you cannot even fulfill the base requirement.)*

**Special Case ($K = 0$):**
If you want to know the combinations where boxes can be completely empty (at least 0 sticks), substituting $K = 0$ into the formula gives you the standard equation for non-negative integer solutions:


$$\binom{N + F - 1}{F - 1}$$