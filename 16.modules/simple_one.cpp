module simple.one;

int sum(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

namespace simple::one
{
	int sum(int a, int b)
	{
		return a + b;
	}
}

namespace simple::two
{
	int sum(int a, int b)
	{
		return a + b;
	}

	int sub(int a, int b)
	{
		return a - b;
	}
}
