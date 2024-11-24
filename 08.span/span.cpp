#include <iostream>
#include <format>
#include <span>
#include <array>

void show(std::span<int> const &a)
{
	for(auto const &v : a)
		std::cout << std::format("{:<4d}", v) << std::endl; 
}

int main(int argc, char *argv[])
{
	std::array values{1, 2, 3, 4, 5, 0, 9 ,8, 7, 6};
	std::cout << "All" << std::endl;
	show(values);

	std::cout << "First 3" << std::endl;
	show(std::span{values}.first(3));

	std::cout << "Last 3" << std::endl;
	show(std::span{values}.last(3));

	std::cout << "Subview(3, 2)" << std::endl;
	show(std::span{values}.subspan(3,2));

	return EXIT_SUCCESS;
}
