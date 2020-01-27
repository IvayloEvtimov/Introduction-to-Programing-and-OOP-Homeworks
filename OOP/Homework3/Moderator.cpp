#include "Moderator.h"

#include <iostream>

Moderator::Moderator(const char *nickname, const int &age):User(nickname,age)
{

}

bool Moderator::isAdmin() const
{
	return false;
}

bool Moderator::isMod() const
{
	return true;
}

void Moderator::print() const
{
	std::cout << nickname << " - Moderator, " << currSize << " posts\n";
}

User * Moderator::clone() const
{
	return new Moderator(*this);
}
