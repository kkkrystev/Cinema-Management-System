#pragma once
#include "Commands/header/Command.h"

class ListMoviesCommand : public Command
{
	void execute(System* system) const override;
};

