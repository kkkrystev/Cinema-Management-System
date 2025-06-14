#include "Core/header/Hall.h"
#include <iostream>

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
	rows = other.rows;
	cols = other.cols;

	seats = other.seats;
	other.seats = nullptr;
}

Hall::Hall() : id(-1), rows(0), cols(0), seats(nullptr) {}
Hall::Hall(size_t rows, size_t cols) : rows(rows), cols(cols), id(s_nextId++)
{
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
Hall::Hall(Hall&& other)
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
Hall& Hall::operator=(Hall&& other)
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

bool Hall::isSeatTaken(size_t row, size_t col)
{
	if (row >= rows || col >= cols)
        throw std::out_of_range("Seat coordinates are out of range");

    return seats[row][col];
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
}
