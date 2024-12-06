export module locking.shared;

import <shared_mutex>;

export namespace Locking
{
	class SharedData
	{
	public:
		SharedData(int initialValue = {});

		int get() const;
		void set(int value);
	private:
		int value_;
		mutable std::shared_mutex mutex_;
		//mutable std::mutex mutex_;
	};
}
