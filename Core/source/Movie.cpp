#include "Core/header/Movie.h"
#include <fstream>

int Movie::s_nextId = 1;
void Movie::setNextId(int nextId)
{
	s_nextId = nextId;
}

Movie::Movie() : title(), releaseYear(0), duration(0) {}
Movie::Movie(const MyString& title, unsigned releaseYear, unsigned duration)
	: id(s_nextId++), title(title), releaseYear(releaseYear), duration(duration), averageRating(0.0), ratingsCount(0) {}
	
void Movie::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&id, sizeof(id));
	title.saveToBinaryFile(ofs);
	ofs.write((const char*)&releaseYear, sizeof(releaseYear));
	ofs.write((const char*)&duration, sizeof(duration));
	ofs.write((const char*)&averageRating, sizeof(averageRating));
	ofs.write((const char*)&ratingsCount, sizeof(ratingsCount));
}
void Movie::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof(id));
	title.loadFromBinaryFile(ifs);
	ifs.read((char*)&releaseYear, sizeof(releaseYear));
	ifs.read((char*)&duration, sizeof(duration));
	ifs.read((char*)&averageRating, sizeof(averageRating));
	ifs.read((char*)&ratingsCount, sizeof(ratingsCount));
}

void Movie::print() const
{
	std::cout << title
		<< " | Genre: " << genreToString(getGenre())
		<< " | Movie ID: " << id
		<< " | Year: " << releaseYear
		<< " | Duration: " << duration << "min"
		<< " | Ticket price: " << getTicketPrice()
		<< " | Average Rating: " << averageRating
		<< " | Ratings Count: " << ratingsCount;
}

int Movie::getId() const
{
	return id;
}
const MyString& Movie::getTitle() const
{
	return title;
}
unsigned Movie::getReleaseYear() const
{
	return releaseYear;
}
unsigned Movie::getDuration() const
{
	return duration;
}

void Movie::setTitle(const MyString& title)
{
	this->title = title;
}
void Movie::addToRating(unsigned rating)
{
	averageRating = (averageRating * ratingsCount + rating) / (ratingsCount + 1);
	++ratingsCount;
}
