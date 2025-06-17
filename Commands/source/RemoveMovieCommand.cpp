#include "Commands/header/RemoveMovieCommand.h"

void RemoveMovieCommand::execute(System* system) const
{
	int movieId;

	std::cin >> movieId;

	system->removeMovie(movieId);
}
