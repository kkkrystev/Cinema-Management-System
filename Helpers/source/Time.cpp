#include "Helpers/header/Time.h"
#include <ctime>

Time::Time() 
{
	time_t now = time(0);
	tm local;
	localtime_s(&local, &now);

	hour = local.tm_hour;
	minutes = local.tm_min;
}
Time::Time(int hour, int minutes) : hour(hour), minutes(minutes) {}

int Time::getHour() const
{
	return hour;
}
int Time::getMinutes() const
{
	return minutes;
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