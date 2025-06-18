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
	loadScreenings();
	loadHalls();
	std::cout << '\n';
}
System::~System()
{
	std::cout << '\n';
	saveUsers();
	saveMovies();
	saveScreenings();
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

	cleanupExpiredScreenings();

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
void System::printScreeningHall(int screeningId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	Screening* screening = findScreeningById(screeningId);
	if (!screening)
		throw std::invalid_argument("A screening with such ID does NOT exist.");

	screening->printSeats();
}
void System::buyTicket(int screeningId, size_t row, size_t col)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	Screening* screening = findScreeningById(screeningId);
	if (!screening)
		throw std::invalid_argument("A screening with such ID does NOT exist.");

	Movie* movie = findMovieById(screening->getMovieId());

	if (row == 0 || col == 0)
		throw std::invalid_argument("Invalid seat coordinates.");

	screening->reserveSeat(row-1, col-1);

	Ticket ticket(screeningId, row-1, col-1);

	loggedIn->buyTicket(ticket, movie->getTicketPrice());
	std::cout << "Thank you for purchasing a ticket for " << movie->getTitle() << ".\n";
}
void System::rateMovie(int movieId, unsigned rating)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (rating < Constants::MIN_MOVIE_RATING || rating > Constants::MAX_MOVIE_RATING)
		throw std::invalid_argument("Rating is restricted to a scale from 0 to 5.");

	Movie* movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does not exist.");

	if (!isMovieInCatalogue(movieId))
		throw std::logic_error("You can only rate movies you have been to.");

	movie->addToRating(rating);
	std::cout << "Rating submitted. Movie score updated.\n";
}
void System::listMovies()
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (movies.getSize() == 0) {
		std::cout << "There are no upcoming screenings scheduled for the moment.\n";
		return;
	}

	for (size_t i = 0; i < movies.getSize(); ++i) {
		std::cout << "[] ";
		movies[i]->print();
		std::cout << '\n';
	}
}
void System::listScreenings()
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (screenings.getSize() == 0) {
		std::cout << "There are no movies at the moment.\n";
		return;
	}

	std::cout << "Upcoming screenings:\n";
	for (size_t i = 0; i < screenings.getSize(); i++) {
		Date date = screenings[i].getDate();
		Time start = screenings[i].getHours().start;
		Time end = screenings[i].getHours().end;

		if (!isScreeningInPast(date, start, end)) {
			Movie* movie = findMovieById(screenings[i].getMovieId());

			std::cout << "[] " << movie->getTitle() << " | ";
			screenings[i].print();
			std::cout << " | Ticket price: " << movie->getTicketPrice();
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

		movie->print();
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

		int screeningId = loggedIn->getTickets()[i].getScreeningId();
		Screening* screening = findScreeningById(screeningId);
		Movie* movie = findMovieById(screening->getMovieId());

		std::cout << movie->getTitle() 
			<< " | " << screening->getDate()
			<< ", " << screening->getHours()
			<< " | Hall: " << screening->getHallId() 
			<< " | Seat: " << loggedIn->getTickets()[i].getRow() + 1 << loggedIn->getTickets()[i].getCol() + 1 
			<< " | " << movie->getTicketPrice() << " BGN"
			<< "\n";
	}
}

