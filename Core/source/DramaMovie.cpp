#include "Core/header/DramaMovie.h"

DramaMovie::DramaMovie() : Movie(), hasComedyElements(0) {}

DramaMovie::DramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, bool hasComedyElements)
	: Movie(title, releaseYear, duration), hasComedyElements(hasComedyElements) {}

void DramaMovie::print() const
{
	Movie::print();

	if (hasComedyElements)
		std::cout << " | Has comedy elements";
	else
		std::cout << " | Does not have comedy elements";
}

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
