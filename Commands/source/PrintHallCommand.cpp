#include "Commands/header/PrintHallCommand.h"

void PrintHallCommand::execute(System* system) const
{
	int hallId;

	std::cin >> hallId;

	try {
		system->printHall(hallId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
