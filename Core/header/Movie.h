#pragma once
#include "Helpers/header/Date.h"
#include "Helpers/header/MyString.h"
#include "Helpers/header/TimeInterval.h"
#include "Helpers/header/Utilities.h"

class Movie
{
public:
	Movie();
	Movie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours);
	virtual ~Movie() = default;

	virtual Movie* clone() const = 0;
	virtual Genre getGenre() const = 0;
	virtual double getTicketPrice() const = 0;
	virtual void printAsUpcoming() const;
	virtual void printAsPast() const;

	virtual void saveToBinaryFile(std::ofstream& ofs) const;
	virtual void loadFromBinaryFile(std::ifstream& ifs);

	int getId() const;
	int getHallId() const;
	const MyString& getTitle() const;
	const Date& getScreeningDate() const;
	const TimeInterval& getScreeningHours() const;

	void setHallId(int hallId);
	void setTitle(const MyString& title);
	static void setNextId(int nextId);

	void addToRating(unsigned rating);

protected:
	static int s_nextId;
	int id;

	MyString title;
	unsigned releaseYear;
	unsigned duration; // in minutes
	int hallId;
	Date screeningDate;
	TimeInterval screeningHours;

	double averageRating;
	size_t ratingsCount;
};