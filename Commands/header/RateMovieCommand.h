#pragma once
#include "Commands/header/Command.h"

class RateMovieCommand : public Command
{
	void execute(System* system) const override;
};

