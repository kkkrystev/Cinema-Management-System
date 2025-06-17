#include "Commands/header/ListUserHistoryCommand.h"

void ListUserHistoryCommand::execute(System* system) const
{
	int userId;

	std::cin >> userId;

	try {
		system->listUserHistory(userId);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
