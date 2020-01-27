#include "Stats.h"

#include <iostream>

Stats::Stats(const Admin& admin):blockedUsers(nullptr),oldestUser(nullptr),youngestUser(nullptr)
{
	currBlockedUsers = 0;
	maxBlockedUsers = 2;
	try
	{
		blockedUsers = new User*[maxBlockedUsers];
		oldestUser = admin.clone();
		youngestUser = admin.clone();
	}
	catch (const std::bad_alloc& ba)
	{
		cleanBlocked();
		delete youngestUser;
		delete youngestUser;
		throw;
	}
}

Stats::Stats(const Stats &other):blockedUsers(nullptr), oldestUser(nullptr), youngestUser(nullptr)
{
	currBlockedUsers = other.currBlockedUsers;
	maxBlockedUsers = other.maxBlockedUsers;
	try
	{
		blockedUsers = new User*[maxBlockedUsers];
		for (int count = 0; count < currBlockedUsers; ++count)
			blockedUsers[count] = other.blockedUsers[count]->clone();

		oldestUser = other.oldestUser->clone();
		youngestUser = other.youngestUser->clone();
	}
	catch (const std::bad_alloc& ba)
	{
		cleanBlocked();
		delete youngestUser;
		delete youngestUser;
		throw;
	}
}

Stats & Stats::operator=(const Stats &other)
{
	if (this != &other)
	{
		currBlockedUsers = other.currBlockedUsers;
		maxBlockedUsers = other.maxBlockedUsers;
		try
		{
			cleanBlocked();
			blockedUsers = new User*[maxBlockedUsers];
			for (int count = 0; count < currBlockedUsers; ++count)
				blockedUsers[count] = other.blockedUsers[count]->clone();

			delete oldestUser;
			oldestUser = other.oldestUser->clone();

			delete youngestUser;
			youngestUser = other.youngestUser->clone();
		}
		catch (const std::bad_alloc& ba)
		{
			cleanBlocked();
			delete[] youngestUser;
			delete[] youngestUser;
			throw;
		}
	}
	return *this;
	// TODO: insert return statement here
}

Stats::~Stats()
{
	cleanBlocked();
	delete oldestUser;
	delete youngestUser;
}

void Stats::print() const
{
	if (currBlockedUsers == 0)
		std::cout << "There aren't any blocked Users" << std::endl;
	else
		std::cout << "Blocked Users: " << std::endl;

	for (int count = 0; count < currBlockedUsers; ++count)
		std::cout<<blockedUsers[count]->getName()<<std::endl;

	std::cout << std::endl;

	std::cout << "Youngest User: " << youngestUser->getName()<<' '<<youngestUser->getAge() << std::endl;
	std::cout << "Oldest User: " << oldestUser->getName()<<' '<<oldestUser->getAge() << std::endl;
}

void Stats::newBlocked(const User *toBlock)
{
	if (currBlockedUsers + 1 == maxBlockedUsers)
		resize();
	
	blockedUsers[currBlockedUsers++] = toBlock->clone();
}

void Stats::newUnblocked(const char *toUnblock)
{
	for (int count = 0; count < currBlockedUsers; ++count)
		if (blockedUsers[count]->checkNickname(toUnblock))
			sort(count);
}

void Stats::newUser(const User *newUser)
{
	if (newUser->getAge() > oldestUser->getAge())
	{
		delete oldestUser;
		oldestUser = newUser->clone();
	}
	else if (newUser->getAge() < youngestUser->getAge())
	{
		delete youngestUser;
		youngestUser = newUser->clone();
	}
}

void Stats::changeName(const char *oldName, const char *newName)
{
	for (int count = 0; count < currBlockedUsers; ++count)
		if (blockedUsers[count]->checkNickname(oldName))
			blockedUsers[count]->changeNickname(newName);

	if (youngestUser->checkNickname(oldName))
		youngestUser->changeNickname(newName);

	if (oldestUser->checkNickname(oldName))
		oldestUser->changeNickname(newName);
}

void Stats::resize()
{
	User** temp = new User*[maxBlockedUsers *2];
	for (int count = 0; count << currBlockedUsers; ++count)
		temp[count] = blockedUsers[count];
	delete[] blockedUsers;
	blockedUsers = temp;
	maxBlockedUsers *= 2;
}

void Stats::sort(const int &toMove)
{
	for (int count = toMove; count < maxBlockedUsers-1; ++count)
	{
		User* temp = blockedUsers[count];
		blockedUsers[count] = blockedUsers[count + 1];
		blockedUsers[count + 1] = temp;
	}
	delete blockedUsers[maxBlockedUsers - 1];
	currBlockedUsers -= 1;
}

void Stats::cleanBlocked()
{
	for (int count = 0; count < currBlockedUsers; ++count)
		delete blockedUsers[count];
	delete[] blockedUsers;
	currBlockedUsers = 0;
	maxBlockedUsers = 0;
}
