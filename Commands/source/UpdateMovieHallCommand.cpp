#include "Commands/header/UpdateMovieHallCommand.h"

void UpdateMovieHallCommand::execute(System* system) const
{
	int movieId, hallId;

	std::cin >> movieId >> hallId;

	try {
		system->updateMovieHall(movieId, hallId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
