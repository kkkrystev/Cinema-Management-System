#pragma once
#include "Core/header/Movie.h"

class DramaMovie : public Movie
{
public:
	DramaMovie(const MyString& title, int releaseYear, int duration, int hallId, 
		const Date& screeningDate, const TimeInterval& screeningHours, bool hasComedyElements);

	Genre getGenre() const override;
	double getTicketPrice() const override;

private:
	bool hasComedyElements;

	static constexpr double BASE_PRICE = 7.00;
};

