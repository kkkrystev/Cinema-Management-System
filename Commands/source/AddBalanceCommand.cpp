#include "Commands/header/AddBalanceCommand.h"

void AddBalanceCommand::execute(System* system) const
{
	double sum;
	
	std::cin >> sum;

	try {
		system->addBalance(sum);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
