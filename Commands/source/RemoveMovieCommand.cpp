#include "Commands/header/RemoveMovieCommand.h"

void RemoveMovieCommand::execute(System* system) const
{
	int movieId;
	
	std::cin >> movieId;

	try {
		system->removeMovie(movieId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
