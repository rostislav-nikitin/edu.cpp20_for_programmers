#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <stop_token>
#include <atomic>
#include <semaphore>

int main(int argc, char *argv[])
{
	constexpr int ThreadsCount = 6;
	constexpr int ParallelThreadsCount = 2;

	std::atomic<int> acquiredCount = 0;

	std::array<std::jthread, ThreadsCount> threads;
	std::stop_source stopSource;
	std::counting_semaphore semaphore(ParallelThreadsCount);



	auto l = [&](int id, std::stop_token stopToken)
	{
		while(!stopToken.stop_requested())
		{
			semaphore.acquire();
			acquiredCount++;

			std::cout << "Thread #" << id << " semaphore acquired [" << acquiredCount << "]." << std::endl;

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			acquiredCount--;
			std::cout << "Thread #" << id << " semaphore released [" << acquiredCount << "]." << std::endl;
			semaphore.release();

		}
	};

	for(int i = 0; i < ThreadsCount; ++i)
		threads[i] = std::jthread(l, i + 1, stopSource.get_token());

	std::this_thread::sleep_for(std::chrono::seconds(8));

	stopSource.request_stop();

	std::this_thread::sleep_for(std::chrono::seconds(3));

	return EXIT_SUCCESS;
}
