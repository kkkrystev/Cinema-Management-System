#pragma once
#include <fstream>

class Ticket
{
public:
	Ticket();
	Ticket(int movieId, size_t row, size_t col);

	int getMovieId() const;
	size_t getRow() const;
	size_t getCol() const;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

private:
	int movieId;
	size_t row;
	size_t col;
};

