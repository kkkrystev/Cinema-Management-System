#include "Commands/header/OpenHallCommand.h"

void OpenHallCommand::execute(System* system) const
{
	int rows, cols;

	std::cin >> rows >> cols;

	try {
		system->openHall(rows, cols);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
