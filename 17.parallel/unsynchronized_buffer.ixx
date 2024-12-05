export module buffers.unsynchronized;

export namespace Buffers
{
	template<typename T>
	class UnsynchronizedBuffer
	{
	public:
		UnsynchronizedBuffer(T initialValue = {});

		T get() const;
		void set(T value);
	private:
		T value_;
	};
}

namespace Buffers
{
	template<typename T>
	UnsynchronizedBuffer<T>::UnsynchronizedBuffer(T initialValue) : value_(initialValue)
	{
	}

	template<typename T>
	T UnsynchronizedBuffer<T>::get() const
	{
		return value_;
	}

	template<typename T>	
	void UnsynchronizedBuffer<T>::set(T value)
	{
		value_ = value;
	}
}
