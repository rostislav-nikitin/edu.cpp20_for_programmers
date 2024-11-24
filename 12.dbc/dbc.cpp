#include <iostream>
#include <format>

template<typename T>
T div(T number, T divider)
[[pre audit: divider > 0]]
{
	return number / divider;
}

int main(int argc, char *argv[])
{

	auto a = div(10.0, 1.5);
	std::cout << std::format("number: {:.2f} / divider: {:.2f} = {:.2f}", 10.0, 1.5, a) << std::endl;

	auto b = div(100.0, 0.0);
	std::cout << std::format("number: {:.2f} / divider: {:.2f} = {:.2f}", 100.0, 0.0, b) << std::endl;

	return EXIT_SUCCESS;
}
