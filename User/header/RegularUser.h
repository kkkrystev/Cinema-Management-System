#pragma once
#include "User/header/User.h"

class RegularUser : public User
{
public:
	RegularUser();
	User* clone() const override;
	Role getRole() const override;
};

