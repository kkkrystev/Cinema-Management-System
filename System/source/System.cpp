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
void System::addBalance(double sum)
{
	loginAndRoleValidation();

	if (sum <= 0.0)
		throw std::invalid_argument("Invalid sum.");

	loggedIn->addBalance(sum);
	std::cout << "You have successfully added " << sum << " to your balance.";
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

// Admin-specific
void System::addActionMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, unsigned actionIntensity)
{
	loginAndRoleValidation(Role::Admin);

	validateMovieInputData(title, releaseYear, duration, hallId, screeningDate, start, end);

	if (actionIntensity > Constants::MAX_ACTION_INTENSITY || actionIntensity < Constants::MIN_ACTION_INTENSITY)
		throw std::invalid_argument("Action intensity must be in the valid range.");

	Movie* moviePtr = new ActionMovie(title, releaseYear, duration, hallId, screeningDate, TimeInterval(start, end), actionIntensity);

	PolymorphicPtr<Movie> toAdd(moviePtr);

	movies.push_back(toAdd);
	std::cout << "Action movie " << title << " successfully added.";
}
void System::addDocumentaryMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, Theme theme, bool isBasedOnTrueEvents)
{
	loginAndRoleValidation(Role::Admin);

	validateMovieInputData(title, releaseYear, duration, hallId, screeningDate, start, end);

	Movie* moviePtr = new DocumentaryMovie(title, releaseYear, duration, hallId, screeningDate, TimeInterval(start, end), theme, isBasedOnTrueEvents);

	PolymorphicPtr<Movie> toAdd(moviePtr);

	movies.push_back(toAdd);
	std::cout << "Documentary movie " << title << " successfully added.";
}
void System::addDramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, bool hasComedyElements)
{
	loginAndRoleValidation(Role::Admin);

	validateMovieInputData(title, releaseYear, duration, hallId, screeningDate, start, end);

	Movie* moviePtr = new DramaMovie(title, releaseYear, duration, hallId, screeningDate, TimeInterval(start, end), hasComedyElements);

	PolymorphicPtr<Movie> toAdd(moviePtr);

	movies.push_back(toAdd);
	std::cout << "Drama movie " << title << " successfully added.";
}
void System::removeMovie(int movieId)
{
	loginAndRoleValidation(Role::Admin);

	PolymorphicPtr<Movie> movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does NOT exist");

	Date screeningDate = movie->getScreeningDate();
	Time start = movie->getScreeningHours().start;
	Time end = movie->getScreeningHours().end;

	if (isScreeningOngoing(screeningDate, start, end)) {
		throw std::runtime_error("Cannot remove a movie during its screening.");
	}
	else if (isScreeningInPast(screeningDate, start, end)) {
		addToUserCatalogues(movie->getId());
		std::cout << "Adding movie to user cataloges...\n";
	}
	else {
		returnUsersTickets(movie);
		std::cout << "Removing user tickets and restoring the amount paid by users...\n";
	}

	removeMovieFromList(movieId);
	std::cout << "Movie " << movie->getTitle() << " removed successfully.";
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

void System::openHaul(int rows, int cols)
{
	loginAndRoleValidation(Role::Admin);

	Hall hall(rows, cols);
	halls.push_back(hall);
	std::cout << "A new hall with ID " << hall.getId() << " successfully opened";
}

// Finders
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
Hall* System::findHallById(int id)
{
	for (size_t i = 0; i < halls.getSize(); i++) {
		if (halls[i].getId() == id) return &halls[i];
	}
	return nullptr;
}

// Checks
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
bool System::isDurationValid(unsigned duration, const Time& start, const Time& end) const
{
	unsigned actualDuration = end.toMinutes() - start.toMinutes();
	return duration == actualDuration;
}
bool System::isScreeningOngoing(const Date& screeningDate, const Time& start, const Time& end) const
{
	Date today;
	Time now;

	return screeningDate == today && (start <= now && now < end);
}
bool System::isScreeningInPast(const Date& screeningDate, const Time& start, const Time& end) const
{
	Date today;
	Time now;

	if (screeningDate < today) return true;
	else if (screeningDate == today && now >= end) return true;

	return false;
}
bool System::doScreeningsOverlap(int hallId, const Date& screeningDate, const Time& start, const Time& end) const
{
	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getHallId() == hallId && movies[i]->getScreeningDate() == screeningDate &&
			doIntervalsOverlap(movies[i]->getScreeningHours(), TimeInterval(start, end))) {
			return true;
		}
	}
	return false;
}

// Isolated and repetitive logic
void System::validateMovieInputData(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end)
{
	Date now;
	if (releaseYear > now.getYear())
		throw std::invalid_argument("You cannot a movie whose release year is in the future.");

	if (!findHallById(hallId))
		throw std::invalid_argument("A hall with such ID does NOT exist.");

	if (doScreeningsOverlap(hallId, screeningDate, start, end))
		throw std::logic_error("Overlapping screening found in the same hall.");

	if (start >= end) throw std::invalid_argument("Invalid screening hours provided."); // another solution is std::swap() 

	if (!isDurationValid(duration, start, end))
		throw std::invalid_argument("Provided duration does not match the provided time range.");

	if (isScreeningInPast(screeningDate, start, end))
		throw std::invalid_argument("You are not allowed to add a movie whose screening is in a past moment in time.");
}
void System::cleanupExpiredMovies()
{
	for (size_t i = 0; i < movies.getSize(); ) {
		Movie* movie = movies[i].get();
		Date screeningDate = movie->getScreeningDate();
		Time screeningStart = movie->getScreeningHours().start;
		Time screeningEnd = movie->getScreeningHours().end;

		if (isScreeningInPast(screeningDate, screeningStart, screeningEnd)) {
			int expiredMovieId = movie->getId();
			addToUserCatalogues(expiredMovieId);
		}
		else ++i;
	}
}
void System::removeMovieFromList(int movieId)
{
	for (size_t i = 0; i < movies.getSize(); ++i) {
		if (movies[i]->getId() == movieId) {
			movies.erase(i);
			return;
		}
	}
}
void System::returnUsersTickets(const PolymorphicPtr<Movie>& movie)
{
	int movieId = movie->getId();
	double ticketPrice = movie->getTicketPrice();

	for (size_t i = 0; i < users.getSize(); i++) {
		users[i]->returnTickets(movieId, ticketPrice);
	}
}
void System::addToUserCatalogues(int movieId)
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->hasTicket(movieId)) {
			users[i]->addToCatalogue(movieId);
		}
	}
}