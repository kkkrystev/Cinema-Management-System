#pragma once
class Time
{
public:
	Time();
	Time(unsigned hour, unsigned minutes);

	unsigned getHour() const;
	unsigned getMinutes() const;

	unsigned toMinutes() const;

	friend bool operator<(const Time& lhs, const Time& rhs);
	friend bool operator>(const Time& lhs, const Time& rhs);
	friend bool operator==(const Time& lhs, const Time& rhs);
	friend bool operator!=(const Time& lhs, const Time& rhs);
	friend bool operator<=(const Time& lhs, const Time& rhs);
	friend bool operator>=(const Time& lhs, const Time& rhs);

private:
	unsigned hour, minutes;

	static bool isValid(unsigned hour, unsigned minutes);
};

