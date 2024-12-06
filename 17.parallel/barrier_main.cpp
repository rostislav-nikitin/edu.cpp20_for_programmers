#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <stop_token>
#include <barrier>

int main(int argc, char *argv[])
{
	constexpr int ThreadsCount = 2;

	std::vector<std::thread> threads;
	std::stop_source stopSource;
	std::barrier barrier(ThreadsCount, []() { std::cout << "Phase completed." << std::endl << std::endl; });

	auto l = [&](int id, std::stop_token stopToken)
	{
		std::cout << "Thread #" << id << " started." << std::endl;
		while(!stopToken.stop_requested())
		{
			std::cout << "Thread #" << id << " sleep." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << "Thread #" << id << " arrived and waiting." << std::endl;
			barrier.arrive_and_wait();
		}
	};

	for(int i = 0; i < ThreadsCount; ++i)
		threads.push_back(std::thread(l, i + 1, stopSource.get_token()));


	std::this_thread::sleep_for(std::chrono::seconds(10));

	stopSource.request_stop(); 

	std::this_thread::sleep_for(std::chrono::seconds(2));

	for(int i = 0; i < ThreadsCount; ++i)
		threads[i].join();


	return EXIT_SUCCESS;
}
