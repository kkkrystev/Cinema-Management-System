#pragma once
class Ticket
{
public:
	int getMovieId() const;
	int getRow() const;
	int getCol() const;
private:
	int movieId;
	int row;
	int col;
};

