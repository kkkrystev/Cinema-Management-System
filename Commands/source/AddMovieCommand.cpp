#include "Commands/header/AddMovieCommand.h"

void AddMovieCommand::execute(System* system) const
{
	MyString genreStr;

	std::cin >> genreStr;

	Genre genre = stringToGenre(genreStr);

	MyString title;
	unsigned releaseYear, duration;
	
	std::cin >> title >> releaseYear >> duration;

	if (genre == Genre::Action) {
		unsigned actionIntensity;

		std::cin >> actionIntensity;

		system->addActionMovie(title, releaseYear, duration, actionIntensity);
	}
	else if (genre == Genre::Documentary) {
		MyString themeStr;
		bool isBasedOnTrueEvents;

		std::cin >> themeStr;
		Theme theme = stringToTheme(themeStr);
		std::cin >> isBasedOnTrueEvents;

		system->addDocumentaryMovie(title, releaseYear, duration, theme, isBasedOnTrueEvents);
	}
	else if (genre == Genre::Drama) {
		bool hasComedyElements;

		std::cin >> hasComedyElements;

		system->addDramaMovie(title, releaseYear, duration, hasComedyElements);
	}
}