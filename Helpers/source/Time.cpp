#include "Helpers/header/Time.h"
#include <ctime>
#include <stdexcept>

Time::Time() 
{
	time_t now = time(0);
	tm local;
	localtime_s(&local, &now);

	hour = local.tm_hour;
	minutes = local.tm_min;
}
Time::Time(int hour, int minutes)
{
	if (!isValid(hour, minutes))
		throw std::invalid_argument("Invalid time provided");

	this->hour = hour;
	this->minutes = minutes;
}

int Time::getHour() const
{
	return hour;
}
int Time::getMinutes() const
{
	return minutes;
}
int Time::toMinutes() const
{
	return hour * 60 + minutes;
}

void Time::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&hour, sizeof(hour));
	ofs.write((const char*)&minutes, sizeof(minutes));
}

void Time::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&hour, sizeof(hour));
	ifs.read((char*)&minutes, sizeof(minutes));
}

bool Time::isValid(unsigned hour, unsigned minutes)
{
	if (hour > 23 || hour < 0) return false;
	if (minutes > 59 || minutes < 0) return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
	if (time.hour < 10) os << '0';
	os << time.hour << ':';

	if (time.minutes < 10) os << '0';
	os << time.minutes;

	return os;
}
std::istream& operator>>(std::istream& is, Time& time)
{
	int h, m;
	char seperator;
	if (is >> h >> seperator >> m && seperator == ':' && Time::isValid(h, m))
		time = Time(h, m);
	else
		time = Time(-1, -1);
	return is;
}

bool operator<(const Time& lhs, const Time& rhs)
{
	if (lhs.hour < rhs.hour) return true;
	if (lhs.hour == rhs.hour && lhs.minutes < rhs.minutes) return true;
	return false;
}
bool operator>(const Time& lhs, const Time& rhs) {
	return rhs < lhs;
}
bool operator==(const Time& lhs, const Time& rhs) {
	return lhs.hour == rhs.hour && lhs.minutes == rhs.minutes;
}
bool operator!=(const Time& lhs, const Time& rhs) {
	return !(lhs == rhs);
}
bool operator<=(const Time& lhs, const Time& rhs) {
	return !(rhs < lhs);
}
bool operator>=(const Time& lhs, const Time& rhs) {
	return !(lhs < rhs);
}