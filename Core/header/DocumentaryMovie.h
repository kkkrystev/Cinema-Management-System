#pragma once
#include "Core/header/Movie.h"
#include "Helpers/header/Utilities.h"

class DocumentaryMovie : public Movie
{
public:
	DocumentaryMovie(const MyString& title, int releaseYear, int duration, int hallId, 
		const Date& screeningDate, const TimeInterval& screeningHours, Theme theme, bool isBasedOnTrueEvents);

	Genre getGenre() const override;
	double getTicketPrice() const override;

	Theme getTheme() const;

private:
	Theme theme;
	bool isBasedOnTrueEvents;

	static constexpr double BASE_PRICE = 5.00;
};

