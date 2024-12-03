export module simple.one;

export int sum(int a, int b);

export 
{
	int sub(int a, int b);
}

export namespace simple::one
{
	int sum(int a, int b);
}

namespace simple::two
{
	export int sum(int a, int b);
	int sub(int a, int b);
}
