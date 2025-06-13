#pragma once
class Hall
{
public:
	Hall();
	Hall(int rows, int cols);

	Hall(const Hall& other);
	Hall(Hall&& other);

	Hall& operator=(const Hall& other);
	Hall& operator=(Hall& other);

	~Hall();

	int getId() const;
	int getRows() const;
	int getCols() const;

	void reserveSeat(int row, int col);
	void freeSeat(int row, int col);

	void printLayout() const;

private:
	int hallId;

	bool** seats;
	int rows;
	int cols;

	void free();
	void copyFrom(const Hall& other);
	void moveFrom(Hall&& other);
};

