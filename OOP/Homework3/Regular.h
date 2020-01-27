#ifndef REGULAR_H_INCLUDED
#define REGULAR_H_INCLUDED

#include "User.h"

class Regular :public User
{
public:
	Regular(const char*,const int&);

	virtual bool isAdmin() const;
	virtual bool isMod() const;

	virtual void print() const;

	virtual User* clone()const;
};

#endif // !REGULAR_H_INCLUDED
