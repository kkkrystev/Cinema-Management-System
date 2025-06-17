#include "Commands/header/PrintBalanceCommand.h"

void PrintBalanceCommand::execute(System* system) const
{
	system->printBalance();
}
