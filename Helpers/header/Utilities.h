#pragma once
#include "Helpers/header/MyString.h"

namespace Constants {
	const int MIN_MOVIE_RATING = 0;
	const int MAX_MOVIE_RATING = 5;
	const unsigned MIN_ACTION_INTENSITY = 0;
	const unsigned MAX_ACTION_INTENSITY = 20;
}

size_t getFileSize(std::ifstream& file);

enum class Role {
	Admin,
	Regular,
	Invalid
};
enum class Genre {
	Action,
	Drama,
	Documentary,
	Invalid
};
enum class Theme {
	Nature,
	History,
	HistoricalFigure,
	Invalid
};

MyString genreToString(Genre genre);
MyString roleToString(Role role);
MyString themeToString(Theme theme);
Genre stringToGenre(const MyString& genreStr);
Theme stringToTheme(const MyString& themeStr);