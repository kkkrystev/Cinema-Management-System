#pragma once
#include "Helpers/header/Time.h"
#include <fstream>

struct TimeInterval
{
public:
	Time start;
	Time end;

	TimeInterval();
	TimeInterval(const Time& start, const Time& end);

	friend std::ostream& operator<<(std::ostream& os, const TimeInterval& timeInterval);

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

	friend bool doIntervalsOverlap(const TimeInterval& lhs, const TimeInterval& rhs);
};

