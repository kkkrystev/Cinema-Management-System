#include "Core/header/Movie.h"

int Movie::s_nextId = 1;

Movie::Movie(const MyString& title, int releaseYear, int duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours)
	: title(title), releaseYear(releaseYear), duration(duration), 
	hallId(hallId), screeningDate(screeningDate), screeningHours(screeningHours), 
	id(s_nextId++), averageRating(0.0), ratingsCount(0) {}

int Movie::getId() const
{
	return id;
}

int Movie::getHallId() const
{
	return hallId;
}

const MyString& Movie::getTitle() const
{
	return title;
}

const Date& Movie::getScreeningDate() const
{
	return screeningDate;
}

const TimeInterval& Movie::getScreeningHours() const
{
	return screeningHours;
}

void Movie::addToRating(int rating)
{
	averageRating = (averageRating * ratingsCount + rating) / (ratingsCount + 1);
	++ratingsCount;
}
