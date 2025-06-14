#pragma once
#include "Helpers/header/MyVector.hpp"
#include "Helpers/header/MyString.h"
#include "Helpers/header/PolymorphicPtr.hpp"
#include "User/header/User.h"
#include "User/header/Admin.h"
#include "User/header/RegularUser.h"
#include "Core/header/Movie.h"
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
	void buyTicket(int movieId, int row, int col);
	void listMovies() const;
	void listTickets() const;
	void rateMovie(int movieId, int rating);

	void addBalance(double sum);

	// Admin-specific
	void addMovie(Genre genre);
	void removeMovie(int movieId);
	void updateMovieTitle(int movieId, const MyString& newTitle);
	void openHaul(int rows, int cols);
	void closeHaul(int haulId);
	void updateMovieHaul(int movieId, int newHaulId);

	void listUserHistory(int userId) const;
	void listUserTickets(int userId) const;
	void listUsers() const;
	void removeUser(int userId);

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

	PolymorphicPtr<User> findUserById(int id);
	PolymorphicPtr<User> findUserByName(const MyString& name);
	PolymorphicPtr<Movie> findMovieById(int id);
	Hall* findHallById(int id);

	bool isNameTaken(const MyString& name) const;
	void loginAndRoleValidation(Role expected = Role::Regular) const;
	void cleanupExpiredMovies();
};

