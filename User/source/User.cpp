#include "User/header/User.h"
#include <fstream>

int User::s_nextId = 100;

User::User() : id(-1), balance(0.0) {}

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

void User::setNextId(int nextId)
{
    s_nextId = nextId;
}

void User::saveToBinaryFile(std::ofstream& ofs) const
{
    ofs.write((const char*)&id, sizeof(id));
    name.saveToBinaryFile(ofs);
    password.saveToBinaryFile(ofs);
    ofs.write((const char*)&balance, sizeof(balance));

    size_t ticketCount = tickets.getSize();
    ofs.write((const char*)&ticketCount, sizeof(ticketCount));
    for (size_t i = 0; i < ticketCount; i++)
        tickets[i].saveToBinaryFile(ofs);

    size_t catalogueCount = catalogue.getSize();
    ofs.write((const char*)&catalogueCount, sizeof(catalogueCount));
    for (size_t i = 0; i < catalogueCount; i++)
        ofs.write((const char*)&catalogue[i], sizeof(int));
}
void User::loadFromBinaryFile(std::ifstream& ifs)
{
    ifs.read((char*)&id, sizeof(id));
    name.loadFromBinaryFile(ifs);
    password.loadFromBinaryFile(ifs);
    ifs.read((char*)&balance, sizeof(balance));

    size_t ticketCount;
    ifs.read((char*)&ticketCount, sizeof(ticketCount));
    tickets.clear();
    for (size_t i = 0; i < ticketCount; i++) {
        Ticket ticket;
        ticket.loadFromBinaryFile(ifs);
        tickets.push_back(std::move(ticket));
    }

    size_t catalogueCount;
    ifs.read((char*)&catalogueCount, sizeof(catalogueCount));
    catalogue.clear();
    for (size_t i = 0; i < catalogueCount; i++) {
        int movieId;
        ifs.read((char*)&movieId, sizeof(int));
        catalogue.push_back(movieId);
    }
}

bool User::hasTicket(int movieId) const
{
    for (size_t i = 0; i < tickets.getSize(); i++) {
        if (tickets[i].getMovieId() == movieId) return true;
    }
    return false;
}
bool User::isInCatalogue(int movieId) const
{
    for (size_t i = 0; i < catalogue.getSize(); i++) {
        if (catalogue[i] == movieId) return true;
    }
    return false;
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
void User::returnTickets(int movieId, double price)
{
    for (size_t i = 0; i < tickets.getSize(); ) {
        if (tickets[i].getMovieId() == movieId) {
            tickets.erase(i);
            addBalance(price);
        }
        else ++i;
    }
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
    removeTickets(movieId);

    if (isInCatalogue(movieId)) return;
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

