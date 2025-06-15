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
    return isPast(day, month, year);
}

void Date::saveToBinaryFile(std::ofstream& ofs) const
{
    ofs.write((const char*)&day, sizeof(day));
    ofs.write((const char*)&month, sizeof(month));
    ofs.write((const char*)&year, sizeof(year));
}

void Date::loadFromBinaryFile(std::ifstream& ifs)
{
    ifs.read((char*)&day, sizeof(day));
    ifs.read((char*)&month, sizeof(month));
    ifs.read((char*)&year, sizeof(year));
}

bool Date::isPast(int day, int month, int year)
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
bool Date::isValid(int day, int month, int year)
{
    if (month < 0 || day < 0 || year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31 };

    if (isLeapYear(year)) daysInMonth[1] = 29;

    return day <= daysInMonth[month - 1];

}
bool Date::isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    if (date.day < 10) os << '0';
    os << date.day << '-';

    if (date.month < 10) os << '0';
    os << date.month << '-';

    os << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
    unsigned d, m, y;
    char dash1, dash2;
    if (is >> d >> dash1 >> m >> dash2 >> y && dash1 == '-' && dash2 == '-')
    {
        if (Date::isValid(d, m, y))
            date = Date(d, m, y);
        else
            date = Date(-1, -1, -1);
    }
    else
        date = Date();
    return is;
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
