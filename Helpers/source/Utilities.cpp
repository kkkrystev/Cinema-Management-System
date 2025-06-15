#include "Helpers/header/Utilities.h"

bool validateName(const MyString& name)
{
	return true;
}
bool validatePassword(const MyString& password)
{
	return true;
}

MyString roleToString(Role role)
{
	switch (role) {
	case Role::Admin  : return MyString("Admin");
	case Role::Regular: return MyString("Regular");
	default			  : return MyString("Unknown");
	}
}

MyString themeToString(Theme theme)
{
	switch (theme) {
	case Theme::Nature			: return MyString("Nature");
	case Theme::History			: return MyString("History");
	case Theme::HistoricalFigure: return MyString("HistoricalFigure");
	default						: return MyString("Unknown");
	}
}
