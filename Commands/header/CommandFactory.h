#pragma once
#include "Command.h"

class CommandFactory
{
public:
	static Command* createCommand(const MyString& commandStr);
};

