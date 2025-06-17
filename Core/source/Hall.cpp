#include "Core/header/Hall.h"
#include <iostream>
#include "Helpers/header/MyString.h"

int Hall::s_nextId = 1;

void Hall::setNextId(int nextId)
{
	s_nextId = nextId;
}

Hall::Hall() : id(-1), rows(0), cols(0) {}
Hall::Hall(size_t rows, size_t cols) : rows(rows), cols(cols), id(s_nextId++) {}

int Hall::getId() const
{
	return id;
}
size_t Hall::getRows() const
{
	return rows;
}
size_t Hall::getCols() const
{
	return cols;
}

void Hall::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&id, sizeof(id));
	ofs.write((const char*)&rows, sizeof(rows));
	ofs.write((const char*)&cols, sizeof(cols));
}
void Hall::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof(id));
	ifs.read((char*)&rows, sizeof(rows));
	ifs.read((char*)&cols, sizeof(cols));
}