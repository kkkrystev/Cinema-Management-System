#pragma once
#include "Commands/header/Command.h"

class AddScreeningCommand : public Command
{
	void execute(System* system) const override;
};