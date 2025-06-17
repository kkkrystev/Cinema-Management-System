#pragma once
#include "Commands/header/Command.h"

class UpdateScreeningHallCommand : public Command
{
	void execute(System* system) const override;
};

