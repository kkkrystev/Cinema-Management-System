#include "Commands/header/UpdateScreeningHallCommand.h"

void UpdateScreeningHallCommand::execute(System* system) const
{
	int screeningId, hallId;

	std::cin >> screeningId >> hallId;

	system->updateScreeningHall(screeningId, hallId);
}
