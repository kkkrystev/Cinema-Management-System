#include "Commands/header/CloseHallCommand.h"

void CloseHallCommand::execute(System* system) const
{
	int hallId;

	std::cin >> hallId;

	try {
		system->closeHall(hallId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
