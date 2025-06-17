#pragma once
#include "Commands/header/Command.h"

class ListTicketsCommand : public Command
{
	void execute(System* system) const override;
};

