export module buffers.cycle;

import <iostream>;
import <condition_variable>;

export namespace Buffers
{
	template<typename T, int Size>
	class CycleBuffer
	{
	public:
		T get() const;
		void set(T value);
	private:
		mutable std::mutex mutex_;
		mutable std::condition_variable cv_;

		std::array<T, Size> values_;
		mutable size_t count_ = 0;
		mutable size_t readIndex_ = 0;
		mutable size_t writeIndex_ = 0;

	};
}

namespace Buffers
{
	template<typename T, int Size>
	T CycleBuffer<T, Size>::get() const
	{
		std::unique_lock lock(mutex_);
		if(count_ == 0)
		{
			cv_.wait(lock, [&]() { return count_ > 0; });
		}

		T result = values_[readIndex_];

		--count_;

		std::cout << "get() = " << result << ", readIndex_ = " << readIndex_ << ", count = " << count_ << std::endl;

		readIndex_ = (++readIndex_) % values_.size();

		cv_.notify_one();
	
		return result;
	}

	template<typename T, int Size>	
	void CycleBuffer<T, Size>::set(T value)
	{
		std::unique_lock lock(mutex_);
		if(count_ == values_.size())
		{
			cv_.wait(lock, [&]() { return count_ < values_.size(); });
		}

		values_[writeIndex_] = value;

		++count_;

		std::cout << "set() = " << value << ", writeIndex_ = " << writeIndex_ << ", count = " << count_ << std::endl;

		writeIndex_ = (++writeIndex_) % values_.size();

		cv_.notify_one();
	}
}
