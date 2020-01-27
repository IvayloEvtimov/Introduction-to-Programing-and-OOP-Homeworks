#include "Regular.h"

#include <iostream>

Regular::Regular(const char *nickname, const int&age):User(nickname,age)
{

}

bool Regular::isAdmin() const
{
	return false;
}

bool Regular::isMod() const
{
	return false;
}

void Regular::print() const
{
	std::cout << nickname << " - Regular user, " << currSize << " posts\n";
}

User * Regular::clone() const
{
	return new Regular(*this);
}
