#pragma once
#include "Commands/header/Command.h"

class LoginCommand : public Command
{
	void execute(System* system) const override;
};