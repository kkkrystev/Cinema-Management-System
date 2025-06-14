#pragma once
class Hall
{
public:
	Hall();
	Hall(size_t rows, size_t cols);

	Hall(const Hall& other);
	Hall(Hall&& other);

	Hall& operator=(const Hall& other);
	Hall& operator=(Hall&& other);

	~Hall();

	int getId() const;
	size_t getRows() const;
	size_t getCols() const;

	bool isSeatTaken(size_t row, size_t col);
	void reserveSeat(size_t row, size_t col);
	void freeSeat(size_t row, size_t col);

	void printLayout() const;

private:
	static int s_nextId;
	int id;

	bool** seats;
	size_t rows;
	size_t cols;

	void free();
	void copyFrom(const Hall& other);
	void moveFrom(Hall&& other);
};

