#pragma once
#include "Helpers/header/Time.h"

struct TimeInterval
{
	Time start;
	Time end;

	TimeInterval(const Time& start, const Time& end);

	friend bool doIntervalsOverlap(const TimeInterval& lhs, const TimeInterval& rhs);
};

