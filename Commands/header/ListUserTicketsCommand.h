#pragma once
#include "Commands/header/Command.h"

class ListUserTicketsCommand : public Command
{
    void execute(System* system) const override;
};

