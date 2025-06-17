#include "Commands/header/OpenHallCommand.h"

void OpenHallCommand::execute(System* system) const
{
	size_t rows, cols;

	std::cin >> rows >> cols;

	system->openHall(rows, cols);
}
