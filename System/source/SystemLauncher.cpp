#include "System/header/SystemLauncher.h"
#include "Commands/header/Command.h"
#include "Commands/header/CommandFactory.h"

void SystemLauncher::printLegend()
{
    std::cout << "===== Available Commands =====\n";
    std::cout << "  register         <name> <password>\n";
    std::cout << "  login            <name> <password>\n";
    std::cout << "  logout\n";
    std::cout << "  add-balance      <amount>\n";
    std::cout << "  wallet\n";
    std::cout << "  view-hall        <hall-id>\n";
    std::cout << "  buy-ticket       <movie-id> <row> <col>\n";
    std::cout << "  rate-movie       <movie-id> <rating>\n";
    std::cout << "  list-movies\n";
    std::cout << "  list-history\n";
    std::cout << "  list-tickets\n";

    std::cout << "\n===== Admin Commands =====\n";
    std::cout << "  add-movie              <genre> <title> <release-year> <duration> <hall-id> <date> <start-time> <end-time>\n";
    std::cout << "                          + <action-intensity>\n";
    std::cout << "                          + <theme> <is-based-on-true-events>\n";
    std::cout << "                          + <has-comedy-elements>\n";
    std::cout << "  remove-movie           <movie-id>\n";
    std::cout << "  remove-user            <user-id>\n";
    std::cout << "  open-hall              <rows> <cols>\n";
    std::cout << "  close-hall             <hall-id>\n";
    std::cout << "  update-movie-title     <movie-id> <new-title>\n";
    std::cout << "  update-movie-hall      <movie-id> <new-hall-id>\n\n";
}

void SystemLauncher::run()
{
	System& system = System::getInstance();

	MyString commandStr;
	Command* command;

	while (true) {
		std::cout << "> ";
		std::cin >> commandStr;

        if (commandStr == "legend") {
            printLegend();
            continue;
        }
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
