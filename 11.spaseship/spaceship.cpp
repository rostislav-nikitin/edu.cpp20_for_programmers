#include <iostream>
#include <format>

class Time
{
public:
	Time(int hour, int minute, int second) :
		hour_(hour), minute_(minute), second_(second)
	{
	}

	int getHour() const { return hour_; }
	int getMinute() const { return minute_; }
	int getSecond() const { return second_; }

	constexpr auto operator <=>(const Time &) const noexcept = default;
private:
	int hour_;
	int minute_;
	int second_;
};

int main(int argc, char *argv[])
{
	Time before(19, 37, 10);
	Time after(19, 45, 0);

	std::cout << std::format("before < after = {}", before < after) << std::endl;
	std::cout << std::format("before > after = {}", before > after) << std::endl;
	std::cout << std::format("before == after = {}", before == after) << std::endl;
	std::cout << std::format("before <= after = {}", before <= after) << std::endl;
	std::cout << std::format("before => after = {}", before >= after) << std::endl;
	std::cout << std::format("before != after = {}", before != after) << std::endl;

	return EXIT_SUCCESS;
}
