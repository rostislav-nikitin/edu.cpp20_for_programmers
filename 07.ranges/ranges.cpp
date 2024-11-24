#include <iostream>

#include <ranges>
#include <format>

void printValues(auto &values)
{
	for(auto const& value : values)
		std::cout << std::format("value: {:>4.2f}",  float(value)) << std::endl;
}

int main(int argc, char *argv[])
{
	auto values = 
			std::ranges::views::iota(1, 11)
			| std::ranges::views::filter([](int const &a) { return a % 2 == 0; })
			| std::ranges::views::transform([](int const &a){ return a * a; });

	printValues(values);

	return EXIT_SUCCESS;
}
