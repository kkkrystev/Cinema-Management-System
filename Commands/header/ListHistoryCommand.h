#pragma once
#include "Commands/header/Command.h"

class ListHistoryCommand : public Command
{
	void execute(System* system) const override;
};

