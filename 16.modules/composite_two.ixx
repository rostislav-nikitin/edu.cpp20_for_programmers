export module composite.two;

export namespace composite
{
	template<typename T>
	class Two
	{
	public:
		Two(T x);
		T getX() const;
	private:
		T x_;
	};
}

template<typename T>
composite::Two<T>::Two(T x) : x_(x)
{
}

template<typename T>
T composite::Two<T>::getX() const
{
	return x_;
}
