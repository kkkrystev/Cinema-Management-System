#include "Commands/header/ListMoviesCommand.h"

void ListMoviesCommand::execute(System* system) const
{
	system->listMovies();
}
