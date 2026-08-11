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

![alt text]({1D91104C-1872-4A6A-B0E3-2ECF8D31DB03}.png)