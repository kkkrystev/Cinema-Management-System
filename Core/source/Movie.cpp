#include "Core/header/Movie.h"
#include <fstream>

int Movie::s_nextId = 1;

Movie::Movie() : title(""), releaseYear(0), duration(0), hallId(-1), screeningDate(1, 1, 0), screeningHours(), 
	id(-1), averageRating(0.0), ratingsCount(0) {}

Movie::Movie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours)
	: title(title), releaseYear(releaseYear), duration(duration), 
	hallId(hallId), screeningDate(screeningDate), screeningHours(screeningHours), 
	id(s_nextId++), averageRating(0.0), ratingsCount(0) {}

void Movie::printInfo() const
{
	std::cout << "Title: " << title
		<< " | Year: " << releaseYear
		<< " | Duration: " << duration << "min"
		<< " | Hall: ";

	if (hallId == -1)
		std::cout << "Unknown";
	else
		std::cout << hallId;

	std::cout << " | Date: " << screeningDate
		<< " | Time: " << screeningHours
		<< " | Avg Rating: " << averageRating
		<< " | Ratings: " << ratingsCount;
}

void Movie::saveToBinaryFile(std::ofstream& ofs) const
{
	title.saveToBinaryFile(ofs);
	ofs.write((const char*)&releaseYear, sizeof(releaseYear));
	ofs.write((const char*)&duration, sizeof(duration));
	ofs.write((const char*)&hallId, sizeof(hallId));
	screeningDate.saveToBinaryFile(ofs);
	screeningHours.saveToBinaryFile(ofs);
	ofs.write((const char*)&averageRating, sizeof(averageRating));
	ofs.write((const char*)&ratingsCount, sizeof(ratingsCount));
	ofs.write((const char*)&id, sizeof(id));
}
void Movie::loadFromBinaryFile(std::ifstream& ifs)
{
	title.loadFromBinaryFile(ifs);
	ifs.read((char*)&releaseYear, sizeof(releaseYear));
	ifs.read((char*)&duration, sizeof(duration));
	ifs.read((char*)&hallId, sizeof(hallId));
	screeningDate.loadFromBinaryFile(ifs);
	screeningHours.loadFromBinaryFile(ifs);
	ifs.read((char*)&averageRating, sizeof(averageRating));
	ifs.read((char*)&ratingsCount, sizeof(ratingsCount));
	ifs.read((char*)&id, sizeof(id));
}

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

void Movie::setHallId(int hallId)
{
	this->hallId = hallId;
}

void Movie::setTitle(const MyString& title)
{
	this->title = title;
}

void Movie::setNextId(int nextId)
{
	s_nextId = nextId;
}

void Movie::addToRating(unsigned rating)
{
	averageRating = (averageRating * ratingsCount + rating) / (ratingsCount + 1);
	++ratingsCount;
}
