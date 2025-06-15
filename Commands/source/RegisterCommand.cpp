#include "Commands/header/RegisterCommand.h"

void RegisterCommand::execute(System* system) const
{
	MyString name, password;

	std::cin >> name >> password;

	try {
		system->registerUser(name, password);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
