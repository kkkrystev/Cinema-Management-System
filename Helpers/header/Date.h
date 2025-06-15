#pragma once
class Date
{
public:
    Date();
    Date(unsigned day, unsigned month, unsigned year);

    unsigned getDay() const;
    unsigned getMonth() const;
    unsigned getYear() const;

    bool isPast() const;

    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);

private:
    unsigned day, month, year;
    
    static bool isPast(unsigned day, unsigned month, unsigned year);
    static bool isValid(unsigned day, unsigned month, unsigned year);
    static bool isLeapYear(unsigned year);
};

