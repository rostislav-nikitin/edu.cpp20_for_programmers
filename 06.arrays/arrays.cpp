#include <iostream>
#include <iterator>
#include <format>
#include <array>
#include <random>
#include <algorithm>

constexpr size_t arraySize = 10;

void fillArray(std::array<int, arraySize> &a)
{
	std::random_device randomDevice;
	std::default_random_engine engine(randomDevice());
	std::uniform_int_distribution randomNumber(1, 6);

	for(auto &value : a)
		value = randomNumber(engine);
}

void showArray(std::array<int, arraySize> a)
{
	std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(std::cout, "\n"));
}

void sumArray(std::array<int, arraySize> a)
{
	for(int sum{0}; auto const &value : a)
	{
		sum += value;
		std::cout << std::format("{:>4d}:\t{:>4d}", value, sum) << std::endl;
	}
}

int main(int argc, char *argv[])
{
	std::array<int, arraySize> array1 {1, 2, 3, 4, 9, 8, 7, 6, 5, 0};

	fillArray(array1);
	showArray(array1);
	sumArray(array1);


	return EXIT_SUCCESS;
}
