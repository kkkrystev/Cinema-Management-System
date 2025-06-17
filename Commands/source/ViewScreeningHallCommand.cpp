#include "Commands/header/ViewScreeningHallCommand.h"

void ViewScreeningHallCommand::execute(System* system) const
{
	int screeningId;

	std::cin >> screeningId;

	system->printScreeningHall(screeningId);
}
