#include "System/header/System.h"
#include "Helpers/header/Utilities.h"

System& System::getInstance()
{
	static System instance;
	return instance;
}
System::System()
{
	loadUsers();
	loadMovies();
	loadHalls();
	std::cout << '\n';
}
System::~System()
{
	saveUsers();
	saveMovies();
	saveHalls();
}

// Non-restrict
void System::registerUser(const MyString& name, const MyString& password)
{
	if (loggedIn)
		throw std::logic_error("To register you must first log out.");
	
	if (isNameTaken(name))
		throw std::logic_error("Name already taken.");

	User* newUser = new RegularUser(name, password);
	users.push_back(PolymorphicPtr<User>(newUser));
	std::cout << "Successfully registered as " << name << " with password " << password << ".\n";
}
void System::login(const MyString& name, const MyString& password)
{
	if (loggedIn)
		throw std::logic_error("User already logged in.");

	User* user = findUserByName(name);

	if (!user)
		throw std::invalid_argument("Invalid login name.");

	if (user->getPassword() != password)
		throw std::invalid_argument("Invalid login password.");

	cleanupExpiredMovies();

	loggedIn = user;
	std::cout << "Login successful! Welcome, " << name << "!\n";
}
void System::logout()
{
	loggedIn = nullptr;
}
void System::addBalance(double sum)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (sum <= 0.0)
		throw std::invalid_argument("Invalid sum.");

	loggedIn->addBalance(sum);
	std::cout << "You have successfully added " << sum << " to your balance.\n";
}
void System::printBalance() const
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	std::cout << "Balnce: " << loggedIn->getBalance() << " BGN.\n";
}
void System::printHall(int hallId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	Hall* hall = findHallById(hallId);

	if (!hall)
		throw std::invalid_argument("A hall with such ID does NOT exist.");

	hall->printLayout();
}
void System::buyTicket(int movieId, size_t row, size_t col)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	Movie* movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does NOT exist.");

	int hallId = movie->getHallId();
	Hall* hall = findHallById(hallId);
	if (!hall)
		throw std::invalid_argument("A hall with such ID does NOT exist.");

	if (row == 0 || col == 0)
		throw std::invalid_argument("Invalid seat coordinates.");

	if (hall->isSeatTaken(row-1, col-1))
		throw std::invalid_argument("Unfortunately, this seat is already taken.");

	hall->reserveSeat(row-1, col-1);

	Ticket ticket(movieId, row-1, col-1);

	loggedIn->buyTicket(ticket, movie->getTicketPrice());
	std::cout << "Thank you for purchasing a ticket for " << movie->getTitle() << ".\n";
}
void System::rateMovie(int movieId, unsigned rating)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (rating < Constants::MIN_MOVIE_RATING || rating > Constants::MAX_MOVIE_RATING)
		throw std::invalid_argument("Rating is restricted to a scale from 0 to 5");

	Movie* movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does not exist");

	if (!isMovieInCatalogue(movieId))
		throw std::logic_error("You can only rate movies you have been to.");

	movie->addToRating(rating);
	std::cout << "Rating submitted. Movie score updated.\n";
}
void System::listMovies() const
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (movies.getSize() == 0) {
		std::cout << "There are no upcoming screenings scheduled for the moment.\n";
		return;
	}

	std::cout << "Upcoming screenings:\n";
	for (size_t i = 0; i < movies.getSize(); i++) {
		Date date = movies[i]->getScreeningDate();
		Time start = movies[i]->getScreeningHours().start;
		Time end = movies[i]->getScreeningHours().end;
		if (!isScreeningInPast(date, start, end)) {
			movies[i]->printAsUpcoming();
			std::cout << '\n';
		}
	}
}
void System::listHistory()
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	size_t movieCount = loggedIn->getCatalogue().getSize();

	if (movieCount == 0) {
		std::cout << "No movies in your catalogue to display.\n";
		return;
	}

	for (size_t i = 0; i < movieCount; i++) {
		std::cout << "Movie #" << i + 1 << ": ";

		int movieId = loggedIn->getCatalogue()[i];
		Movie* movie = findMovieById(movieId);

		movie->printAsPast();
		std::cout << "\n";
	}

}
void System::listTickets()
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	size_t ticketCount = loggedIn->getTickets().getSize();

	if (ticketCount == 0) {
		std::cout << "No tickets to display.\n";
		return;
	}

	for (size_t i = 0; i < ticketCount; i++) {
		std::cout << "Ticket #" << i + 1 << ": ";

		int movieId = loggedIn->getTickets()[i].getMovieId();
		Movie* movie = findMovieById(movieId);

		std::cout << movie->getTitle() 
			<< " | " << movie->getScreeningDate() 
			<< ", " << movie->getScreeningHours()
			<< " | Hall: " << movie->getHallId() 
			<< " | Seat: " << loggedIn->getTickets()[i].getRow()+1 << loggedIn->getTickets()[i].getCol()+1 
			<< " | " << movie->getTicketPrice() << " BGN"
			<< "\n";
	}
}

