#include <iostream>
#include <format>

template<typename T>
inline constexpr auto integral_value = std::is_integral<T>::value;

int main(int argc, char *argv[])
{
	std::cout << std::format("integral_value<int> = {}", integral_value<int>) << std::endl;
	std::cout << std::format("integral_value<float> = {}", integral_value<float>) << std::endl;

	return EXIT_SUCCESS;
}
