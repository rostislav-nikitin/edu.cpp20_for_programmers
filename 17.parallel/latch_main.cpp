#include <cstdlib>
#include <iostream>
#include <thread>
#include <latch>
#include <chrono>

int main(int argc, char *argv[])
{
	std::latch latch(2);

	auto l = [&](int id)
	{
		std::cout << "Thread #" << id << "started." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "Thread #" << id << "finished." << std::endl;
		latch.count_down();
	};

	std::jthread t1(l, 1);
	std::jthread t2(l, 2);

	std::cout << "Main thread waiting for latch." << std::endl;
	latch.wait();
	std::cout << "Main thread latch opened." << std::endl;

	return EXIT_SUCCESS;
}
