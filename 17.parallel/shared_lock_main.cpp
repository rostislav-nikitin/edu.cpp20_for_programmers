import <iostream>;
import <thread>;
import <atomic>;

import locking.shared;


int main(int argc, char *argv[])
{
	using Locking::SharedData;

	std::atomic<int> counter = 0;
	SharedData data(counter++);

	std::cout << "BEGIN" << std::endl;

	auto t1{std::thread([&]()
	{
		for(int i = 0; i < 1000; ++i)
		{
			data.set(counter++);
//			std::this_thread::yield();
		}
	})};

	auto t2{std::thread([&]()
	{
		for(int i = 0; i < 1000; ++i)
			data.get();
	})};


	auto t3{std::thread([&]()
	{
		for(int i = 0; i < 1000; ++i)
			data.get();
	})};

	t1.join();
	t2.join();
	t3.join();

	std::cout << "I'am done!" << std::endl;

	return EXIT_SUCCESS;
}
