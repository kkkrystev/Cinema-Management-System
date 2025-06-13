#include "Core/header/ActionMovie.h"

ActionMovie::ActionMovie(const MyString& title, int releaseYear, int duration, int hallId, 
	const Date& screeningDate, const TimeInterval& screeningHours, unsigned actionIntensity)
	: Movie(title, releaseYear, duration, hallId, screeningDate, screeningHours), actionIntensity(actionIntensity) {}

Genre ActionMovie::getGenre() const
{
	return Genre::Action;
}

double ActionMovie::getTicketPrice() const
{
	return BASE_PRICE + actionIntensity * 1.5;
}

