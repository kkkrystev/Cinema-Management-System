#pragma once
#include "Commands/header/Command.h"

class OpenHallCommand : public Command
{
	void execute(System* system) const override;
};

