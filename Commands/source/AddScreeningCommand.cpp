#include "Commands/header/AddScreeningCommand.h"

void AddScreeningCommand::execute(System* system) const
{
	int movieId, hallId;
	Date date;
	Time start, end;

	std::cin >> movieId >> hallId >> date >> start >> end;

	system->addScreening(movieId, hallId, date, start, end);
}
