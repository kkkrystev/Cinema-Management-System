#include "Commands/header/RemoveUserCommand.h"

void RemoveUserCommand::execute(System* system) const
{
	int userId;
	
	std::cin >> userId;

	try {
		system->removeUser(userId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
