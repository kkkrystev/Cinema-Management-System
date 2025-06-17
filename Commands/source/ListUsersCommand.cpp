#include "Commands/header/ListUsersCommand.h"

void ListUsersCommand::execute(System* system) const
{
	system->listUsers();
}
