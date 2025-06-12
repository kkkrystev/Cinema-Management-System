#pragma once
#include "Movie.h"

class ActionMovie : public Movie
{
public:
	ActionMovie();
	
	Genre getGenre() const override;
	double getTicketPrice() const override;
	
private:
	unsigned actionIntensity;
	
	static constexpr double BASE_PRICE = 9.00;
	static constexpr unsigned MIN_ACTION_INTENSITY = 0;
	static constexpr unsigned MAX_ACTION_INTENSITY = 20;
};

