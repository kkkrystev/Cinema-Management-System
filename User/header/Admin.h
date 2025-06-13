#pragma once
#include "User/header/User.h"

class Admin : public User
{
	Admin();
	User* clone() const override;
	Role getRole() const override;
};

