#include "Commands/header/UpdateMovieTitleCommand.h"

void UpdateMovieTitleCommand::execute(System* system) const
{
	int movieId;
	MyString movieTitle;

	std::cin >> movieId;
	char buffer[1024];
	std::cin.getline(buffer, 1024);
	movieTitle = MyString(buffer);

	system->updateMovieTitle(movieId, movieTitle);
}
