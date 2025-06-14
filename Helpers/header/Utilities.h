#pragma once
#include "Helpers/header/MyString.h"

namespace Constants {
	const int MIN_MOVIE_RATING = 0;
	const int MAX_MOVIE_RATING = 5;
}

bool validateName(const MyString& name);
bool validatePassword(const MyString& name);

enum class Role {
	Admin,
	Regular
};

MyString roleToString(Role role);