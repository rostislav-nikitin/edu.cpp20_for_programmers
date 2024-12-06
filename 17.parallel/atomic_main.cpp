import <iostream>;
import <cstdlib>;
import <atomic>;
import <thread>;

int main(int argc, char *argv[])
{
	int x = 0;
	std::atomic<int> y = 0;

	std::jthread t1 = std::jthread([&]() 
	{
		for(int i = 0; i < 1000; ++i)
		{
			++x;
			++y;
		}
	});

	std::jthread t2 = std::jthread([&]() 
	{
		for(int i = 0; i < 1000; ++i)
		{
			++x;
			++y;
		}
	});

	t1.join();
	t2.join();

	std::cout << "x = " << x << ", y = " << y << std::endl;

	return EXIT_SUCCESS;
}
