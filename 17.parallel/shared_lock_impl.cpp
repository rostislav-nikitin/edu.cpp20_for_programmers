import <iostream>;
import <format>;
import <mutex>;
import <shared_mutex>;
import <thread>;

import locking.shared;

namespace Locking
{
	SharedData::SharedData(int initialValue) : value_(initialValue)
	{
	}

	int SharedData::get() const
	{
		int tmp;
		{
			std::shared_lock<std::shared_mutex> lock(mutex_);
			//std::lock_guard<std::mutex> lock(mutex_);
			std::cout << "[" << value_ << "] [" << std::this_thread::get_id() << "] [SHARED] LOCKED" << std::endl;

			tmp = value_;

			std::cout << "[" << tmp << "] [" << std::this_thread::get_id() << "] [SHARED] UNLOCKED" << std::endl;
			std::flush(std::cout);
		}

		return tmp;

	}

	void SharedData::set(int value)
	{
		{
			std::unique_lock<std::shared_mutex> lock(mutex_);
			//std::lock_guard<std::mutex> lock(mutex_);

			std::cout << "[" << value << "] [" << std::this_thread::get_id() << "] [UNIQUE] LOCKED" << std::endl;

			value_ = value;

			std::cout << "[" << value << "] [" << std::this_thread::get_id() << "] [UNIQUE] UNLOCKED" << std::endl;
			std::flush(std::cout);
		}
	}
}
