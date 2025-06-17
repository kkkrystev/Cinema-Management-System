#include "Commands/header/LoginCommand.h"

void LoginCommand::execute(System* system) const
{
	MyString name, password;

	std::cin >> name >> password;

	system->login(name, password);
}
