#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include "User.h"

class Admin : public User
{
public:
	Admin(const char*, const int&);

	virtual bool isAdmin() const;
	virtual bool isMod() const;

	virtual void print() const;

	virtual Admin* clone() const;
};

#endif // !ADMIN_H_INCLUDED
