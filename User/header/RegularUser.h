#pragma once
#include "User/header/User.h"

class RegularUser : public User
{
public:
	RegularUser(const MyString& name, const MyString& password);

	User* clone() const override;
	Role getRole() const override;
};

