#pragma once
#include "Commands/header/Command.h"

class ListUsersCommand : public Command
{
    void execute(System* system) const override;
};

