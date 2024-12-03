import <iostream>;
import composite;

int main(int argc, char *argv[])
{
	composite::One one(10);
	std::cout << "one.getX() = " << one.getX() << std::endl;

	composite::Two two(20);
	std::cout << "two.getX() = " << two.getX() << std::endl;

	return EXIT_SUCCESS;
}

