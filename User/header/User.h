#pragma once
#include "Helpers/header/MyString.h"
#include "MyVector.hpp"
#include "Ticket.h"
#include "Catalogue.h"

class User
{
	MyString name;
	MyString password;

	double balance;
	MyVector<Ticket> tickets;
	Catalogue catalogue;
};

