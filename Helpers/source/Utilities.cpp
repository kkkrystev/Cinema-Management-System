#include "Helpers/header/Utilities.h"
#include <fstream>;

size_t getFileSize(std::ifstream& file)
{
	size_t currPos = file.tellg();
	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(currPos);
	return fileSize;
}

MyString genreToString(Genre genre)
{
	switch (genre) {
	case Genre::Action		: return MyString("Action");
	case Genre::Drama		: return MyString("Drama");
	case Genre::Documentary : return MyString("Documentary");
	default					: return MyString("Unknown");
	}
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

Genre stringToGenre(const MyString& genreStr)
{
	if (genreStr == "Action" || genreStr == "action")				 return Genre::Action;
	else if (genreStr == "Drama" || genreStr == "drama")			 return Genre::Drama;
	else if (genreStr == "Documentary" || genreStr == "documentary") return Genre::Documentary;
}

Theme stringToTheme(const MyString& themeStr)
{
	if (themeStr == "nature" || themeStr == "Nature") {
		return Theme::Nature;
	}
	else if (themeStr == "history" || themeStr == "History") {
		return Theme::History;
	}
	else if (themeStr == "historical-figure" || themeStr == "Historical-figure") {
		return Theme::HistoricalFigure;
	}
	else {
		return Theme::Unknown;
	}
}
