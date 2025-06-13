#include "Helpers/header/Time.h"

Time::Time() : hour(-1), minutes(-1) {}
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