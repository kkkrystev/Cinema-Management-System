#pragma once
#include "Helpers/header/Date.h"
#include "Helpers/header/TimeInterval.h"
#include "Helpers/header/MyString.h"

class Screening
{
public:
	static void setNextId(int nextId);

	Screening();
	Screening(int movieId, int hallId, size_t rows, size_t cols, const Date& date, const TimeInterval& hours);

	Screening(const Screening& other);
	Screening(Screening&& other) noexcept;

	Screening& operator=(const Screening& other);
	Screening& operator=(Screening&& other) noexcept;

	~Screening();

	int getId() const;
	int getMovieId() const;
	int getHallId() const;
	const Date& getDate() const;
	const TimeInterval& getHours() const;
	void print() const;

	bool isSeatTaken(size_t row, size_t col) const;
	void reserveSeat(size_t row, size_t col);
	void freeSeat(size_t row, size_t col);
	void setHallId(int hallId);

	void printSeats() const;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

private:
	static int s_nextId;
	int id;

	int movieId;
	int hallId;	
	Date date;
	TimeInterval hours;

	bool** seats;
	size_t rows, cols;

	void free();
	void copyFrom(const Screening& other);
	void moveFrom(Screening&& other);
};

