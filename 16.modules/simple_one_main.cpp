import <iostream>;
import simple.one;

int main(int argc, char *argv[])
{
	std::cout << "sum(10, 20) = " << sum(10, 20) << "\n";
	std::cout << "sub(10, 20) = " << sub(10, 20) << "\n";
	std::cout << "simple::one::sum(10, 20) = " << simple::one::sum(10, 20) << "\n";
	std::cout << "simple::two::sum(10, 20) = " << simple::two::sum(10, 20) << "\n";
	//std::cout << "simple::two::sub(10, 20) = " << simple::two::sub(10, 20) << "\n";

	return EXIT_SUCCESS;
}
