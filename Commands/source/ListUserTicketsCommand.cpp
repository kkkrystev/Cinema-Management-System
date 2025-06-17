#include "Commands/header/ListUserTicketsCommand.h"

void ListUserTicketsCommand::execute(System* system) const
{
	int userId;

	std::cin >> userId;

	system->listUserTickets(userId);
}
