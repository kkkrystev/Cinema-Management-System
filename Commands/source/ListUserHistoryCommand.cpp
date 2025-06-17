#include "Commands/header/ListUserHistoryCommand.h"

void ListUserHistoryCommand::execute(System* system) const
{
	int userId;

	std::cin >> userId;

	system->listUserHistory(userId);
}
