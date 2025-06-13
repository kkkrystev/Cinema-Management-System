#pragma once
#include "Helpers/header/MyString.h"
#include "Helpers/header/MyVector.hpp"
#include "Core/header/Ticket.h"
#include "User/header/Catalogue.h"

enum class Role {
	Admin,
	Regular
};

class User
{
public:
	User(const MyString& name, const MyString& password);
	virtual ~User() = default;

	virtual User* clone() const = 0;
	virtual Role getRole() const = 0;

private:
	static int s_nextId;
	int id;

	MyString name;
	MyString password;

	double balance;
	MyVector<Ticket> tickets;
	Catalogue catalogue;
};

