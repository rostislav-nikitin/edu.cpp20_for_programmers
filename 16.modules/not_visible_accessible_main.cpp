import <iostream>;
import not_visible_accessible;

int main(int argc, char *argv[])
{
	auto a = not_visible_accessible::getA(10);
	std::cout << a.getX() << std::endl;
	std::cout << not_visible_accessible::to_string(a) << std::endl;

	return EXIT_SUCCESS;
}

