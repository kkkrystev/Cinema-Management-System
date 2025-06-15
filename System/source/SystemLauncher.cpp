#include "System/header/SystemLauncher.h"
#include "Commands/header/Command.h"
#include "Commands/header/CommandFactory.h"

void SystemLauncher::run()
{
	System& system = System::getInstance();

	MyString commandStr;
	Command* command;

	while (true) {
		std::cout << "> ";
		std::cin >> commandStr;

		if (commandStr == "exit") break;

		command = CommandFactory::createCommand(commandStr);

		if (!command) {
			std::cout << "Invalid command" << '\n' << '\n';
			continue;
		}

		command->execute(&system);
		delete command;

		std::cout << '\n';
	}
}
