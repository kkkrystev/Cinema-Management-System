#include "Commands/header/ListTicketsCommand.h"

void ListTicketsCommand::execute(System* system) const
{
	system->listTickets();
}
