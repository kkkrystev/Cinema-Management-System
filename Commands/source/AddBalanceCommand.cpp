#include "Commands/header/AddBalanceCommand.h"

void AddBalanceCommand::execute(System* system) const
{
	double sum;

	std::cin >> sum;

	system->addBalance(sum);

}
