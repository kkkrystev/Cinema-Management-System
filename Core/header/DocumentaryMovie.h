#pragma once
#include "Movie.h"

enum class Theme {
	Nature,
	History,
	HistoricalFigure
};

class DocumentaryMovie : public Movie
{
public:
	DocumentaryMovie();

	Genre getGenre() const override;
	double getTicketPrice() const override;

	Theme getTheme() const;

private:
	Theme theme;
	bool isBasedOnTrueEvents;

	static constexpr double BASE_PRICE = 5.00;
};

