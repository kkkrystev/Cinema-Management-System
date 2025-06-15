#pragma once
#include "Helpers/header/Date.h"
#include "Helpers/header/MyString.h"
#include "Helpers/header/TimeInterval.h"

enum class Genre {
	Action,
	Drama,
	Documentary
};

class Movie
{
public:
	Movie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours);
	virtual ~Movie() = default;

	int getId() const;
	int getHallId() const;
	const MyString& getTitle() const;
	const Date& getScreeningDate() const;
	const TimeInterval& getScreeningHours() const;

	void addToRating(int rating);

	virtual Genre getGenre() const = 0;
	virtual double getTicketPrice() const = 0;

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