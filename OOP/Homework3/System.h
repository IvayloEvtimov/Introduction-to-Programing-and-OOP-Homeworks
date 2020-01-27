#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <fstream>

#include "PostContainer.h"
#include "UserContainer.h"
#include "Stats.h"

#include "Helper.h"

class System
{
public:
	System(const Admin&);

	void newUser(const char*, const char*, const int&, const char&);
	void removeUser(const char*, const char*);

	void blockUser(const char*, const char*);
	void unblockUser(const char*, const char*);

	void newPost(const char*, const char*, const char*, const char&);
	void removePost(const char*, const int&);
	void viewPost(const char*, const int&) const;
	void viewAll(const char*, const char*) const;

	void changeNickname(const char*, const char*);

	void statistic() const;
private:
	UserContainer users;
	PostContainer posts;
	Stats stats;
};

#endif // !SYSTEM_H_INCLUDED
