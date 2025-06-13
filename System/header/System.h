#pragma once
#include "Helpers/header/MyVector.hpp"
#include "Helpers/header/PolymorphicPtr.hpp"
#include "User/header/User.h"
#include "Core/header/Movie.h"
#include "Core/header/Hall.h"

class System
{
public:
	// All user commands
	
	// Admin specific
private:
	MyVector<PolymorphicPtr<User>> users;
	MyVector<PolymorphicPtr<Movie>> movies;
	MyVector<Hall> halls;
};

