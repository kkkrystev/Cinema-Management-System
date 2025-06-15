#pragma once
#include "Core/header/Movie.h"

class DramaMovie : public Movie
{
public:
	DramaMovie();
	DramaMovie(const MyString& title, int releaseYear, int duration, int hallId, 
		const Date& screeningDate, const TimeInterval& screeningHours, bool hasComedyElements);

	Movie* clone() const override;
	Genre getGenre() const override;
	double getTicketPrice() const override;

	void saveToBinaryFile(std::ofstream& ofs) const override;
	void loadFromBinaryFile(std::ifstream& ifs) override;

private:
	bool hasComedyElements;

	static constexpr double BASE_PRICE = 7.00;
};

