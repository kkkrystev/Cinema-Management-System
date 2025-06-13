#include "Core/header/DramaMovie.h"

DramaMovie::DramaMovie(const MyString& title, int releaseYear, int duration, 
	int hallId, const Date& screeningDate, const TimeInterval& screeningHours, bool hasComedyElements)
	: Movie(title, releaseYear, duration, hallId, screeningDate, screeningHours), 
	hasComedyElements(hasComedyElements) {}

Genre DramaMovie::getGenre() const
{
	return Genre::Drama;
}

double DramaMovie::getTicketPrice() const
{
	return BASE_PRICE + hasComedyElements * 2.00;
}
