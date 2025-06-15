#include "User/header/Admin.h"

const MyString Admin::ADMMIN_NAME = "Admin";
const MyString Admin::ADMIN_PASSWORD = "0000";
const double Admin::ADMIN_BALANCE = 999999.0;

Admin::Admin() : User(ADMMIN_NAME, ADMIN_PASSWORD)
{
	addBalance(ADMIN_BALANCE);
}

User* Admin::clone() const
{
	return new Admin(*this);
}
Role Admin::getRole() const
{
	return Role::Admin;
}
