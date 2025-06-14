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
Date::Date(int day, int month, int year)
{
    if (!isValid(day, month, year))
        throw std::invalid_argument("Invalid date provided");
    if (!isPast(day, month, year))
        throw std::invalid_argument("Date must not be in the past");

    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::getDay() const
{
    return day;
}
int Date::getMonth() const
{
    return month;
}
int Date::getYear() const
{
    return month;
}

bool Date::isPast() const
{
    isPast(day, month, year);
}

bool Date::isPast(int day, int month, int year)
{
    time_t now = time(0);
    tm local;
    localtime_s(&local, &now);

    int currentYear = local.tm_year + 1900;
    int currentMonth = local.tm_mon + 1;
    int currentDay = local.tm_mday;

    if (year < currentYear)
        return true;
    if (year == currentYear && month < currentMonth)
        return true;
    if (year == currentYear && month == currentMonth && day < currentDay)
        return true;

    return false;
}
bool Date::isValid(int day, int month, int year)
{
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    if (isLeapYear(year))
        daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];

}
bool Date::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.year < rhs.year) return true;
    if (lhs.year > rhs.year) return false;

    if (lhs.month < rhs.month) return true;
    if (lhs.month > rhs.month) return false;

    return lhs.day < rhs.day;
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
