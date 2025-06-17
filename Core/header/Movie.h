#pragma once
#include "Helpers/header/Date.h"
#include "Helpers/header/MyString.h"
#include "Helpers/header/TimeInterval.h"
#include "Helpers/header/Utilities.h"

class Movie
{
public:
	static void setNextId(int nextId);

	Movie();
	Movie(const MyString& title, unsigned releaseYear, unsigned duration);
	virtual ~Movie() = default;

	virtual Movie* clone() const = 0;
	virtual Genre getGenre() const = 0;
	virtual double getTicketPrice() const = 0;
	virtual void print() const;

	int getId() const;
	const MyString& getTitle() const;
	unsigned getReleaseYear() const;
	unsigned getDuration() const;

	void setTitle(const MyString& title);
	void addToRating(unsigned rating);

	virtual void saveToBinaryFile(std::ofstream& ofs) const;
	virtual void loadFromBinaryFile(std::ifstream& ifs);

protected:
	static int s_nextId;
	int id;

	MyString title;
	unsigned releaseYear;
	unsigned duration; // in minutes

	double averageRating;
	size_t ratingsCount;
};