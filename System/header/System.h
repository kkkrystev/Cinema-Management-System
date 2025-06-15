#pragma once
#include "Helpers/header/MyVector.hpp"
#include "Helpers/header/MyString.h"
#include "Helpers/header/PolymorphicPtr.hpp"
#include "User/header/User.h"
#include "User/header/Admin.h"
#include "User/header/RegularUser.h"
#include "Core/header/Movie.h"
#include "Core/header/ActionMovie.h"
#include "Core/header/DramaMovie.h"
#include "Core/header/DocumentaryMovie.h"
#include "Core/header/Hall.h"

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
	void buyTicket(int movieId, int row, int col);
	void rateMovie(int movieId, unsigned rating);
	void listMovies() const;
	void listTickets() const;

	// Admin-specific
	void addActionMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, unsigned actionIntensity);
	void addDocumentaryMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, Theme theme, bool isBasedOnTrueEvents);
	void addDramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, bool hasComedyElements);
	void removeMovie(int movieId);
	void removeUser(int userId);
	void openHall(int rows, int cols);
	void closeHall(int hallId);
	void updateMovieTitle(int movieId, const MyString& newTitle);
	void updateMovieHall(int movieId, int newHallId);
	void listUserHistory(int userId) const;
	void listUserTickets(int userId) const;
	void listUsers() const;

private:
	MyVector<PolymorphicPtr<User>> users;
	MyVector<PolymorphicPtr<Movie>> movies;
	MyVector<Hall> halls;

	PolymorphicPtr<User> loggedIn;

	System();
	System(const System&) = delete;
	System& operator=(const System&) = delete;
	System(System&&) = delete;
	System& operator=(System&&) = delete;

	// Save & load 
	void saveUsers() const;
	void saveMovies() const;
	void saveHalls() const;
	void loadUsers();
	void loadMovies();
	void loadHalls();

	// Finders
	PolymorphicPtr<User> findUserById(int id);
	PolymorphicPtr<User> findUserByName(const MyString& name);
	PolymorphicPtr<Movie> findMovieById(int id);
	Hall* findHallById(int id);

	// Checks
	bool isNameTaken(const MyString& name) const;
	bool isDurationValid(unsigned duration, const Time& start, const Time& end) const;
	bool isScreeningOngoing(const Date& screeningDate, const Time& start, const Time& end) const;
	bool isScreeningInPast(const Date& screeningDate, const Time& start, const Time& end) const;
	bool doScreeningsOverlap(int hallId, const Date& screeningDate, const Time& start, const Time& end) const;

	// Isolated and repetitive logic
	void validateMovieInputData(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end);
	void loginAndRoleValidation(Role expected = Role::Regular) const;
	void cleanupExpiredMovies();
	void removeMovieFromList(int movieId);
	void returnUsersTickets(const PolymorphicPtr<Movie>& movie);
	void addToUserCatalogues(int movieId);
};