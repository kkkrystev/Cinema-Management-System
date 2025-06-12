#pragma once

class Catalogue
{
public:
	Catalogue();

	void addMovie(int movieId);

private:
	MyVector<int> movieIds;
};

