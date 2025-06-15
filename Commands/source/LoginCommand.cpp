#include "Commands/header/LoginCommand.h"

void LoginCommand::execute(System* system) const
{
	MyString name, password;

	std::cin >> name >> password;

	try {
		system->login(name, password);
	}
	catch (std::exception& e) {
		std::cout << e.what() << '\n';
	}
}
