#include "User/header/User.h"

int User::s_nextId = 100;

User::User(const MyString& name, const MyString& password)
    : name(name), password(password), id(s_nextId++), balance(0.0), tickets(), catalogue() {}

int User::getId() const
{
    return id;
}
const MyString& User::getName() const
{
    return name;
}
const MyString& User::getPassword() const
{
    return password;
}

void User::addBalance(double sum)
{
    balance += sum;
}

void User::buyTicket(const Ticket& ticket, double price)
{
    if (balance < price)
        throw std::logic_error("Isufficient funds.");

    tickets.push_back(ticket);
    balance -= price;
}
void User::removeTickets(int movieId)
{
    for (size_t i = 0; i < tickets.getSize(); ) {
        if (tickets[i].getMovieId() == movieId)
            tickets.erase(i);
        else ++i;
    }
}

void User::addToCatalogue(int movieId)
{
    catalogue.push_back(movieId);
}
void User::removeFromCatalogue(int movieId)
{
    for (size_t i = 0; i < catalogue.getSize(); ) {
        if (catalogue[i] == movieId)
            catalogue.erase(i);
        else ++i;
    }
}

