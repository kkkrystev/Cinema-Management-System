#include "Commands/header/LogoutCommand.h"

void LogoutCommand::execute(System* system) const
{
	system->logout();
}
