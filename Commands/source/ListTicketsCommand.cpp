#include "Commands/header/ListTicketsCommand.h"

void ListTicketsCommand::execute(System* system) const
{
	try {
		system->listTickets();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
