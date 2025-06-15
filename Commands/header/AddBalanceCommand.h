#pragma once
#include "Commands/header/Command.h"

class AddBalanceCommand : public Command
{
	void execute(System* system) const override;
};

