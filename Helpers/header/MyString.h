// Kristian Krasimirov Krastev
// 4MI0600440

#pragma once
#include <iostream>

class MyString
{
public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	~MyString();

	size_t getSize() const;
	size_t getCapacity() const;
	const char* c_str() const;

	const char& operator[](size_t idx) const;
	char& operator[](size_t idx);

	MyString& operator+=(const MyString& other);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

	MyString substr(unsigned begin, unsigned howMany);

	void debug() const;

private:
	char* data;
	size_t size;
	size_t capacity; // does NOT include space '\0'

	static constexpr size_t INITIAL_CAPACITY = 16;

	void free();

	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);

	void resize(size_t newCapacity);

	static unsigned getNextPowerOfTwo(size_t n);
	static unsigned getMaxResizeCapacity(size_t n);
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);