#pragma once
#include <fstream>

class Ticket
{
public:
	Ticket();
	Ticket(int movieId, int row, int col);

	int getMovieId() const;
	int getRow() const;
	int getCol() const;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

private:
	int movieId;
	int row;
	int col;
};

