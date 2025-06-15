#pragma once
#include "Commands/header/Command.h"

class RegisterCommand : public Command
{
	void execute(System* system) const override;
};

