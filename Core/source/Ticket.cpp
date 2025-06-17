#include "Core/header/Ticket.h"

Ticket::Ticket() : movieId(-1), row(0), col(0) {}

Ticket::Ticket(int movieId, size_t row, size_t col) : movieId(movieId), row(row), col(col) {}

int Ticket::getMovieId() const
{
	return movieId;
}

size_t Ticket::getRow() const
{
	return row;
}

size_t Ticket::getCol() const
{
	return col;
}

void Ticket::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&movieId, sizeof(movieId));
	ofs.write((const char*)&row, sizeof(row));
	ofs.write((const char*)&col, sizeof(col));
}

void Ticket::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&movieId, sizeof(movieId));
	ifs.read((char*)&row, sizeof(row));
	ifs.read((char*)&col, sizeof(col));
}
