#include "Core/header/DramaMovie.h"

DramaMovie::DramaMovie() : Movie(), hasComedyElements(0) {}

DramaMovie::DramaMovie(const MyString& title, int releaseYear, int duration,
	int hallId, const Date& screeningDate, const TimeInterval& screeningHours, bool hasComedyElements)
	: Movie(title, releaseYear, duration, hallId, screeningDate, screeningHours), hasComedyElements(hasComedyElements) {}

Movie* DramaMovie::clone() const
{
	return new DramaMovie(*this);
}
Genre DramaMovie::getGenre() const
{
	return Genre::Drama;
}
double DramaMovie::getTicketPrice() const
{
	return BASE_PRICE + hasComedyElements * 2.00;
}

void DramaMovie::saveToBinaryFile(std::ofstream& ofs) const
{
	Movie::saveToBinaryFile(ofs);
	ofs.write((const char*)&hasComedyElements, sizeof(hasComedyElements));
}
void DramaMovie::loadFromBinaryFile(std::ifstream& ifs)
{
	Movie::loadFromBinaryFile(ifs);
	ifs.read((char*)&hasComedyElements, sizeof(hasComedyElements));
}
