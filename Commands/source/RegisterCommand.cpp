#include "Commands/header/RegisterCommand.h"

void RegisterCommand::execute(System* system) const
{
	MyString name, password;

	std::cin >> name >> password;

	system->registerUser(name, password);
}
