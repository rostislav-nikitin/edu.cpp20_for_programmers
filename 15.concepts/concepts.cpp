#include <iostream>
#include <concepts>
#include <format>

template<typename T>
	requires std::integral<T>
T sum(T const &a, T const &b)
{
	return a + b;
}

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<Numeric T>
T multiply(T const &a, T const &b)
{
	return a * b;
}

auto substract(Numeric auto const &a, Numeric auto const &b)
{
	return a - b;
}

auto divide = [](Numeric auto const &a, Numeric auto const &b)
{
	return a / b;
};

auto divide2 = []<Numeric T>(T const &a, T const &b)
{
	return a / b;
};

auto divide3 = []<Numeric T>(T const &a, T const &b)
	requires Numeric<T>
{
	return a / b;
};

// Simple concept
template<typename T>
class A
{
public:
	A(T a, T b) : a_(a), b_(b) {}
	T sum() { return a_ + b_; }
private:
	T a_;
	T b_;
};


template<typename T>
concept SumExists = 
	requires(T a) 
	{
		a.sum();
	};

template<template<typename> typename U, typename T>
	requires SumExists<U<T>>
	T sumOp(U<T> sumObj){ return sumObj.sum(); }

// Compoud concepts
template<typename T>
class B
{
public: 
	B(T a) : a_(a) {}
	T operator()() { return a_; }

private:
	T a_;
};

template<template<typename> typename U, typename T>
concept SameReturn = 
	requires(U<T> a)
	{
		{a() } -> std::same_as<T>; 
	};

template<template<typename> typename U, typename T>
	requires SameReturn<U, T>
T IdentityOp(U<T> b) { return b(); }

// Type concepts
template<typename T>
concept NumericType = std::integral<T> ||
	requires  
	{
		std::is_floating_point_v<T>;
	};

auto MulOp(NumericType auto const a, NumericType auto const b) { return a * b; }

// Nested concepts
template<typename T>
	requires requires
	{
		std::is_integral_v<T>;
	}
	T ModOp(T const a, T const b) { return a % b; }


int main(int argc, char *argv[])
{
	using namespace std::string_literals;

	// Using intergal type: OK
	std::cout << std::format("sum(a, b) = {}", sum(10, 25)) << std::endl;

	// Using NON intergal type: NOT OK
	//std::cout << std::format("sum(a, b) = {}", sum(10.5, 25.1)) << std::endl;
	
	// Using Numeric type: OK
	std::cout << std::format("multiply(a, b) = {}", multiply(10, 25)) << std::endl;

	// Using NOT Numeric type: NOT OK
	//std::cout << std::format("multiply(a, b) = {}", multiply("a"s, "b"s)) << std::endl;
	
	std::cout << std::format("substract(a, b) = {}", substract(25, 10)) << std::endl;

	std::cout << std::format("divide(a, b) = {}", divide(50, 10)) << std::endl;

	// Simple concept
	A a(50, 60);
	int sr = sumOp(a);
	std::cout << std::format("sumOp(a) = {}", sr) << std::endl;

	// Compound concept
	B b(99);
	int cr = IdentityOp(b);
	std::cout << std::format("IdentityOp = {}", cr) << std::endl;

	// Type concept
	std::cout << std::format("MulOp(10, 20) = {}", MulOp(10, 20)) << std::endl;

	// Nested concept
	std::cout << std::format("ModOp(100, 11) = {}", ModOp(100, 11)) << std::endl;


	return EXIT_SUCCESS;
}
