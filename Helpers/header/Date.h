#pragma once
class Date
{
public:
	Date();

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool isPast() const;

    // override necessary operators for comparision

private:
	int day, month, year;
};