// Admin-specific
void System::addActionMovie(const MyString& title, unsigned releaseYear, unsigned duration, unsigned actionIntensity)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	if (isMovieTitleTaken(title))
		throw std::logic_error("A movie with such title already exists.");

	if (!isReleaseYearValid(releaseYear))
		throw std::invalid_argument("You cannot a movie with a release year in the future.");

	if (actionIntensity > Constants::MAX_ACTION_INTENSITY || actionIntensity < Constants::MIN_ACTION_INTENSITY)
		throw std::invalid_argument("Action intensity must be in the valid range.");

	Movie* movie = new ActionMovie(title, releaseYear, duration, actionIntensity);

	PolymorphicPtr<Movie> toAdd(movie);

	movies.push_back(toAdd);
	std::cout << "Action movie " << title << " successfully added.\n";
}
void System::addDocumentaryMovie(const MyString& title, unsigned releaseYear, unsigned duration, Theme theme, bool isBasedOnTrueEvents)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	if (isMovieTitleTaken(title))
		throw std::logic_error("A movie with such title already exists.");

	if (!isReleaseYearValid(releaseYear))
		throw std::invalid_argument("You cannot a movie with a release year in the future.");

	if (theme == Theme::Invalid)
		throw std::invalid_argument("You cannot create a movie with an invalid theme type.");

	Movie* movie = new DocumentaryMovie(title, releaseYear, duration, theme, isBasedOnTrueEvents);

	PolymorphicPtr<Movie> toAdd(movie);

	movies.push_back(toAdd);
	std::cout << "Documentary movie " << title << " successfully added.\n";
}
void System::addDramaMovie(const MyString& title, unsigned releaseYear, unsigned duration, bool hasComedyElements)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	if (isMovieTitleTaken(title))
		throw std::logic_error("A movie with such title already exists.");

	if (!isReleaseYearValid(releaseYear))
		throw std::invalid_argument("You cannot a movie with a release year in the future.");

	Movie* movie = new DramaMovie(title, releaseYear, duration,  hasComedyElements);

	PolymorphicPtr<Movie> toAdd(movie);

	movies.push_back(toAdd);
	std::cout << "Drama movie " << title << " successfully added.\n";
}
void System::addScreening(int movieId, int hallId, const Date& date, const Time& start, const Time& end)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Movie* movie = findMovieById(movieId);
	if (!movie)
		throw std::invalid_argument("A movie with such ID does NOT exist.");

	Hall* hall = findHallById(hallId);
	if (!hall)
		throw std::invalid_argument("A hall with such ID does NOT exist.");

	if (isScreeningInPast(date, start, end) || isScreeningOngoing(date, start, end))
		throw std::invalid_argument("You cannot schedule a screening for a past or ongoing moment in time.");

	if (start >= end) 
		throw std::invalid_argument("Invalid screening hours provided.");

	if (!areScreeningHoursValid(movie->getDuration(), start, end))
		throw std::invalid_argument("Provided duration does not match the provided time range.");

	if (doOverlappingScreeningsExist(hallId, date, start, end))
		throw std::logic_error("Overlapping screening found in the same hall.");

	Screening screening(movieId, hallId, hall->getRows(), hall->getCols(), date, TimeInterval(start, end));
	
	std::cout << "A new screening of " << movie->getTitle() << " successfully scheduled.\n";
	screenings.push_back(std::move(screening));
}
void System::removeScreening(int screeningId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Screening* screening = findScreeningById(screeningId);
	if (!screening)
		throw std::invalid_argument("A screening with such ID does NOT exist.");

	Date date = screening->getDate();
	Time start = screening->getHours().start;
	Time end = screening->getHours().end;

	if (isScreeningOngoing(date, start, end)) {
		throw std::runtime_error("Cannot remove a screening while it is still ongoing.");
	}
	else if (isScreeningInPast(date, start, end)) {
		addToUserCatalogues(screening);
		std::cout << "Screening is in the past. Adding movie to user cataloges...\n";
	}
	else {
		returnUsersTickets(screening);
		std::cout << "Screening was sheduled for the future. Restoring the amout paid by users...\n";
	}

	Movie* movie = findMovieById(screening->getMovieId());

	std::cout << "A screening of " << movie->getTitle() << " with ID " << screening->getId() << " removed successfully.\n";
	removeScreeningFromList(screening->getId());
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

	if (doesMovieHaveOngoingScreenings(movieId)) 
		throw std::logic_error("You cannot remove a movie while it still has ongoing screenings.");
	
	bool hadPastScreenings = false;
	bool hadFutureScreenings = false;

	for (size_t i = 0; i < screenings.getSize(); ++i) {
		if (screenings[i].getMovieId() == movieId) {
			Date date = screenings[i].getDate();
			Time start = screenings[i].getHours().start;
			Time end = screenings[i].getHours().end;

			if (isScreeningInPast(date, start, end)) {
				addToUserCatalogues(&screenings[i]);
				hadPastScreenings = true;
			}
			else {
				returnUsersTickets(&screenings[i]);
				hadFutureScreenings = true;
			}

			removeScreeningFromList(screenings[i].getId());
			i--;
		}
	}
	
	if (hadPastScreenings && !hadFutureScreenings)
		std::cout << "All screenings were in the past. Movie added to user catalogues.\n";
	else if (!hadPastScreenings && hadFutureScreenings)
		std::cout << "All screenings were in the future. User payments were refunded.\n";
	else if (hadPastScreenings && hadFutureScreenings)
		std::cout << "Movie had both past and future screenings. Both user catalogue addition and payment refund were applied.\n";
	else
		std::cout << "Movie had no associated screenings.\n";

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

	if (doesHallHaveOngoingScreenings(hallId))
		throw std::logic_error("You cannot close a hall during a screening.");

	bool hadPastScreenings = false;
	bool hadFutureScreenings = false;

	for (size_t i = 0; i < screenings.getSize(); ++i) {
		if (screenings[i].getHallId() == hallId) {
			Date date = screenings[i].getDate();
			Time start = screenings[i].getHours().start;
			Time end = screenings[i].getHours().end;

			if (isScreeningInPast(date, start, end)) {
				addToUserCatalogues(&screenings[i]);
				hadPastScreenings = true;
			}
			else {
				returnUsersTickets(&screenings[i]);
				hadFutureScreenings = true;
			}

			removeScreeningFromList(screenings[i].getId());
			i--;
		}
	}

	if (hadPastScreenings && !hadFutureScreenings)
		std::cout << "All screenings were in the past. Movies added to user catalogues.\n";
	else if (!hadPastScreenings && hadFutureScreenings)
		std::cout << "All screenings were in the future. User payments were refunded.\n";
	else if (hadPastScreenings && hadFutureScreenings)
		std::cout << "Hall had both past and future screenings. Both catalogue additions and refunds applied.\n";
	else
		std::cout << "Hall had no associated screenings.\n";

	std::cout << "Successfully closed hall " << hallId << ".\n";
	removeHallFromList(hallId);
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

	if (isMovieTitleTaken(newTitle))
		throw std::logic_error("A movie with such title already exists.");

	std::cout << "Successfully changed " << movie->getTitle() << " to " << newTitle << ".\n";
	movie->setTitle(newTitle);
}
void System::updateScreeningHall(int screeningId, int newHallId)
{
	if (!loggedIn)
		throw std::logic_error("You must be logged in to perform this action.");

	if (loggedIn->getRole() != Role::Admin)
		throw std::logic_error("You must be an Admin to perform this action.");

	Screening* screening = findScreeningById(screeningId);
	if (!screening)
		throw std::invalid_argument("A screening with such ID does NOT exist.");

	if(screening->getHallId() == newHallId)
		throw std::logic_error("The new hall must be different than the current one.");

	Hall* hall = findHallById(newHallId);
	if (!hall)
		throw std::invalid_argument("A hall with such ID does not exist.");

	Date date = screening->getDate();
	Time start = screening->getHours().start;
	Time end = screening->getHours().end;

	if (doOverlappingScreeningsExist(newHallId, date, start, end))
		throw std::logic_error("Overlapping screening found in the new hall.");

	std::cout << "Successfully screening with ID " << screeningId << " to hall " << newHallId << ".\n";
	screening->setHallId(newHallId);
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

		std::cout << "[" << i + 1 << "] ";
		movie->print();
		std::cout << '\n';
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

	std::cout << user->getName() << "'s list of tickets:\n";
	for (size_t i = 0; i < ticketCount; i++) {
		int screeningId = user->getTickets()[i].getScreeningId();
		Screening* screening = findScreeningById(screeningId);
		Movie* movie = findMovieById(screening->getMovieId());

		std::cout << "[" << i + 1 << "] "
			<< movie->getTitle()
			<< " | " << screening->getDate()
			<< ", " << screening->getHours()
			<< " | Hall: " << screening->getHallId()
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
void System::saveScreenings() const
{
	std::ofstream ofs("screenings.dat", std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "Can't open screenings.dat when trying to save\n";
		return;
	}

	size_t count = screenings.getSize();
	ofs.write((const char*)&count, sizeof(count));

	for (size_t i = 0; i < count; ++i) {
		screenings[i].saveToBinaryFile(ofs);
	}

	ofs.close();
	std::cout << "Screenings saved successfully!\n";
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
void System::loadScreenings()
{
	std::ifstream ifs("screenings.dat", std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "Can't open screenings.dat when trying to load...";

		std::ofstream ofs("screenings.dat", std::ios::binary);
		if (!ofs.is_open()) {
			std::cout << "Failed to create screenings.dat\n";
			return;
		}

		std::cout << "A new screenings.dat has been created successfully!\n";
		screenings.clear();
		return;
	}

	if (getFileSize(ifs) == 0) {
		std::cout << "No screenings to load. Continuing...\n";
		return;
	}

	size_t count;
	ifs.read((char*)&count, sizeof(count));

	screenings.clear();
	for (size_t i = 0; i < count; ++i) {
		Screening s;
		s.loadFromBinaryFile(ifs);
		screenings.push_back(s);
	}

	if (!screenings.empty())
		Screening::setNextId(screenings.back().getId() + 1);

	ifs.close();
	std::cout << "Screenings loaded successfully!\n";
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
Screening* System::findScreeningById(int id)
{
	for (size_t i = 0; i < screenings.getSize(); i++) {
		if (screenings[i].getId() == id)
			return &screenings[i];
	}
	return nullptr;
}
Hall* System::findHallById(int id)
{
	for (size_t i = 0; i < halls.getSize(); i++) {
		if (halls[i].getId() == id) 
			return &halls[i];
	}
	return nullptr;
}

// Checks
bool System::isMovieTitleTaken(const MyString& title) const
{
	for (size_t i = 0; i < movies.getSize(); i++) {
		if (movies[i]->getTitle() == title)
			return true;
	}
	return false;
}
bool System::isNameTaken(const MyString& name) const
{
	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->getName() == name) 
			return true;
	}

	return false;
}
bool System::isReleaseYearValid(unsigned releaseYear) const
{
	Date now;
	return (int)releaseYear <= now.getYear();
}
bool System::areScreeningHoursValid(unsigned duration, const Time& start, const Time& end) const
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
bool System::doOverlappingScreeningsExist(int hallId, const Date& screeningDate, const Time& start, const Time& end) const
{
	for (size_t i = 0; i < screenings.getSize(); i++) {
		if (screenings[i].getHallId() == hallId 
			&& screenings[i].getDate() == screeningDate 
			&& doIntervalsOverlap(screenings[i].getHours(), TimeInterval(start, end))) {
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
bool System::doesMovieHaveOngoingScreenings(int movieId) const
{
	for (size_t i = 0; i < screenings.getSize(); ++i) {
		if (screenings[i].getMovieId() == movieId) {
			Date date = screenings[i].getDate();
			Time start = screenings[i].getHours().start;
			Time end = screenings[i].getHours().end;

			if (isScreeningOngoing(date, start, end)) {
				return true;
			}
		}
	}
	return false;
}
bool System::doesHallHaveOngoingScreenings(int hallId) const
{
	for (size_t i = 0; i < screenings.getSize(); ++i) {
		if (screenings[i].getHallId() == hallId) {
			Date date = screenings[i].getDate();
			Time start = screenings[i].getHours().start;
			Time end = screenings[i].getHours().end;

			if (isScreeningOngoing(date, start, end)) {
				return true;
			}
		}
	}
	return false;
}

// Isolated and repetitive logic
void System::cleanupExpiredScreenings()
{
	for (size_t i = 0; i < screenings.getSize(); ) {
		Date date = screenings[i].getDate();
		Time start = screenings[i].getHours().start;
		Time end = screenings[i].getHours().end;

		if (isScreeningInPast(date, start, end)) {
			int expiredScreeningId = screenings[i].getId();
			addToUserCatalogues(&screenings[i]);
			removeScreeningFromList(expiredScreeningId);
		}
		else i++;
	}
}
void System::removeScreeningFromList(int screeningId)
{
	for (size_t i = 0; i < screenings.getSize(); ++i) {
		if (screenings[i].getId() == screeningId) {
			screenings.erase(i);
			return;
		}
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
void System::removeHallFromList(int hallId)
{
	for (size_t i = 0; i < halls.getSize(); i++) {
		if (halls[i].getId() == hallId) {
			halls.erase(i);
			return;
		}
	}
}
void System::returnUsersTickets(Screening* screening)
{
	int screeningId = screening->getId();
	Movie* movie = findMovieById(screening->getMovieId());
	double ticketPrice = movie->getTicketPrice();

	for (size_t i = 0; i < users.getSize(); i++) {
		users[i]->returnTickets(screeningId, ticketPrice);
	}
}
void System::addToUserCatalogues(Screening* screening)
{
	int screeningId = screening->getId();
	Movie* movie = findMovieById(screening->getMovieId());
	int movieId = movie->getId();

	for (size_t i = 0; i < users.getSize(); i++) {
		if (users[i]->hasTicket(screeningId)) {
			users[i]->addToCatalogue(movieId);
		}
	}
}