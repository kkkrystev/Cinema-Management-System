#include "Commands/header/ListScreeningsCommand.h"

void ListScreeningsCommand::execute(System* system) const
{
	system->listScreenings();
}
