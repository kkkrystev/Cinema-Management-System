#include "Commands/header/LogoutCommand.h"

void LogoutCommand::execute(System* system) const
{
	try {
		system->logout();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
