export module composite.one;

export namespace composite
{
	template<typename T>
	class One
	{
	public:
		One(T x);
		T getX() const;
	private:
		T x_;
	};
}

template<typename T>
composite::One<T>::One(T x) : x_(x)
{
}

template<typename T>
T composite::One<T>::getX() const
{
	return x_;
}
