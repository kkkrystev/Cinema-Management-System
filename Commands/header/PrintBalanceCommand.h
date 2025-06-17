#pragma once
#include "Commands/header/Command.h"

class PrintBalanceCommand : public Command
{
	void execute(System* system) const override;
};

