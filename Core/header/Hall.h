#pragma once
#include <fstream>
#include "Helpers/header/MyVector.hpp"

class Hall
{
public:
	static void setNextId(int nextId);

	Hall();
	Hall(size_t rows, size_t cols);

	int getId() const;
	size_t getRows() const;
	size_t getCols() const;

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

private:
	static int s_nextId;
	int id;

	size_t rows;
	size_t cols;
};

