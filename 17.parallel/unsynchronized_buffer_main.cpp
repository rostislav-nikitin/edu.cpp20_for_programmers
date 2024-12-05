import <iostream>;
import <format>;
import <thread>;

import buffers.unsynchronized;

int main(int argc, char *argv[])
{
	using Buffers::UnsynchronizedBuffer;

	int counter = 0;
	UnsynchronizedBuffer<int> buf;

	auto t1 = std::jthread([&]()
	{
		for(int i = 0; i < 1'000; ++i)
			std::cout << "buf.get() =" <<  buf.get() << std::endl;
	});
	
	auto t2 = std::jthread([&]()
	{
		for(int i = 0; i < 1'000; ++i)
		{
			buf.set(counter++);
			std::cout << "buf.set()" << std::endl; 
		}
	});

	return EXIT_SUCCESS;
}
