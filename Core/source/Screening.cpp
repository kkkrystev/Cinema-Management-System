#include "Core/header/Screening.h"

void Screening::free()
{
    for (size_t i = 0; i < rows; ++i)
        delete[] seats[i];
    delete[] seats;
    seats = nullptr;
}
void Screening::copyFrom(const Screening& other)
{
    id = other.id;
    movieId = other.movieId;
    hallId = other.hallId;
    date = other.date;
    hours = other.hours;
    rows = other.rows;
    cols = other.cols;

    seats = new bool* [rows];
    for (size_t i = 0; i < rows; i++) {
        seats[i] = new bool[cols];
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            seats[i][j] = other.seats[i][j];
        }
    }
}
void Screening::moveFrom(Screening&& other)
{
    id = other.id;
    movieId = other.movieId;
    hallId = other.hallId;

    date = std::move(other.date);
    hours = std::move(other.hours);

    rows = other.rows;
    cols = other.cols;
    seats = other.seats;

    other.seats = nullptr;
    other.rows = 0;
    other.cols = 0;
}

int Screening::s_nextId = 1;

void Screening::setNextId(int nextId)
{
    s_nextId = nextId;
}

Screening::Screening()
    : id(-1), movieId(-1), hallId(-1), date(), hours(), seats(nullptr), rows(0), cols(0) {}

Screening::Screening(int movieId, int hallId, size_t rows, size_t cols, const Date& date, const TimeInterval& hours)
    : id(s_nextId++), movieId(movieId), hallId(hallId), rows(rows), cols(cols), date(date), hours(hours) 
{
    seats = new bool* [rows];
    for (size_t i = 0; i < rows; i++) {
        seats[i] = new bool[cols];
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            seats[i][j] = false;
        }
    }
}

Screening::Screening(const Screening& other)
{
    copyFrom(other);
}
Screening::Screening(Screening&& other) noexcept
{
    moveFrom(std::move(other));
}

Screening& Screening::operator=(const Screening& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
Screening& Screening::operator=(Screening&& other) noexcept
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

Screening::~Screening()
{
    free();
}

int Screening::getId() const
{
    return id;
}
int Screening::getMovieId() const
{
    return movieId;
}
int Screening::getHallId() const
{
    return hallId;
}
const Date& Screening::getDate() const
{
    return date;
}
const TimeInterval& Screening::getHours() const
{
    return hours;
}
void Screening::print() const
{
    std::cout << "Screening ID: " << id
        << " | Movie ID: " << movieId
        << " | Hall: " << hallId
        << " | Date: " << date
        << " | Time: " << hours;
}

bool Screening::isSeatTaken(size_t row, size_t col) const
{
    if (row >= rows || col >= cols)
        throw std::out_of_range("Invalid seat coordinates.");

    return seats[row][col] == true;
}
void Screening::reserveSeat(size_t row, size_t col)
{
    if (isSeatTaken(row, col))
        throw std::logic_error("Unfortunately this seat is already taken.");

    seats[row][col] = true;
}
void Screening::freeSeat(size_t row, size_t col)
{
    if (row >= rows || col >= cols)
        throw std::out_of_range("Invalid seat coordinates.");

    seats[row][col] = false;
}
void Screening::setHallId(int hallId)
{
    this->hallId = hallId;
}
void Screening::printSeats() const
{
    size_t totalWidth = cols * 3 - 1;  // Each seat + space takes 2 chars, add 1 more for better alignment

    MyString screenLabel = "=== SCREEN ===";
    size_t padding = (totalWidth > screenLabel.getSize()) ? (totalWidth - screenLabel.getSize()) / 2 : 0;

    MyString spaces = "";
    for (size_t i = 0; i < padding; ++i) {
        spaces = spaces + " ";
    }

    MyString line = spaces + screenLabel;

    std::cout << line << "\n\n";

    // Print column numbers aligned to seats
    std::cout << "    ";
    for (size_t c = 0; c < cols; ++c) {
        if (c + 1 < 10)
            std::cout << " " << (c + 1) << " ";
        else
            std::cout << (c + 1) << " ";
    }
    std::cout << '\n';

    for (size_t r = 0; r < rows; ++r) {
        // Align row numbers: 1-digit rows get 2 spaces, 2-digit rows 1 space for same width
        if (r + 1 < 10)
            std::cout << " " << (r + 1) << "  ";
        else
            std::cout << (r + 1) << "  ";

        // Print seats spaced to align under column numbers
        for (size_t c = 0; c < cols; ++c) {
            char seatChar = seats[r][c] ? 'X' : 'O';
            std::cout << " " << seatChar << " ";
        }
        std::cout << '\n';
    }
}

void Screening::saveToBinaryFile(std::ofstream& ofs) const
{
    ofs.write((const char*)&id, sizeof(id));
    ofs.write((const char*)&movieId, sizeof(movieId));
    ofs.write((const char*)&hallId, sizeof(hallId));
    date.saveToBinaryFile(ofs);
    hours.saveToBinaryFile(ofs);
    ofs.write((const char*)&rows, sizeof(rows));
    ofs.write((const char*)&cols, sizeof(cols));

    for (size_t i = 0; i < rows; ++i) {
        ofs.write((const char*)seats[i], sizeof(bool) * cols);
    }
}
void Screening::loadFromBinaryFile(std::ifstream& ifs)
{
    ifs.read((char*)&id, sizeof(id));
    ifs.read((char*)&movieId, sizeof(movieId));
    ifs.read((char*)&hallId, sizeof(hallId));
    date.loadFromBinaryFile(ifs);
    hours.loadFromBinaryFile(ifs);
    ifs.read((char*)&rows, sizeof(rows));
    ifs.read((char*)&cols, sizeof(cols));

    seats = new bool* [rows];
    for (size_t i = 0; i < rows; ++i) {
        seats[i] = new bool[cols];
        ifs.read((char*)seats[i], sizeof(bool) * cols);
    }
}