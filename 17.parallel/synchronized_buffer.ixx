export module buffers.synchronized;

import <iostream>;
import <condition_variable>;

export namespace Buffers
{
	template<typename T>
	class SynchronizedBuffer
	{
	public:
		T get() const;
		void set(T value);
	private:
		mutable volatile bool occupied_ = false;
		mutable std::mutex mutex_;
		mutable std::condition_variable cv_;

		T value_ = {};
	};
}

namespace Buffers
{
	template<typename T>
	T SynchronizedBuffer<T>::get() const
	{
		std::unique_lock lock(mutex_);
		if(!occupied_)
		{
			cv_.wait(lock, [&]() { return occupied_; });
		}

		T result = value_;
		occupied_ = false;
		std::cout << "get() = " << result << std::endl;
		cv_.notify_one();
	
		return result;
	}

	template<typename T>	
	void SynchronizedBuffer<T>::set(T value)
	{
		std::unique_lock lock(mutex_);
		if(occupied_)
		{
			cv_.wait(lock, [&]() { return !occupied_; });
		}

		value_ = value;
		occupied_ = true;
		std::cout << "set() = " << value_ << std::endl;
		cv_.notify_one();
	}
}
