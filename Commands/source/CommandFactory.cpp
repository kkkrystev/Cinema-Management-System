#include "Commands/header/CommandFactory.h"

#include "Commands/header/RegisterCommand.h"
#include "Commands/header/LoginCommand.h"
#include "Commands/header/LogoutCommand.h"
#include "Commands/header/AddBalanceCommand.h"
#include "Commands/header/PrintBalanceCommand.h"
#include "Commands/header/ViewScreeningHallCommand.h"
#include "Commands/header/BuyTicketCommand.h"
#include "Commands/header/RateMovieCommand.h"
#include "Commands/header/ListMoviesCommand.h"
#include "Commands/header/ListScreeningsCommand.h"
#include "Commands/header/ListHistoryCommand.h"
#include "Commands/header/ListTicketsCommand.h"

#include "Commands/header/AddMovieCommand.h"
#include "Commands/header/AddScreeningCommand.h"
#include "Commands/header/RemoveUserCommand.h"
#include "Commands/header/RemoveMovieCommand.h"
#include "Commands/header/RemoveScreeningCommand.h"
#include "Commands/header/OpenHallCommand.h"
#include "Commands/header/CloseHallCommand.h"
#include "Commands/header/UpdateMovieTitleCommand.h"
#include "Commands/header/UpdateScreeningHallCommand.h"
#include "Commands/header/ListUserTicketsCommand.h"
#include "Commands/header/ListUserHistoryCommand.h"
#include "Commands/header/ListUsersCommand.h"

Command* CommandFactory::createCommand(const MyString& commandStr)
{
    // All-user-access commands
    if (commandStr == "register") {
        return new RegisterCommand();
    }
    else if (commandStr == "login") {
        return new LoginCommand();
    }
    else if (commandStr == "logout") {
        return new LogoutCommand();
    }
    else if (commandStr == "add-balance") {
        return new AddBalanceCommand();
    }
    else if (commandStr == "wallet") {
        return new PrintBalanceCommand();
    }
    else if (commandStr == "view-screening-hall") {
        return new ViewScreeningHallCommand();
    }
    else if (commandStr == "buy-ticket") {
        return new BuyTicketCommand();
    }
    else if (commandStr == "rate-movie") {
        return new RateMovieCommand();
    }
    else if (commandStr == "list-movies") {
        return new ListMoviesCommand();
    }
    else if (commandStr == "list-screenings") {
        return new ListScreeningsCommand();
    }
    else if (commandStr == "list-history") {
        return new ListHistoryCommand();
    }
    else if (commandStr == "list-tickets") {
        return new ListTicketsCommand();
    }

    // Admin commands
    else if (commandStr == "add-movie") {
        return new AddMovieCommand();
    }
    else if (commandStr == "add-screening") {
        return new AddScreeningCommand();
    }
    else if (commandStr == "remove-user") {
        return new RemoveUserCommand();
    }
    else if (commandStr == "remove-movie") {
        return new RemoveMovieCommand();
    }
    else if (commandStr == "remove-screening") {
        return new RemoveScreeningCommand();
    }
    else if (commandStr == "open-hall") {
        return new OpenHallCommand();
    }
    else if (commandStr == "close-hall") {
        return new CloseHallCommand();
    }
    else if (commandStr == "update-movie-title") {
        return new UpdateMovieTitleCommand();
    }
    else if (commandStr == "update-screening-hall") {
        return new UpdateScreeningHallCommand();
    }
    else if (commandStr == "list-user-tickets") {
        return new ListUserTicketsCommand();
    }
    else if (commandStr == "list-user-history") {
        return new ListUserHistoryCommand();
    }
    else if (commandStr == "list-users") {
        return new ListUsersCommand();
    }

    return nullptr;
}
