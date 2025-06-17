#pragma once
#include "Commands/header/Command.h"

class ListUserHistoryCommand : public Command
{
	void execute(System* system) const override;
};

