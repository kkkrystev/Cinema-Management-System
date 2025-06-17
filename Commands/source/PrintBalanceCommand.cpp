#include "Commands/header/PrintBalanceCommand.h"

void PrintBalanceCommand::execute(System* system) const
{
	try {
		system->printBalance();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
