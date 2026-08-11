Compression without using Map reduce complexity from O(N log N + N log MAXV) -> O(N log N)

```cpp
    vector<int> temp = a;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());


    for(int i = 0; i < n; i++){
        a[i] = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin() + 1;
    }
```