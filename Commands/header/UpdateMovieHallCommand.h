#pragma once
#include "Commands/header/Command.h"

class UpdateMovieHallCommand : public Command
{
	void execute(System* system) const override;
};

