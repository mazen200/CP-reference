int phi(int x)
{
	int ret = x;
	for (int i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
		{
			while (x % i == 0)
				x /= i;
			ret -= ret / i;
		}
	}
	if (x > 1)
		ret -= ret / x;
	return ret;
}