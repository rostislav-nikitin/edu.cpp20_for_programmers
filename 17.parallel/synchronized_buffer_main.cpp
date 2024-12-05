import <iostream>;
import <format>;
import <thread>;

import buffers.synchronized;

int main(int argc, char *argv[])
{
	using Buffers::SynchronizedBuffer;

	int counter = 0;
	SynchronizedBuffer<int> buf;

	auto t1 = std::jthread([&]()
	{
		for(int i = 0; i < 1'000; ++i)
		{
			int value = buf.get();
			//std::cout << "buf.get() = " << value << std::endl;
		}
	});
	
	auto t2 = std::jthread([&]()
	{
		for(int i = 0; i < 1'000; ++i)
		{
			buf.set(counter++);
			//std::cout << "buf.set()" << std::endl; 
		}
	});

	return EXIT_SUCCESS;
}
