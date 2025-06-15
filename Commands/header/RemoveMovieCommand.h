#pragma once
#include "Commands/header/Command.h"

class RemoveMovieCommand : public Command
{
	void execute(System* system) const override;
};

