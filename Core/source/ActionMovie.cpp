#include "Core/header/ActionMovie.h"

ActionMovie::ActionMovie() : Movie(), actionIntensity(0) {}

ActionMovie::ActionMovie(const MyString& title, unsigned releaseYear, unsigned duration, unsigned actionIntensity)
	: Movie(title, releaseYear, duration), actionIntensity(actionIntensity) {}

void ActionMovie::print() const
{
	Movie::print();
	std::cout << " | ActionIntensity: " << actionIntensity;
}

Movie* ActionMovie::clone() const
{
	return new ActionMovie(*this);
}

Genre ActionMovie::getGenre() const
{
	return Genre::Action;
}

double ActionMovie::getTicketPrice() const
{
	return BASE_PRICE + actionIntensity * 1.5;
}

void ActionMovie::saveToBinaryFile(std::ofstream& ofs) const
{
	Movie::saveToBinaryFile(ofs);
	ofs.write((const char*)&actionIntensity, sizeof(actionIntensity));
}

void ActionMovie::loadFromBinaryFile(std::ifstream& ifs)
{
	Movie::loadFromBinaryFile(ifs);
	ifs.read((char*)&actionIntensity, sizeof(actionIntensity));
}

