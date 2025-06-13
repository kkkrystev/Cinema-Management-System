#include "Core/header/DocumentaryMovie.h"

DocumentaryMovie::DocumentaryMovie(const MyString& title, int releaseYear, int duration, int hallId, 
	const Date& screeningDate, const TimeInterval& screeningHours, Theme theme, bool isBasedOnTrueEvents)
	: Movie(title, releaseYear, duration, hallId, screeningDate, screeningHours), theme(theme), isBasedOnTrueEvents(isBasedOnTrueEvents) {}

Genre DocumentaryMovie::getGenre() const
{
	return Genre::Documentary;
}

double DocumentaryMovie::getTicketPrice() const
{
	return BASE_PRICE + isBasedOnTrueEvents * 3.00;
}

Theme DocumentaryMovie::getTheme() const
{
	return theme;
}
