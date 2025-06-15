#pragma once
#include "Commands/header/Command.h"

class UpdateMovieTitleCommand : public Command
{
	void execute(System* system) const override;
};

