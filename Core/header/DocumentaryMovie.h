#pragma once
#include "Core/header/Movie.h"
#include "Helpers/header/Utilities.h"

class DocumentaryMovie : public Movie
{
public:
	DocumentaryMovie();
	DocumentaryMovie(const MyString& title, unsigned releaseYear, unsigned duration, Theme theme, bool isBasedOnTrueEvents);

	void print() const override;

	Movie* clone() const override;
	Genre getGenre() const override;
	double getTicketPrice() const override;

	Theme getTheme() const;

	void saveToBinaryFile(std::ofstream& ofs) const override;
	void loadFromBinaryFile(std::ifstream& ifs) override;

private:
	Theme theme;
	bool isBasedOnTrueEvents;

	static constexpr double BASE_PRICE = 5.00;
};

