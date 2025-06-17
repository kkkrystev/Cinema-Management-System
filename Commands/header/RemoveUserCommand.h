#pragma once
#include "Commands/header/Command.h"

class RemoveUserCommand : public Command
{
	void execute(System* system) const override;
};