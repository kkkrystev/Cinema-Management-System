#pragma once
#include <fstream>

class Time
{
public:
	Time();
	Time(int hour, int minutes);

	int getHour() const;
	int getMinutes() const;

	int toMinutes() const;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

	friend std::ostream& operator<<(std::ostream& os, const Time& time);
	friend std::istream& operator>>(std::istream& is, Time& time);

	friend bool operator<(const Time& lhs, const Time& rhs);
	friend bool operator>(const Time& lhs, const Time& rhs);
	friend bool operator==(const Time& lhs, const Time& rhs);
	friend bool operator!=(const Time& lhs, const Time& rhs);
	friend bool operator<=(const Time& lhs, const Time& rhs);
	friend bool operator>=(const Time& lhs, const Time& rhs);

private:
	int hour, minutes;

	static bool isValid(unsigned hour, unsigned minutes);
};

