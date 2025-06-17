#pragma once
#include "Core/header/Movie.h"

class DramaMovie : public Movie
{
public:
	DramaMovie();
	DramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, bool hasComedyElements);

	void print() const override;

	Movie* clone() const override;
	Genre getGenre() const override;
	double getTicketPrice() const override;

	void saveToBinaryFile(std::ofstream& ofs) const override;
	void loadFromBinaryFile(std::ifstream& ifs) override;

private:
	bool hasComedyElements;

	static constexpr double BASE_PRICE = 7.00;
};

