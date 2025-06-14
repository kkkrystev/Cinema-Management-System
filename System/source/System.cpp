#include "System/header/System.h"
#include "Helpers/header/Utilities.h"

System& System::getInstance()
{
	static System instance;
	return instance;
}

// Non-restrict
void System::registerUser(const MyString& name, const MyString& password)
{
	if (loggedIn)
		throw std::logic_error("To register you must first log out.");
	
	if (!isNameTaken(name))
		throw std::logic_error("Name already taken.");
	if (!validateName(name))
		throw std::invalid_argument("To register you must enter a valid name.");
	if (!validatePassword(password))
		throw std::invalid_argument("To register you must enter a valid password.");

	users.push_back(new RegularUser(name, password));
	std::cout << "Successfully registered as " << name << " with password " << password << " !";
}
void System::login(const MyString& name, const MyString& password)
{
	if (loggedIn)
		throw std::logic_error("User already logged in.");

	PolymorphicPtr<User> user = findUserByName(name);

	if (!user)
		throw std::invalid_argument("Invalid login name.");
	if (user->getPassword() != password)
		throw std::invalid_argument("Invalid login password.");

	cleanupExpiredMovies();

	loggedIn = user;
	std::cout << "Login successful!" << '\n';
	if (loggedIn->getRole() != Role::Admin)
		std::cout << "Welcome, " << name << " !";
}
void System::logout()
{
	loggedIn = nullptr;
}
void System::buyTicket(int movieId, int row, int col)
{
	loginAndRoleValidation();

	PolymorphicPtr<Movie> movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does NOT exist.");

	int hallId = movie->getHallId();
	Hall* hall = findHallById(hallId);
	if (!hall)
		throw std::invalid_argument("A hall with such ID does NOT exist.");

	// potentially make this a while cycle
	if (hall->isSeatTaken(row, col))
		throw std::invalid_argument("Unfortunately, this seat is already taken.");

	hall->reserveSeat(row, col);

	Ticket ticket(movieId, row, col);

	loggedIn->buyTicket(ticket, movie->getTicketPrice());
	std::cout << "Thank you for purchasing a ticket for " << movie->getTitle() << '.';
}
void System::rateMovie(int movieId, int rating)
{
	loginAndRoleValidation();

	if (rating < Constants::MIN_MOVIE_RATING || rating > Constants::MAX_MOVIE_RATING)
		throw std::invalid_argument("Rating is restricted to a scale from 0 to 5");

	PolymorphicPtr<Movie> movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does not exist");

	movie->addToRating(rating);
	std::cout << "Rating submitted! Movie score updated";
}

void System::addBalance(double sum)
{
	loginAndRoleValidation();

	if (sum <= 0.0)
		throw std::invalid_argument("Invalid sum.");

	loggedIn->addBalance(sum);
	std::cout << "You have successfully added " << sum << " to your balance.";
}

// Admin-specific
void System::addMovie(Genre genre)
{
	loginAndRoleValidation(Role::Admin);
}
void System::removeMovie(int movieId)
{
	loginAndRoleValidation(Role::Admin);

	PolymorphicPtr<Movie> movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does NOT exist");

	// if removed before begin -> return balance and don't add to catalogues
	// if removed during screening -> exception or (don't return balance and add to catalogues)
	// if removed after screening -> don't return balance add to catalogues
}
void System::openHaul(int rows, int cols)
{
	loginAndRoleValidation(Role::Admin);

	Hall hall(rows, cols);
	halls.push_back(hall);
	std::cout << "A new hall with ID " << hall.getId() << " successfully opened";
}
void System::removeUser(int userId)
{
	loginAndRoleValidation(Role::Admin);

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i] && users[i]->getId() == userId)
		{
			std::cout << "User " << users[i]->getName() << " with ID " << userId << " deleted successfully\n";
			users.erase(i);
			return;
		}
	}

	throw std::invalid_argument("A user with such ID does NOT exist");
}

PolymorphicPtr<User> System::findUserById(int id)
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->getId() == id)
			return users[i];
	}
	return nullptr;
}
PolymorphicPtr<User> System::findUserByName(const MyString& name)
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->getName() == name)
			return users[i].get();
	}
	return nullptr;
}
PolymorphicPtr<Movie> System::findMovieById(int id)
{
	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getId() == id)
			return movies[i];
	}
	return nullptr;
}

bool System::isNameTaken(const MyString& name) const
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->getName() == name) 
			return true;
	}

	return false;
}
void System::loginAndRoleValidation(Role expected) const
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != expected)
		throw std::logic_error(("You must be a(n) " + roleToString(expected) + " to perform this action.").c_str());
}
void System::cleanupExpiredMovies()
{
	Date today;
	Time now;

	for (size_t i = 0; i < movies.getSize(); ) {
		Movie* movie = movies[i].get();

		if (movie->getScreeningDate() < today || (movie->getScreeningDate() == today && movie->getScreeningHours().end < now)) {
			int expiredMovieId = movie->getId();

			for (size_t j = 0; i < users.getSize(); j++) {
				users[j]->removeTickets(expiredMovieId);
				users[j]->addToCatalogue(expiredMovieId);
			}

			movies.erase(i);
		}
		else ++i;
	}
}
