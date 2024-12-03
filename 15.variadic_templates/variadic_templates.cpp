#include <iostream>
#include <format>

template<typename T, typename... Args>
T sumUnLeft(Args... args)
{
	return (... + args);
}

template<typename... Args>
auto sumUnLeftAuto(Args... args)
{
	return (... + args);
}

template<typename T, typename... Args>
T sumBinLeft(T first, Args... next)
{
	return (first + ... + next);
}

template<typename... Args>
auto sumBinLeftAuto(Args... args)
{
	return (0 + ... + args);
}

//concept
template<typename T, typename... Args>
concept VariadicSameType = (std::same_as<T, Args> && ...);

template<typename T, typename... Args>
	requires VariadicSameType<T, Args...> && (std::integral<T> || std::floating_point<T>)
T sum(T first, Args... args)
{
	return (first + ... + args);
}

template<typename... Args>
auto print(Args... args)
{
	(..., (std::cout << args << ", "));
}



int main(int argc, char *argv[])
{
	std::cout << std::format("sumUnLeft(1, 2, 3, 4, 5) = {}", sumUnLeft<int>(1, 2, 3, 4, 5)) << std::endl;
	std::cout << std::format("sumBinLeft(1, 2, 3, 4, 5) = {}", sumBinLeft(1, 2, 3, 4, 5)) << std::endl;
	std::cout << std::format("sum(1, 2, 3, 4, 5) = {}", sum(1, 2, 3, 4, 5)) << std::endl;
	print(1, 2, 3, 4, 5);
	
	return EXIT_SUCCESS;
}
