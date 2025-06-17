#pragma once
#include "Commands/header/Command.h"

class ViewScreeningHallCommand : public Command
{
	void execute(System* system) const override;
};

