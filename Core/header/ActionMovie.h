#pragma once
#include "Core/header/Movie.h"

class ActionMovie : public Movie
{
public:
	ActionMovie();
	ActionMovie(const MyString& title, int releaseYear, int duration, int hallId, const Date& screeningDate, const TimeInterval& screeningHours, unsigned actionIntensity);
	
	Movie* clone() const override;
	Genre getGenre() const override;
	double getTicketPrice() const override;
	
	void saveToBinaryFile(std::ofstream& ofs) const override;
	void loadFromBinaryFile(std::ifstream& ifs) override;

private:
	unsigned actionIntensity;
	
	static constexpr double BASE_PRICE = 9.00;
};

