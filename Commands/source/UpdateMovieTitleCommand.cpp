#include "Commands/header/UpdateMovieTitleCommand.h"

void UpdateMovieTitleCommand::execute(System* system) const
{
	int movieId;
	MyString movieTitle;

	std::cin >> movieId;
	char buffer[1024];
	std::cin.getline(buffer, 1024);
	movieTitle = MyString(buffer);

	try {
		system->updateMovieTitle(movieId, movieTitle);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
