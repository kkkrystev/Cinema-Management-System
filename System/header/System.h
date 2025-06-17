#pragma once
#include "Helpers/header/MyVector.hpp"
#include "Helpers/header/MyString.h"
#include "Helpers/header/PolymorphicPtr.hpp"
#include "User/header/User.h"
#include "User/header/Admin.h"
#include "User/header/RegularUser.h"
#include "Core/header/Hall.h"
#include "Core/header/Screening.h"
#include "Core/header/Movie.h"
#include "Core/header/ActionMovie.h"
#include "Core/header/DramaMovie.h"
#include "Core/header/DocumentaryMovie.h"

class System
{
public:
	static System& getInstance();
	~System();

	// Non-restrict
	void registerUser(const MyString& name, const MyString& password);
	void login(const MyString& name, const MyString& password);
	void logout();
	void addBalance(double sum);
	void printBalance() const;
	void printScreeningHall(int screeningHall);
	void buyTicket(int screeningId, size_t row, size_t col);
	void rateMovie(int movieId, unsigned rating);
	void listMovies();
	void listScreenings();
	void listHistory();
	void listTickets();

	// Admin-specific
	void addActionMovie(const MyString& title, unsigned releaseYear, unsigned duration, unsigned actionIntensity);
	void addDocumentaryMovie(const MyString& title, unsigned releaseYear, unsigned duration, Theme theme, bool isBasedOnTrueEvents);
	void addDramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, bool hasComedyElements);
	void addScreening(int movieId, int hallId, const Date& date, const Time& start, const Time& end);
	void removeScreening(int screeningId);
	void removeMovie(int movieId);
	void removeUser(int userId);
	void openHall(size_t rows, size_t cols);
	void closeHall(int hallId);
	void updateMovieTitle(int movieId, const MyString& newTitle);
	void updateScreeningHall(int screeningId, int newHallId);
	void listUserHistory(int userId);
	void listUserTickets(int userId);
	void listUsers() const;

private:
	MyVector<PolymorphicPtr<User>> users;
	MyVector<PolymorphicPtr<Movie>> movies;
	MyVector<Screening> screenings;
	MyVector<Hall> halls;

	User* loggedIn;

	System();
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	System(System&&) = delete;
	System& operator=(System&&) = delete;

	// Save & load 
	void saveUsers() const;
	void saveMovies() const;
	void saveScreenings() const;
	void saveHalls() const;
	void loadUsers();
	void loadMovies();
	void loadScreenings();
	void loadHalls();

	// Finders
	User* findUserById(int id);
	User* findUserByName(const MyString& name);
	Movie* findMovieById(int id);
	Screening* findScreeningById(int id);
	Hall* findHallById(int id);

	// Checks
	bool isMovieTitleTaken(const MyString& title) const;
	bool isNameTaken(const MyString& name) const;
	bool isReleaseYearValid(unsigned releaseYear) const;
	bool areScreeningHoursValid(unsigned duration, const Time& start, const Time& end) const;
	bool isScreeningOngoing(const Date& screeningDate, const Time& start, const Time& end) const;
	bool isScreeningInPast(const Date& screeningDate, const Time& start, const Time& end) const;
	bool doOverlappingScreeningsExist(int hallId, const Date& screeningDate, const Time& start, const Time& end) const;
	bool isMovieInCatalogue(int movieId) const;
	bool doesMovieHaveOngoingScreenings(int movieId) const;
	bool doesHallHaveOngoingScreenings(int hallId) const;

	// Isolated and repetitive logic
	void cleanupExpiredScreenings();
	void removeScreeningFromList(int screeningId);
	void removeMovieFromList(int movieId);
	void removeHallFromList(int hallId);
	void returnUsersTickets(Screening* screening);
	void addToUserCatalogues(Screening* screening);
};