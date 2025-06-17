#include "Commands/header/RateMovieCommand.h"

void RateMovieCommand::execute(System* system) const
{
	int movieId;
	unsigned rating;

	std::cin >> movieId >> rating;

	system->rateMovie(movieId, rating);
}
