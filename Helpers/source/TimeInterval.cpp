#include "Helpers/header/TimeInterval.h"

bool doIntervalsOverlap(const TimeInterval& lhs, const TimeInterval& rhs)
{
    return false;
}

TimeInterval::TimeInterval(const Time& start, const Time& end) : start(start), end(end) {}
