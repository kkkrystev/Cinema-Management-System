#pragma once
#include "Helpers/header/MyString.h"

namespace Constants {
	const int MIN_MOVIE_RATING = 0;
	const int MAX_MOVIE_RATING = 5;
	const unsigned MIN_ACTION_INTENSITY = 0;
	const unsigned MAX_ACTION_INTENSITY = 20;
}

bool validateName(const MyString& name);
bool validatePassword(const MyString& name);

enum class Role {
	Admin,
	Regular
};

enum class Theme {
	Nature,
	History,
	HistoricalFigure
};

MyString roleToString(Role role);
MyString themeToString(Theme theme);