// Admin-specific
void System::addActionMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, unsigned actionIntensity)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	validateMovieInputData(title, releaseYear, duration, hallId, screeningDate, start, end);

	if (actionIntensity > Constants::MAX_ACTION_INTENSITY || actionIntensity < Constants::MIN_ACTION_INTENSITY)
		throw std::invalid_argument("Action intensity must be in the valid range.");

	Movie* moviePtr = new ActionMovie(title, releaseYear, duration, hallId, screeningDate, TimeInterval(start, end), actionIntensity);

	PolymorphicPtr<Movie> toAdd(moviePtr);

	movies.push_back(toAdd);
	std::cout << "Action movie " << title << " successfully added.\n";
}
void System::addDocumentaryMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, Theme theme, bool isBasedOnTrueEvents)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	validateMovieInputData(title, releaseYear, duration, hallId, screeningDate, start, end);

	Movie* moviePtr = new DocumentaryMovie(title, releaseYear, duration, hallId, screeningDate, TimeInterval(start, end), theme, isBasedOnTrueEvents);

	PolymorphicPtr<Movie> toAdd(moviePtr);

	movies.push_back(toAdd);
	std::cout << "Documentary movie " << title << " successfully added.\n";
}
void System::addDramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end, bool hasComedyElements)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	validateMovieInputData(title, releaseYear, duration, hallId, screeningDate, start, end);

	Movie* moviePtr = new DramaMovie(title, releaseYear, duration, hallId, screeningDate, TimeInterval(start, end), hasComedyElements);

	PolymorphicPtr<Movie> toAdd(moviePtr);

	movies.push_back(toAdd);
	std::cout << "Drama movie " << title << " successfully added.\n";
}
void System::removeMovie(int movieId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Movie* movie = findMovieById(movieId);
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

	std::cout << "Movie " << movie->getTitle() << " removed successfully.\n";
	removeMovieFromList(movieId);	
}
void System::removeUser(int userId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (users[i] && users[i]->getId() == userId)
		{
			if (users[i]->getRole() == Role::Admin)
				throw std::logic_error("You are not allowed to remove the Admin.");

			std::cout << "User " << users[i]->getName() << " with ID " << userId << " deleted successfully\n";
			users.erase(i);
			return;
		}
	}

	throw std::invalid_argument("A user with such ID does NOT exist.\n");
}
void System::openHall(size_t rows, size_t cols)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Hall hall(rows, cols);
	std::cout << "A new hall with ID " << hall.getId() << " successfully opened.\n";
	halls.push_back(std::move(hall));
}
void System::closeHall(int hallId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Hall* hall = findHallById(hallId);

	if (!hall)
		throw std::invalid_argument("A hall with such ID does NOT exist.");

	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getHallId() == hallId) {
			Date screeningDate = movies[i]->getScreeningDate();
			Time screeningStart = movies[i]->getScreeningHours().start;
			Time screeningEnd = movies[i]->getScreeningHours().end;

			if (isScreeningOngoing(screeningDate, screeningStart, screeningEnd))
				throw std::logic_error("You cannot close a hall during a screening.");
		}
	}

	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getHallId() == hallId) {
			Date screeningDate = movies[i]->getScreeningDate();
			Time screeningStart = movies[i]->getScreeningHours().start;
			Time screeningEnd = movies[i]->getScreeningHours().end;

			if (isScreeningInPast(screeningDate, screeningStart, screeningEnd)) {
				movies[i]->setHallId(-1);
			}
			else {
				returnUsersTickets(movies[i].get());
			}
		}
	}

	for (size_t i = 0; i < halls.getSize(); i++) {
		if (halls[i].getId() == hallId) {
			halls.erase(i);
			break;
		}
	}
	std::cout << "Successfully closed hall " << hallId << ".\n";
}
void System::updateMovieTitle(int movieId, const MyString& newTitle)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Movie* movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does not exist.");

	if (movie->getTitle() == newTitle)
		throw std::logic_error("The new movie title must be different than the old one.");

	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getTitle() == newTitle)
			throw std::logic_error("A movie with such title already exists.");
	}

	std::cout << "Successfully changed " << movie->getTitle() << " to " << newTitle << ".\n";
	movie->setTitle(newTitle);
}
void System::updateMovieHall(int movieId, int newHallId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Movie* movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does not exist.");

	if (movie->getHallId() == newHallId)
		throw std::logic_error("The new hall must be different than the current one.");

	Hall* hall = findHallById(newHallId);
	if (!hall)
		throw std::invalid_argument("A hall with such ID does not exist.");

	Date date = movie->getScreeningDate();
	Time start = movie->getScreeningHours().start;
	Time end = movie->getScreeningHours().end;

	if (doScreeningsOverlap(newHallId, date, start, end))
		throw std::logic_error("Overlapping screening found in the new hall.");

	std::cout << "Successfully moved " << movie->getTitle() << " to hall " << newHallId << ".\n";
	movie->setHallId(newHallId);
}
void System::listUserHistory(int userId) 
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	User* user = findUserById(userId);
	if (!user)
		throw std::invalid_argument("A user with such ID does NOT exist.");

	size_t watchCount = user->getCatalogue().getSize();

	if (watchCount == 0) {
		std::cout << user->getName() << "'s watch history is empty.\n";
		return;
	}

	std::cout << user->getName() << "'s watch history:\n";
	for (size_t i = 0; i < watchCount; i++) {
		int movieId = user->getCatalogue()[i];
		Movie* movie = findMovieById(movieId);

		std::cout << "[] "
			<< movie->getId()
			<< " | " << movie->getTitle()
			<< " | " << movie->getScreeningDate()
			<< ", " << movie->getScreeningHours()
			<< "\n";
			
	}
}
void System::listUserTickets(int userId) 
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	User* user = findUserById(userId);
	if (!user)
		throw std::invalid_argument("A user with such ID does NOT exist.");

	size_t ticketCount = user->getTickets().getSize();

	if (ticketCount == 0) {
		std::cout << user->getName() << " has no tickets to display.\n";
		return;
	}

	std::cout << user->getName() << "'list of tickets:\n";
	for (size_t i = 0; i < ticketCount; i++) {
		int movieId = user->getTickets()[i].getMovieId();
		Movie* movie = findMovieById(movieId);

		std::cout << "[] "
			<< movie->getId()
			<< " | " << movie->getTitle()
			<< " | " << movie->getScreeningDate()
			<< ", " << movie->getScreeningHours()
			<< " | Hall: " << movie->getHallId()
			<< " | Seat: " << loggedIn->getTickets()[i].getRow()+1 << '-' << loggedIn->getTickets()[i].getCol() + 1
			<< " | " << movie->getTicketPrice() << " BGN"
			<< "\n";
	}
}
void System::listUsers() const
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	if (users.getSize() <= 1) {
		std::cout << "No users to display.\n";
		return;
	}

	for (size_t i = 0; i < users.getSize(); i++) {
		std::cout << "[] User " << users[i]->getId()
			<< " | " << users[i]->getName()
			<< " | Balance: " << users[i]->getBalance()
			<< '\n';
	}
}

