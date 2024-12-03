import <iostream>;
import partial;

int main(int argc, char *argv[])
{
	std::cout << "one = " << partial::one() << std::endl;
	std::cout << "two = " << partial::two() << std::endl;

	return EXIT_SUCCESS;
}
