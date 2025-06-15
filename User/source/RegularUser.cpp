#include "User/header/RegularUser.h"

RegularUser::RegularUser() : User() {}
RegularUser::RegularUser(const MyString& name, const MyString& password) : User(name, password) {}

User* RegularUser::clone() const
{
	return new RegularUser(*this);
}

Role RegularUser::getRole() const
{
	return Role::Regular;
}
