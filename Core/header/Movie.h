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
	Movie(const MyString& title, int releaseYear, int duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours);
	virtual ~Movie() = default;

	int getMovieId() const;
	int getHallId() const;
	const MyString& getTile() const;
	double getRating() const;
	int getDuration() const;
	int getReleaseYear() const;

	virtual Genre getGenre() const = 0;
	virtual double getTicketPrice() const = 0;

protected:
	static int s_nextId;
	int id;

	MyString title;
	int releaseYear;
	int duration; // in minutes
	int hallId;
	Date screeningDate;
	TimeInterval screeningHours;

	double rating;
};