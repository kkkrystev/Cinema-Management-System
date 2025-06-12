// Kristian Krasimirov Krastev
// 4MI0600440

#include "Helpers/header/MyString.h"
#include <fstream>
#include <cstring>
#pragma warning (disable:4996)

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

void MyString::copyFrom(const MyString& other)
{
	data = new char[other.capacity + 1];
	strcpy(data, other.data);

	size = other.size;
	capacity = other.capacity;
}
void MyString::moveFrom(MyString&& other)
{
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

void MyString::resize(size_t newCapacity)
{
	char* newData = new char[newCapacity + 1];
	newData[0] = '\0';

	if (data)
		strcpy(newData, data);

	delete[] data;
	data = newData;
	capacity = newCapacity;
}

unsigned MyString::getNextPowerOfTwo(size_t n)
{
	unsigned res = 1;
	while (res <= n)
	{
		res *= 2;
	}

	return res;
}
unsigned MyString::getMaxResizeCapacity(size_t n)
{
	return std::max(getNextPowerOfTwo(n), 16u);
}

MyString::MyString()
{
	size = 0;
	capacity = INITIAL_CAPACITY;
	data = new char[capacity + 1];
	data[0] = '\0';
}
MyString::MyString(const char* str)
{
	if (!str) str = "";

	size = strlen(str);
	capacity = getMaxResizeCapacity(size);
	data = new char[capacity + 1];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}
MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}
MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getSize() const
{
	return size;
}
size_t MyString::getCapacity() const
{
	return capacity - 1;
}
const char* MyString::c_str() const
{
	return data;
}

const char& MyString::operator[](size_t idx) const
{
	if (idx >= size) throw std::out_of_range("Index out of range");
	return data[idx];
}
char& MyString::operator[](size_t idx)
{
	if (idx >= size) throw std::out_of_range("Index out of range");
	return data[idx];
}

MyString& MyString::operator+=(const MyString& other)
{
	if (size + other.size + 1 > capacity)
		resize(getMaxResizeCapacity(size + other.size));

	for (size_t i = 0; i < other.size; ++i) {
		data[size + i] = other.data[i];
	}

	size += other.size;
	data[size] = '\0';

	return *this;
}

void MyString::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&size, sizeof(size));
	ofs.write(data, size * sizeof(char));
}

void MyString::loadFromBinaryFile(std::ifstream& ifs)
{
	delete[] data;

	ifs.read((char*)&size, sizeof(size));

	capacity = getMaxResizeCapacity(size);

	data = new char[capacity + 1];
	ifs.read(data, size);
	data[size] = '\0';
}

MyString MyString::substr(unsigned begin, unsigned howMany)
{
	if (begin + howMany > size)
		throw std::out_of_range("Substring range out of bounds");

	MyString result;

	result.capacity = getMaxResizeCapacity(howMany);
	result.size = howMany;

	result.data = new char[result.capacity+1];
	strncat(result.data, data + begin, howMany);

	return result;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs);
	result += rhs;
	return result;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.data;
}
std::istream& operator>>(std::istream& is, MyString& str)
{
	char buffer[1024];
	is >> buffer;

	size_t bufferLen = strlen(buffer);
	if (bufferLen >= str.capacity)
		str.resize(MyString::getMaxResizeCapacity(bufferLen));

	strcpy(str.data, buffer);
	str.size = bufferLen;

	return is;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}
bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}
bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

void MyString::debug() const
{
	std::cout << "DATA: \"" << data << "\", SIZE: " << size
		<< ", strlen: " << strlen(data)
		<< ", CAPACITY: " << capacity << std::endl;
}