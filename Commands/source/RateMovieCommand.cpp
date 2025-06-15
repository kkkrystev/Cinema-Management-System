#include "Commands/header/RateMovieCommand.h"

void RateMovieCommand::execute(System* system) const
{
	int movieId;
	unsigned rating;

	std::cin >> movieId >> rating;

	try {
		system->rateMovie(movieId, rating);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
