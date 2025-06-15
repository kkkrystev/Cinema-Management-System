#pragma once
#include "Commands/header/Command.h"

class AddMovieCommand : public Command
{
	void execute(System* system) const override;
};

