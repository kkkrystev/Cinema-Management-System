#include "System/header/SystemLauncher.h"
#include "Commands/header/Command.h"
#include "Commands/header/CommandFactory.h"

void SystemLauncher::printLegend()
{
    std::cout << "===== All-User-Access Commands =====\n";
    std::cout << "  register                   <name> <password>\n";
    std::cout << "  login                      <name> <password>\n";
    std::cout << "  logout\n";
    std::cout << "  add-balance                <amount>\n";
    std::cout << "  wallet\n";
    std::cout << "  view-screening-hall        <screening-id>\n";
    std::cout << "  buy-ticket                 <screening-id> <row> <col>\n";
    std::cout << "  rate-movie                 <movie-id> <rating>\n";
    std::cout << "  list-screenings\n";
    std::cout << "  list-history\n";
    std::cout << "  list-tickets\n";

    std::cout << "\n===== Admin Commands =====\n";
    std::cout << "  add-movie                  <genre> <title> <release-year> <duration> \n";
    std::cout << "                           + <action-intensity>\n";
    std::cout << "                           + <theme> <is-based-on-true-events>\n";
    std::cout << "                           + <has-comedy-elements>\n";
    std::cout << "  add-screening              <movie-id> <hall-id> <screening-date> <start-time> <end-time>\n";
    std::cout << "  remove-user                <user-id>\n";
    std::cout << "  remove-movie               <movie-id>\n";
    std::cout << "  remove-screening           <screening-id>\n";
    std::cout << "  open-hall                  <rows> <cols>\n";
    std::cout << "  close-hall                 <hall-id>\n";
    std::cout << "  update-movie-title         <movie-id> <new-title>\n";
    std::cout << "  update-screening-hall      <movie-id> <new-hall-id>\n";
    std::cout << "  update-user-history        <user-id>\n";
    std::cout << "  update-user-history        <user-id>\n";
    std::cout << "  update-users\n";
    std::cout << '\n';
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

        try {
            command->execute(&system);
        }
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }

		delete command;

		std::cout << '\n';
	}
}
