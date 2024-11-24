#include <iostream>
#include <stdexcept>

// Function try in constructor
class A
{
public:
	A()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		throw std::runtime_error("Error when constructing A.");
	}
};

class B : public A
{
public:
	B() try : A()
	{
	}
	catch(std::runtime_error const &ex)
	{
		throw;
	}
};


// Functional try in destructor
class C
{
public:
   	~C()
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		throw std::runtime_error("Error when destructing C.");
	}
};

class D : public C
{
public:
	~D() try
	{
	}
	catch(std::runtime_error const &ex)
	{
		std::cout << ex.what() << std::endl;
	}
};



int main(int argc, char *argv[])
{
	try
	{
		B b;
	}
	catch(std::runtime_error const &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	//D d;

	int *i = new(std::nothrow)int(10);

	delete i;

	return EXIT_SUCCESS;
}
