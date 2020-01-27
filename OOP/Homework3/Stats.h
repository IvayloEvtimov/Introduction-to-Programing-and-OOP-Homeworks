#ifndef STATS_H_INCUDED
#define STATS_H_INCUDED

#include "Admin.h"

class Stats  //This class is used for collection information about the current System 
{           //Likes making a list of blocked user for quick printing  or looking
public:    //And the youngest and oldest user
	Stats(const Admin&);
	Stats(const Stats&);
	Stats& operator=(const Stats&);
	~Stats();

	void print() const;

	void newBlocked(const User*);
	void newUnblocked(const char*);
	void newUser(const User*);
	void changeName(const char*, const char*);
private:
	void resize();
	void sort(const int&);
	void cleanBlocked();
private:
	int currBlockedUsers;
	int maxBlockedUsers;
	User ** blockedUsers;
	User* oldestUser;
	User* youngestUser;
};

#endif // !STATS_H_INCUDED
