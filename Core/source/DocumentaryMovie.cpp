#include "Core/header/DocumentaryMovie.h"

DocumentaryMovie::DocumentaryMovie() : Movie(), theme(Theme::Unknown), isBasedOnTrueEvents(false) {}

DocumentaryMovie::DocumentaryMovie(const MyString& title, int releaseYear, int duration, int hallId,
	const Date& screeningDate, const TimeInterval& screeningHours, Theme theme, bool isBasedOnTrueEvents)
	: Movie(title, releaseYear, duration, hallId, screeningDate, screeningHours), theme(theme), isBasedOnTrueEvents(isBasedOnTrueEvents) {}

Movie* DocumentaryMovie::clone() const
{
	return new DocumentaryMovie(*this);
}
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

void DocumentaryMovie::saveToBinaryFile(std::ofstream& ofs) const
{
	Movie::saveToBinaryFile(ofs);
	ofs.write((const char*)&theme, sizeof(theme));
	ofs.write((const char*)&isBasedOnTrueEvents, sizeof(isBasedOnTrueEvents));
}
void DocumentaryMovie::loadFromBinaryFile(std::ifstream& ifs)
{
	Movie::loadFromBinaryFile(ifs);
	ifs.read((char*)&theme, sizeof(theme));
	ifs.read((char*)&isBasedOnTrueEvents, sizeof(isBasedOnTrueEvents));
}


