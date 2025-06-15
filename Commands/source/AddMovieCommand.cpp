#include "Commands/header/AddMovieCommand.h"

void AddMovieCommand::execute(System* system) const
{
	MyString genreStr;
	
	std::cin >> genreStr;

	Genre genre = stringToGenre(genreStr);

	MyString title;
	unsigned releaseYear, duration;
	int hallId;
	Date screeningDate;
	Time start, end;
	
	std::cin >> title >> releaseYear >> duration >> hallId >> screeningDate >> start >> end;

	try {
		if (genre == Genre::Action) {
			unsigned actionIntensity;

			std::cin >> actionIntensity;

			system->addActionMovie(title, releaseYear, duration, hallId, screeningDate, start, end, actionIntensity);
		}
		else if (genre == Genre::Documentary){
			MyString themeStr;
			bool isBasedOnTrueEvents;

			std::cin >> themeStr;
			Theme theme = stringToTheme(themeStr);
			std::cin >> isBasedOnTrueEvents;

			system->addDocumentaryMovie(title, releaseYear, duration, hallId, screeningDate, start, end, theme, isBasedOnTrueEvents);
		}
		else if (genre == Genre::Drama) {
			bool hasComedyElements;

			std::cin >> hasComedyElements;

			system->addDramaMovie(title, releaseYear, duration, hallId, screeningDate, start, end, hasComedyElements);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
