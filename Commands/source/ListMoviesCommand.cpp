#include "Commands/header/ListMoviesCommand.h"

void ListMoviesCommand::execute(System* system) const
{
	try {
		system->listMovies();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
