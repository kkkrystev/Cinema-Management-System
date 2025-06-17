#include "Core/header/Hall.h"
#include <iostream>
#include "Helpers/header/MyString.h"

int Hall::s_nextId = 1;

void Hall::free()
{
	for (size_t i = 0; i < rows; i++) {
		delete[] seats[i];
	}
	delete[] seats;
	seats = nullptr;
}
void Hall::copyFrom(const Hall& other)
{
	id = other.id;

	rows = other.rows;
	cols = other.cols;

	seats = new bool* [rows]();
	for (size_t i = 0; i < rows; i++) {
		seats[i] = new bool[cols];
	}

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			seats[i][j] = other.seats[i][j];
		}
	}
}
void Hall::moveFrom(Hall&& other)
{
	id = other.id;

	rows = other.rows;
	cols = other.cols;

	seats = other.seats;

	other.seats = nullptr;
	other.rows = 0;
	other.cols = 0;
}

Hall::Hall() : id(-1), rows(0), cols(0), seats(nullptr) {}
Hall::Hall(size_t rows, size_t cols)
{
	id = s_nextId++;

	this->rows = rows;
	this->cols = cols;

	seats = new bool* [rows]();
	for (size_t i = 0; i < rows; i++) {
		seats[i] = new bool[cols];
	}

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			seats[i][j] = false;
		}
	}
}

Hall::Hall(const Hall& other)
{
	copyFrom(other);
}
Hall::Hall(Hall&& other) noexcept
{
	moveFrom(std::move(other));
}

Hall& Hall::operator=(const Hall& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
Hall& Hall::operator=(Hall&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Hall::~Hall()
{
	free();
}

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

void Hall::setNextId(int nextId)
{
	s_nextId = nextId;
}

void Hall::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&id, sizeof(id));
	ofs.write((const char*)&rows, sizeof(rows));
	ofs.write((const char*)&cols, sizeof(cols));

	for (size_t i = 0; i < rows; i++) {
		ofs.write((const char*)seats[i], sizeof(bool) * cols);
	}
}
void Hall::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read((char*)&id, sizeof(id));
	ifs.read((char*)&rows, sizeof(rows));
	ifs.read((char*)&cols, sizeof(cols));

	seats = new bool* [rows];
	for (size_t i = 0; i < rows; i++) {
		seats[i] = new bool[cols];
		ifs.read((char*)seats[i], sizeof(bool) * cols);
	}
}

bool Hall::isSeatTaken(size_t row, size_t col)
{
	if (row >= rows || col >= cols)
        throw std::out_of_range("Seat coordinates are out of range");

    return seats[row][col] == true;
}
void Hall::reserveSeat(size_t row, size_t col)
{
	if (row >= rows || col >= cols) 
		throw std::invalid_argument("Such seat does NOT exist in this hall");

	if (isSeatTaken(row, col))
		throw std::logic_error("This seat is already taken");

	seats[row][col] = true;
}
void Hall::freeSeat(size_t row, size_t col)
{
	if (row >= rows || col >= cols)
		throw std::invalid_argument("Such seat does NOT exist in this hall");

	seats[row][col] = false;
}

void Hall::printLayout() const
{
	size_t totalWidth = cols * 3 - 1;  // Each seat + space takes 2 chars, add 1 more for better alignment

	MyString screenLabel = "=== SCREEN ===";
	size_t padding = (totalWidth > screenLabel.getSize()) ? (totalWidth - screenLabel.getSize()) / 2 : 0;

	MyString spaces = "";
	for (size_t i = 0; i < padding; ++i) {
		spaces = spaces + " ";
	}

	MyString line = spaces + screenLabel;

	std::cout << line << "\n\n";

	// Print column numbers aligned to seats
	std::cout << "    ";
	for (size_t c = 0; c < cols; ++c) {
		if (c + 1 < 10)
			std::cout << " " << (c + 1) << " ";
		else
			std::cout << (c + 1) << " ";
	}
	std::cout << '\n';

	for (size_t r = 0; r < rows; ++r) {
		// Align row numbers: 1-digit rows get 2 spaces, 2-digit rows 1 space for same width
		if (r + 1 < 10)
			std::cout << " " << (r + 1) << "  ";
		else
			std::cout << (r + 1) << "  ";

		// Print seats spaced to align under column numbers
		for (size_t c = 0; c < cols; ++c) {
			char seatChar = seats[r][c] ? 'X' : 'O';
			std::cout << " " << seatChar << " ";
		}
		std::cout << '\n';
	}
}
