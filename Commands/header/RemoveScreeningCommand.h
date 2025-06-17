#pragma once
#include "Commands/header/Command.h"

class RemoveScreeningCommand : public Command
{
	void execute(System* system) const override;
};