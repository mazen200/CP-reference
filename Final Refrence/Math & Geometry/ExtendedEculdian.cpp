int euclid(int a, int b, int &x, int &y)
{
    if (a < 0 || b < 0)
    {
        int g = euclid(abs(a), abs(b), x, y);
        if (a < 0)
            x *= -1;
        if (b < 0)
            y *= -1;
        return g;
    }
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int g = euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}
int find_sol(int a, int b, int c, int &x0, int &y0, bool &found)
{
    int g = euclid(abs(a), abs(b), x0, y0);
    found = 1;
    if (c % g)
    {
        found = 0;
        return g;
    }
    x0 *= c / g;
    y0 *= c / g;
    return g;
}