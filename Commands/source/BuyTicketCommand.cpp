#include "Commands/header/BuyTicketCommand.h"

void BuyTicketCommand::execute(System* system) const
{
	int movieId, row, col;

	std::cin >> movieId >> row >> col;

	try {
		system->buyTicket(movieId, row, col);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
