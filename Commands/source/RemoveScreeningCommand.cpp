#include "Commands/header/RemoveScreeningCommand.h"

void RemoveScreeningCommand::execute(System* system) const
{
	int screeningId;

	std::cin >> screeningId;

	system->removeScreening(screeningId);
}
