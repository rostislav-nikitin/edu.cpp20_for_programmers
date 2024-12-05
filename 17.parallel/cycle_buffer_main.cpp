import <iostream>;
import <format>;
import <thread>;

import buffers.cycle;

int main(int argc, char *argv[])
{
	using Buffers::CycleBuffer;

	int counter = 0;
	CycleBuffer<int, 10> buf;

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
