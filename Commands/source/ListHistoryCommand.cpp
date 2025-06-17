#include "Commands/header/ListHistoryCommand.h"

void ListHistoryCommand::execute(System* system) const
{
	try {
		system->listHistory();
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
