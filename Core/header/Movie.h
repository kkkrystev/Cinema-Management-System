#pragma once
#include "Date.h"
#include "Time.h"
#include "MyString.h"

enum class Genre {
	Action,
	Drama,
	Documentary
};

class Movie
{
public:
	Movie();
	virtual ~Movie() = default;

	void setHallId(int hallId);
	void setTitle(const MyString& title);
	void setReleaseYear(int releaseYear);
	void setDuration(int duration);
	void setRating(double rating);

	int getMovieId() const;
	int getHallId() const;
	const MyString& getTile() const;
	double getRating() const;
	int getDuration() const;
	int getReleaseYear() const;

	virtual Genre getGenre() const = 0;
	virtual double getTicketPrice() const = 0;

protected:
	int movieId;
	int hallId;

	MyString title;
	int releaseYear;
	int duration; // in minutes
	double rating;

	Date screeningDate;
	Time startHour;
	Time endHour;
};