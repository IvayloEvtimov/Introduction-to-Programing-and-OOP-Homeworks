#include "Admin.h"

#include <iostream>

Admin::Admin(const char *nickname, const int &age):User(nickname,age)
{

}

bool Admin::isAdmin() const
{
	return true;
}

bool Admin::isMod() const
{
	return true;
}

void Admin::print() const
{
	std::cout << nickname << " - Admin, " << currSize << " posts\n";
}

Admin * Admin::clone() const
{
	return new Admin(*this);
}
