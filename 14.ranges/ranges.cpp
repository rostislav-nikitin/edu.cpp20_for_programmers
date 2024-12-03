#include <iostream>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <format>
#include <string_view>
#include <iomanip>
#include <numeric>

using namespace std::string_literals;
using std::operator""sv;

int main(int argc, char *argv[])
{
	std::ranges::iota_view a(0);

	std::ranges::copy(a 
		| std::ranges::views::filter([](int a) { return a % 2 == 0; })
		| std::ranges::views::take(10)
		| std::ranges::views::take_while([](int a){ return a < 5; })
, std::ostream_iterator<int>(std::cout, ", "));

	std::cout << std::endl;

	std::map<int, std::string> m = {{1, "a"s}, {2, "b"s}, {3, "c"s}};
	std::ranges::copy(m | std::ranges::views::keys, std::ostream_iterator<int>(std::cout, ", "));

	std::cout << std::endl;

	std::ranges::copy(m | std::ranges::views::values | std::ranges::views::drop(1), std::ostream_iterator<std::string>(std::cout, ", "));

	std::cout << std::endl;

	std::vector<int> v{1, 2, 3, 4, 5};
	auto [min, max] = std::ranges::minmax(v);

	std::cout << std::format("Min: {}, Max: {}", min, max) << std::endl;

	std::vector<std::string> str;
	std::ranges::copy(
		std::ranges::views::split("The one two three"sv, " "sv)
		| std::views::transform([](auto const sr){ return std::string(sr.begin(), sr.end()); })
	, std::back_inserter(str));

	std::ranges::copy(str, std::ostream_iterator<std::string>(std::cout, ", "));

	std::cout << std::endl;

//	auto splitted = std::ranges::views::split("The one two three"s, " "s);
//	for(auto const val : std::views::split("a b c d e"sv, " "sv)
//	{
//		std::cout << std::string_view(val) << std::endl;
//	}
	//std::ranges::copy(splitted, std::ostream_iterator<std::string>(std::cout, ", "));

    using std::operator""sv;
    constexpr auto words{"Hello^_^C++^_^20^_^!"sv};
    constexpr auto delim{"^_^"sv};
 
    for (const auto word : std::views::split(words, delim))
        // with string_view's C++23 range constructor:
        std::cout << std::quoted(std::string_view(word.begin(), word.end())) << ' ';
    std::cout << '\n';


	auto jv = std::views::join(str) | std::views::common;
	std::cout << std::string(jv.begin(), jv.end()) << std::endl;
	//std::cout << std::string_view(jv) << std::endl;

	std::string jstr(jv.begin(), jv.end());
	std::string_view jstrv(jstr.begin(), jstr.end());


	std::vector ints {1, 2, 3, 3, 4, 6, 7, 8, 9};
	int rr = std::reduce(std::begin(ints), std::end(ints), 0, std::plus());
	std::cout << std::format("Reduce result: {}", rr) << std::endl;

	int trr = std::transform_reduce(std::begin(ints), std::end(ints), 0, std::plus(), [](int a) { return a * a; });
	std::cout << std::format("Transform & Reduce result: {}", trr) << std::endl;

	

	return EXIT_SUCCESS;
}
