#include "Helpers/header/TimeInterval.h"

std::ostream& operator<<(std::ostream& os, const TimeInterval& timeInterval)
{
    return os << timeInterval.start << '-' << timeInterval.end;
}

bool doIntervalsOverlap(const TimeInterval& lhs, const TimeInterval& rhs)
{
    return lhs.start < rhs.end && rhs.start < lhs.end;
}

TimeInterval::TimeInterval() : start(0, 0), end(0, 0) {}
TimeInterval::TimeInterval(const Time& start, const Time& end) : start(start), end(end) {}

void TimeInterval::saveToBinaryFile(std::ofstream& ofs) const
{
    start.saveToBinaryFile(ofs);
    end.saveToBinaryFile(ofs);
}
void TimeInterval::loadFromBinaryFile(std::ifstream& ifs)
{
    start.loadFromBinaryFile(ifs);
    end.loadFromBinaryFile(ifs);
}