// Save & load
void System::saveUsers() const
{
	std::ofstream ofs("users.dat", std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Can't open users.dat when trying to save\n";
		return;
	}

	size_t count = users.getSize();
	ofs.write((const char*)&count, sizeof(count));

	for (size_t i = 0; i < count; i++) {
		Role r = users[i]->getRole();
		ofs.write((const char*)&r, sizeof(r));
		users[i]->saveToBinaryFile(ofs);
	}

	std::cout << "Users saved successfully!\n";
}
void System::saveMovies() const
{
	std::ofstream ofs("movies.dat", std::ios::binary);
	if (!ofs.is_open()) 
		std::cout << "Can't open movies.dat when trying to save\n";

	size_t movieCount = movies.getSize();
	ofs.write((const char*)&movieCount, sizeof(movieCount));

	for (size_t i = 0; i < movieCount; i++) {
		Genre genre = movies[i]->getGenre();
		ofs.write((const char*)&genre, sizeof(genre));
		movies[i]->saveToBinaryFile(ofs);
	}

	ofs.close();
	std::cout << "Movies saved successfully!\n";
}
void System::saveHalls() const
{
	std::ofstream ofs("halls.dat", std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Can't open halls.dat when trying to save\n";
		return;
	}

	size_t count = halls.getSize();
	ofs.write((const char*)&count, sizeof(count));

	for (size_t i = 0; i < count; i++) {
		halls[i].saveToBinaryFile(ofs);
	}

	ofs.close();
	std::cout << "Halls saved successfully!\n";
}
void System::loadUsers()
{
	std::ifstream ifs("users.dat", std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Can't open users.dat when trying to load...";

		std::ofstream ofs("users.dat", std::ios::binary);
		if (!ofs.is_open()) {
			std::cout << "Failed to create users.dat\n";
			return;
		}

		users.push_back(PolymorphicPtr<User>(new Admin()));
		std::cout << "A new users.dat and an Admin user have been created successfully!\n";
		return;
	}

	if (getFileSize(ifs) == 0) {
		users.clear();
		users.push_back(PolymorphicPtr<User>(new Admin()));
		std::cout << "A new Admin user has been created successfully!\n";
		return;
	}

	users.clear();
	size_t count;
	ifs.read((char*)&count, sizeof(count));

	for (size_t i = 0; i < count; i++) {
		Role role;
		ifs.read((char*)&role, sizeof(role));

		User* user;

		switch (role) {
		case Role::Admin: { 
			user = new Admin();
			user->loadFromBinaryFile(ifs);
			users.push_back(PolymorphicPtr<User>(user));
			break; 
		}
		case Role::Regular: { 
			user = new RegularUser();
			user->loadFromBinaryFile(ifs);
			users.push_back(PolymorphicPtr<User>(user));
			break; 
		}
		}
	}

	User::setNextId(users.back()->getId() + 1);

	std::cout << "Users loaded successfully!\n";
}
void System::loadMovies()
{
	std::ifstream ifs("movies.dat", std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Can't open movies.dat when trying to load...";

		std::ofstream ofs("movies.dat", std::ios::binary);
		if (!ofs.is_open()) {
			std::cout << "Failed to create movies.dat\n";
			return;
		}

		std::cout << "A new movies.dat file has been created successfully!\n";
		movies.clear();
		return;
	}

	if (getFileSize(ifs) == 0) {
		std::cout << "No movies to load. Continuing...\n";
		return;
	}

	size_t movieCount = 0;
	ifs.read((char*)&movieCount, sizeof(movieCount));

	for (size_t i = 0; i < movieCount; i++) {
		Genre genre;
		ifs.read((char*)&genre, sizeof(genre));

		Movie* movie;

		switch (genre) {
		case Genre::Action: {
			movie = new ActionMovie();
			movie->loadFromBinaryFile(ifs);
			movies.push_back(PolymorphicPtr<Movie>(movie));
			break;
		}
		case Genre::Drama: { 
			movie = new DramaMovie();
			movie->loadFromBinaryFile(ifs);
			movies.push_back(PolymorphicPtr<Movie>(movie));
			break; }
		case Genre::Documentary: {
			movie = new DocumentaryMovie();
			movie->loadFromBinaryFile(ifs);
			movies.push_back(PolymorphicPtr<Movie>(movie));
			break;
		}
		}
	}

	if (!movies.empty())
		Movie::setNextId(movies.back()->getId() + 1);

	ifs.close();
	std::cout << "Movies loaded successfully!\n";
}
void System::loadHalls()
{
	std::ifstream ifs("halls.dat", std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Can't open halls.dat when trying to load...";

		std::ofstream ofs("halls.dat", std::ios::binary);
		if (!ofs.is_open()) {
			std::cout << "Failed to create halls.dat\n";
			return;
		}

		std::cout << "A new halls.dat has been created successfully!\n";
		halls.clear();
		return;
	}

	if (getFileSize(ifs) == 0) {
		std::cout << "No halls to load. Continuing...\n";
		return;
	}

	size_t count;
	ifs.read((char*)&count, sizeof(count));

	for (size_t i = 0; i < count; i++) {
		Hall hall;
		hall.loadFromBinaryFile(ifs);
		halls.push_back(hall);
	}

	if(!halls.empty())
		Hall::setNextId(halls.back().getId() + 1);

	ifs.close();
	std::cout << "Halls loaded successfully!\n";
}

// Finders
User* System::findUserById(int id)
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->getId() == id)
			return users[i].get();
	}
	return nullptr;
}
User* System::findUserByName(const MyString& name)
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->getName() == name)
			return users[i].get();
	}
	return nullptr;
}
Movie* System::findMovieById(int id)
{
	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getId() == id)
			return movies[i].get();
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
bool System::isMovieInCatalogue(int movieId) const
{
	for (size_t i = 0; i < loggedIn->getCatalogue().getSize(); i++) {
		if (loggedIn->getCatalogue()[i] == movieId)
			return true;
	}
	return false;
}

// Isolated and repetitive logic
void System::validateMovieInputData(const MyString& title, unsigned releaseYear, unsigned duration, int hallId, const Date& screeningDate, const Time& start, const Time& end)
{
	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getTitle() == title)
			throw std::logic_error("A movie with such title already exists.");
	}

	Date now;
	if ((int)releaseYear > now.getYear())
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
void System::returnUsersTickets(Movie* movie)
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