#include "Commands/header/BuyTicketCommand.h"

void BuyTicketCommand::execute(System* system) const
{
	int screeningId;
	size_t row, col;

	std::cin >> screeningId >> row >> col;

	system->buyTicket(screeningId, row, col);
}
