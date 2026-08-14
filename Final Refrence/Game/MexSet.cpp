int sz;
struct Set
{
    set<int> missing;
    Set()
    {
        for(int i = 0; i < sz; i++)
        {
            missing.insert(i);
        }
    }
    int getMex()
    {
        return missing.empty() ? sz : *missing.begin();
    }
    void insert(int x)
    {
        if(missing.count(x))
            missing.erase(x);
    }
    void clear()
    {
        for(int i = 0; i < sz; i++)
        {
            missing.insert(i);
        }
    }
};