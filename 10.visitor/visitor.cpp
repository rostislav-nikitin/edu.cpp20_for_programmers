#include <iostream>

#include <variant>

struct A
{
	std::string toString()
	{
		return std::string(__PRETTY_FUNCTION__);
	}
};

struct B
{
	std::string toString()
	{
		return std::string(__PRETTY_FUNCTION__);
	}
};

int main(int argc, char *argv[])
{

	using namespace std::string_literals;

	std::string str = R"(Test string)";
	std::string str2 = str + "test"s;


	std::variant<A, B> value(A{});

	std::visit([](auto& obj) { std::cout << obj.toString();  }, value);

	

	return EXIT_SUCCESS;
}
