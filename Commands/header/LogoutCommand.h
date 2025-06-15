#pragma once
#include "Commands/header/Command.h"

class LogoutCommand : public Command
{
	void execute(System* system) const override;
};

