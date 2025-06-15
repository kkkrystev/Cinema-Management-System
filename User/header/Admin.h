#pragma once
#include "User/header/User.h"

class Admin : public User
{
public:
	Admin();

	User* clone() const override;
	Role getRole() const override;

private:
	static const MyString ADMMIN_NAME;
	static const MyString ADMIN_PASSWORD;
	static const double ADMIN_BALANCE;
};

