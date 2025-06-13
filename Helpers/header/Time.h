#pragma once
class Time
{
public:
	Time();
	Time(int hour, int minutes);

	int getHour() const;
	int getMinutes() const;

	friend bool operator<(const Time& lhs, const Time& rhs);
	friend bool operator>(const Time& lhs, const Time& rhs);
	friend bool operator==(const Time& lhs, const Time& rhs);
	friend bool operator!=(const Time& lhs, const Time& rhs);
	friend bool operator<=(const Time& lhs, const Time& rhs);
	friend bool operator>=(const Time& lhs, const Time& rhs);

private:
	int hour, minutes;
};

