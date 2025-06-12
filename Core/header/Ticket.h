#pragma once
class Ticket
{
public:
	Ticket(int movieId, int row, int col);

	int getMovieId() const;
	int getRow() const;
	int getCol() const;

private:
	int movieId;
	int row;
	int col;
};

