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
Time::Time(unsigned hour, unsigned minutes) 
{
	if (!isValid(hour, minutes))
		throw std::invalid_argument("Invalid time provided");

	this->hour = hour;
	this->minutes = minutes;
}

unsigned Time::getHour() const
{
	return hour;
}
unsigned Time::getMinutes() const
{
	return minutes;
}

unsigned Time::toMinutes() const
{
	return hour * 60 + minutes;
}

bool Time::isValid(unsigned hour, unsigned minutes)
{
	if (hour > 23) return false;
	if (minutes > 59) return false;
	return true;
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