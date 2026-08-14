const int H = 1e4 + 5;
vector<int> grundy(H, 0);
for (int i = 1; i < H; i++)
{
    set<int> reachable;
    for (auto &move : moves)
        if (i - move >= 0)
            reachable.insert(grundy[i - move]);

    for (auto &x : reachable)
        if (grundy[i] == x)
            grundy[i]++;
        else
            break;
}