#pragma once
#include "Movie.h"

class DramaMovie : public Movie
{
public:
	DramaMovie();

	Genre getGenre() const override;
	double getTicketPrice() const override;

private:
	bool hasComedyElements;

	static constexpr double BASE_PRICE = 7.00;
};

