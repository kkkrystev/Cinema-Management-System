#pragma once
#include "System/header/System.h"
#include "Helpers/header/MyString.h"

class Command
{
public:
	virtual void execute(System* system) const = 0;
	virtual ~Command() = default;
};

