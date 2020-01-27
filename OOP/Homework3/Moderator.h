#ifndef MODERATOR_H_INCLUDED
#define MODERATOR_H_INCLUDED

#include "User.h"

class Moderator: public User
{
public:
	Moderator(const char*, const int&);

	virtual bool isAdmin() const;
	virtual bool isMod() const;

	virtual void print() const;

	virtual User* clone() const;
};

#endif // !MODERATOR_H_INCLUDED
