#include "Commands/header/ListUsersCommand.h"

void ListUsersCommand::execute(System* system) const
{
	try {
		system->listUsers();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
