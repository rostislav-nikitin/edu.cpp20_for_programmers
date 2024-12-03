#include <iostream>
#include <string>

import global.section;

int main(int argc, char *argv[])
{
	std::cout << "Global section example" << std::endl;
	std::string message = "Test message";
	global::section::print(message);

	return EXIT_SUCCESS;
}
