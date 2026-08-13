vector<int> temp = a;
sort(temp.begin(), temp.end());
temp.erase(unique(temp.begin(), temp.end()), temp.end());


for(int i = 0; i < n; i++){
    a[i] = lower_bound(temp.begin(), temp.end(), a[i]) - temp.begin() + 1;
}