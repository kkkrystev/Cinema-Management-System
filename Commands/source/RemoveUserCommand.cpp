#include "Commands/header/RemoveUserCommand.h"

void RemoveUserCommand::execute(System* system) const
{
	int userId;

	std::cin >> userId;

	system->removeUser(userId);
}
