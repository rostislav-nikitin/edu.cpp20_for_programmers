export module not_visible_accessible;

import <string>;

namespace not_visible_accessible
{
	class A
	{
	public:
		A(int x);
		int getX() const;
	private:
		int x_;
	};

	export A getA(int x);
	export std::string to_string(A);
}

not_visible_accessible::A::A(int x) : x_(x)
{
}

int not_visible_accessible::A::getX() const
{
	return x_;
}

not_visible_accessible::A not_visible_accessible::getA(int x)
{
	return not_visible_accessible::A(x);
}
	
std::string not_visible_accessible::to_string(A a)
{
	return std::to_string(a.getX());
}
