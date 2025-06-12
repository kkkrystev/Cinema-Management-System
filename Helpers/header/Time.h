#pragma once
class Time
{
public:
	Time();
	Time(int hour, int minutes);

	int getHour() const;
	int getMinutes() const;

	void setHour();
	void setMinutes();

	// override necessary operators for comparision

private:
	int hour, minutes;
};

