#include "Commands/header/ListHistoryCommand.h"

void ListHistoryCommand::execute(System* system) const
{
	system->listHistory();
}
