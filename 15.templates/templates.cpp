#include <iostream>
#include <format>

// template function
auto sum(auto const &a, auto const &b)
{
	return a + b;
}

//template lambda
auto lsum = [](auto const &a, auto const &b)
{
	return a + b;
};

//template lamda with restricted same type for all args
auto rlsum = []<typename T> (T const &a, T const &b)
{
	return a + b;
};


int main(int argc, char *argv[])
{
	std::cout << std::format("sum: a + b = {}", sum(10, 15)) << std::endl;
	std::cout << std::format("lambda sum: a + b = {}", lsum(10, 15)) << std::endl;
	std::cout << std::format("restricted lambda sum: a + b = {}", rlsum(10, 15)) << std::endl;

	
	return EXIT_SUCCESS;
}
