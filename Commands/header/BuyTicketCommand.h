#pragma once
#include "Commands/header/Command.h"

class BuyTicketCommand : public Command
{
	void execute(System* system) const override;
};

