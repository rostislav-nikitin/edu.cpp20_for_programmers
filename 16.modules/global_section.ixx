module;
// Global section

#include <iostream>
#include <string>

export module global.section;

export namespace global::section
{
	void print(std::string message);
}

void global::section::print(std::string message)
{
	std::cout << message << std::endl;
}
