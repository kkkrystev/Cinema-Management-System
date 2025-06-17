#include "Core/header/Ticket.h"

Ticket::Ticket() : screeningId(-1), row(0), col(0) {}

Ticket::Ticket(int screeningId, size_t row, size_t col) : screeningId(screeningId), row(row), col(col) {}

int Ticket::getScreeningId() const
{
	return screeningId;
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
	ofs.write((const char*)&screeningId, sizeof(screeningId));
	ofs.write((const char*)&row, sizeof(row));
	ofs.write((const char*)&col, sizeof(col));
}

void Ticket::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&screeningId, sizeof(screeningId));
	ifs.read((char*)&row, sizeof(row));
	ifs.read((char*)&col, sizeof(col));
}
