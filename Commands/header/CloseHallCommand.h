#pragma once
#include "Commands/header/Command.h"

class CloseHallCommand : public Command
{
	void execute(System* system) const override;
};

