#include <iostream>
#include <string>
#include <format>
#include <algorithm>
#include <cstdint>

// Template meta-programming
template<int N>
long long int factorial()
{
	return N * factorial<N - 1>();
}

template<>
long long int factorial<0>()
{
	return 1;
}

// constexpr recursive
constexpr long long int factorial_recursive(int n)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	if(n == 0)
		return 1;

	return n * factorial_recursive(n - 1);
}

// constexpr metaprogramming
constexpr long long int factorial_iterative(int n)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	long long result = 1;

	for(int i = 1; i <= n; ++i)
		result *= i;

	return result;
}

// constexpr if
template<int N>
constexpr long long factorial_best()
{
	if constexpr (N < 6)
		return factorial_recursive(N);
	else
		return factorial_iterative(N);
}

// enable_if
template<typename T, typename = std::enable_if<std::is_integral<T>::value>::type>
T sum(T a, T b)
{
	return a + b;
}

//traits
template<typename T>
struct my_is_integer
{
	static constexpr bool value = false;
};

template<>
struct my_is_integer<int>
{
	static constexpr bool value = true;
};

template<typename T>
constexpr bool my_is_integer_v = my_is_integer<T>::value;

template<typename T>
concept MyIsInteger = my_is_integer_v<T>; 

auto inc(MyIsInteger auto n)
{
	return ++n;
}

// Field
template<int N>
struct string_literal
{
	consteval string_literal(const char (&str)[N])
	{
		std::copy_n(str, N, value_);
	}
	char value_[N];
};

template<string_literal name, typename T>
class field
{
public:
	template<int starts, int ends>
	struct position
	{
		std::string_view getName() { return std::string_view(name.value_); }
	};

	std::string_view getName() { return std::string_view(name.value_); }
	
};

// constexpr
template<typename T>
struct size
{
	static constexpr size_t value = sizeof(T);
};

template<typename T>
constexpr size_t size_v = size<T>::value;

template<typename T>
constexpr bool check_type_size()
{
	if constexpr(size_v<T> == 1)
		return true;
	else
		return false;
}

constexpr bool test_local_const()
{
	int const n = 10;

	if constexpr (n == 10)
		return true;
	else 
		return false;
}

// enable_if

//template<typename T, typename std::enable_if<std::is_move_constructible_v<T>, bool>::type = true>
//template<typename T, typename std::enable_if_t<std::is_move_constructible_v<T>, bool> = true>
template<typename T, std::enable_if_t<std::is_move_constructible_v<T>, bool> = true>
//template<typename T, typename = std::enable_if<std::is_move_constructible_v<T>, bool>::type>
class A
{
public:
	A(T t) {}
};

class B
{
};

class C
{
public:
	C() = default;
	C(C&) = default;
//	C(C&&) = delete;
};


// Embedded

template<typename T, uint32_t address>
struct reg
{
public:
	template<int bitNumber, std::enable_if_t<bitNumber < sizeof(T) * 8, bool> = true>
	struct bit
	{
		static void setValue(bool value);
		static bool getValue();
		
		static void set() {}
		static void reset() {}
	};

	template<int bitFrom, int bitTo, std::enable_if_t<(bitFrom <= bitTo) && (bitTo < sizeof(T) * 8), bool> = true>
	struct bit_group
	{
		static void setValue(T value) {}
		static T getValue();

		static void set();
		static void reset();
	};

	static void setValue(T value) {}
	static T getValue();
};

template<uint32_t address>
class Uart
{
private:
	static constexpr uint32_t ControlRegisterOffset = 0x00;
	static constexpr uint32_t OutputDataRegisterOffset = 0x04;
public:
/*
	auto getControlRegister()
	{
		return reg<uint32_t, address>();
	}
*/
	using cr = reg<uint32_t, address + ControlRegisterOffset>;
	using odr = reg<uint32_t, address + OutputDataRegisterOffset>;

	// Static 
	static void setMode() {}
	static void setSpeed() {}

	// Or None static
	void setOrdInst(uint8_t value) {}
	void setModeInst() {}
	void setSpeedInst() {}


};


template<typename Transmitter>
class DataTransmitter
{
public:
	void transmit(uint8_t *buffer, size_t size)
	{
		for(int i = 0; i < size; ++i)
			Transmitter::odr::setValue(*(buffer + i));
	}
};

template<typename Transmitter>
class DataTransmitterDynamic
{
private:
	Transmitter transmitter_;
public:
	DataTransmitterDynamic(Transmitter transmitter) : transmitter_(transmitter)
	{
	}

	void transmit(uint8_t *buffer, size_t size)
	{
		for(size_t i = 0; i < size; ++i)
			transmitter_.setOrdInst(buffer[i]);
	}
};

int main(int argc, char *argv[])
{
	std::cout << std::format("factorial<5>() = {}", factorial<5>()) << std::endl;
	std::cout << std::format("factorial_recursive(5) = {}", factorial_recursive(5)) << std::endl;
	std::cout << std::format("factorial_iterative(5) = {}", factorial_iterative(5)) << std::endl;
	std::cout << std::format("factorial_best<5>() = {}", factorial_best<5>()) << std::endl;
	std::cout << std::format("factorial_best<6>() = {}", factorial_best<6>()) << std::endl;

	std::cout << std::format("sum(10, 15) = {}", sum(10, 15)) << std::endl;
	//std::cout << std::format("sum(10, 15) = {}", sum(10.5, 15.5)) << std::endl;
	
	std::cout << std::format("my_is_integer_v<int> = {}", my_is_integer_v<int>) << std::endl;
	std::cout << std::format("my_is_integer_v<float> = {}", my_is_integer_v<float>) << std::endl;
	std::cout << std::format("int(5) = {}", inc(5)) << std::endl;
	//std::cout << std::format("int(5.5) = {}", inc(5.5)) << std::endl;
	

	field<"header", int> f;
	std::cout << std::format("field name: {}", f.getName()) << std::endl;

	field<"payload", int>::position<10, 20> pos;
	std::cout << std::format("position name: {}", pos.getName()) << std::endl;


	std::cout << std::format("check type for: char={}, unsigned char={}, short int={}, int={}",
		check_type_size<char>(), check_type_size<unsigned char>(), check_type_size<short int>(), check_type_size<int>()
	) << std::endl;

	std::cout << std::format("test_local_const: {}", test_local_const()) << std::endl;

	B b;
	static_assert(std::is_move_constructible_v<B>);
	A ab(b);

	C c;
	static_assert(!std::is_move_constructible_v<C>);
	//A ac(c);
	
/*
	reg<uint32_t, 0x00000001>::bit<31> b_31;
	Uart<0x00000008> uart1;
	auto cr = uart1.getControlRegister();

	uart1::cr ccr;
*/
	//b_1.set();
	
	using uart1 = Uart<0x00000008>;

	uart1::cr::bit<7>::set();
	uart1::cr::bit_group<0, 2>::setValue(0x02);

	uint8_t buffer[32];

	// Static
	uart1::setMode();
	uart1::setSpeed();

	DataTransmitter<uart1> dt;
	dt.transmit(buffer, sizeof(buffer));

	// Dynamic
	uart1 uart1Inst;
	uart1Inst.setModeInst();
	uart1Inst.setSpeedInst();
	DataTransmitterDynamic<uart1> dtdyn(uart1Inst);
	dtdyn.transmit(buffer, sizeof(buffer));
	


	return EXIT_SUCCESS;
}
