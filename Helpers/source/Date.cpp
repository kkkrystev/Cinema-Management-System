#include "Helpers/header/Date.h"
#include <stdexcept>
#include <ctime>

Date::Date() 
{
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);

    day = local.tm_mday;
    month = local.tm_mon + 1;
    year = local.tm_year + 1900;
}
Date::Date(unsigned day, unsigned month, unsigned year)
{
    if (!isValid(day, month, year))
        throw std::invalid_argument("Invalid date provided");

    this->day = day;
    this->month = month;
    this->year = year;
}

unsigned Date::getDay() const
{
    return day;
}
unsigned Date::getMonth() const
{
    return month;
}
unsigned Date::getYear() const
{
    return month;
}

bool Date::isPast() const
{
    isPast(day, month, year);
}

bool Date::isPast(unsigned day, unsigned month, unsigned year)
{
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);

    int currentYear = local.tm_year + 1900;
    int currentMonth = local.tm_mon + 1;
    int currentDay = local.tm_mday;

    if (year < currentYear) return true;
    else if (year == currentYear && month < currentMonth) return true;
    else if (year == currentYear && month == currentMonth && day < currentDay) return true;

    return false;
}
bool Date::isValid(unsigned day, unsigned month, unsigned year)
{
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    unsigned daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    if (isLeapYear(year))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];

}
bool Date::isLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.year < rhs.year) return true;
    else if (lhs.year == rhs.year && lhs.month < rhs.month) return true;
    else if (lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day) return true;

    return false;
}

bool operator>(const Date& lhs, const Date& rhs)
{
    return rhs < lhs;
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.year == rhs.year &&
        lhs.month == rhs.month &&
        lhs.day == rhs.day;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
    return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
    return !(rhs < lhs);
}

bool operator>=(const Date& lhs, const Date& rhs)
{
    return !(lhs < rhs);
}
