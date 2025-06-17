#include "Commands/header/ListUserTicketsCommand.h"

void ListUserTicketsCommand::execute(System* system) const
{
	int userId;

	std::cin >> userId;

	try {
		system->listUserTickets(userId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
