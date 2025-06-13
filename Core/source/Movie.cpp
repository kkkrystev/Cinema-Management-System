#include "Core/header/Movie.h"

int Movie::s_nextId = 1;

Movie::Movie(const MyString& title, int releaseYear, int duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours)
	: title(title), releaseYear(releaseYear), duration(duration), 
	hallId(hallId), screeningDate(screeningDate), screeningHours(screeningHours), 
	id(s_nextId++), rating(0) {}
