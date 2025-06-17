#include "Commands/header/CloseHallCommand.h"

void CloseHallCommand::execute(System* system) const
{
	int hallId;

	std::cin >> hallId;

	system->closeHall(hallId);
}
