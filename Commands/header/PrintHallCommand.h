#pragma once
#include "Commands/header/Command.h"

class PrintHallCommand : public Command
{
	void execute(System* system) const override;
};

