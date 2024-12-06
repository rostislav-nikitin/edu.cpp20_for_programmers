#include <iostream>
#include <array>
#include <stop_token>
#include <thread>

void t(int number, std::stop_token stopToken)
{
	std::cout << "Thread #" << number << " started." << std::endl;
	while(!stopToken.stop_requested())
	{
		std::cout << "Thread #" << number << " alive." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "Thread #" << number << " end." << std::endl;
}

int main(int argc, char *argv[])
{
	std::array<std::thread, 2> threads;
	std::stop_source stopSource;

	std::stop_callback callback(stopSource.get_token(), [](){ std::cout << "Stop callback called." << std::endl; });

	std::cout << "Threads creating started." << std::endl;

	for(int i = 0; i < 2; ++i)
		threads[i] = std::thread(t, i + 1, stopSource.get_token());

	std::cout << "Threads creating finished." << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(5));

	stopSource.request_stop();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	for(int i = 0; i < 2; ++i)
		threads[i].join();

	return EXIT_SUCCESS;
}
