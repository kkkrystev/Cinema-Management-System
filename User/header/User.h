#pragma once
#include "Helpers/header/MyString.h"
#include "Helpers/header/MyVector.hpp"
#include "Core/header/Ticket.h"
#include "Helpers/header/Utilities.h"

class User
{
public:
	User();
	User(const MyString& name, const MyString& password);
	virtual ~User() = default;

	virtual User* clone() const = 0;
	virtual Role getRole() const = 0;

	int getId() const;
	const MyString& getName() const;
	const MyString& getPassword() const;

	static void setNextId(int nextId);

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

	bool hasTicket(int movieId) const;
	bool isInCatalogue(int movieId) const;

	void addBalance(double sum);
	void buyTicket(const Ticket& ticket, double price);
	void returnTickets(int movieId, double price);
	void removeTickets(int movieId);
	void addToCatalogue(int movieId);
	void removeFromCatalogue(int movieId);

protected:
	static int s_nextId;
	int id;

	MyString name;
	MyString password;

	double balance;
	MyVector<Ticket> tickets;
	MyVector<int> catalogue;
};

