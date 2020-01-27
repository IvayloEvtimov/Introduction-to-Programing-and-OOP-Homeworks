#include "UserContainer.h"

#include <iostream>

UserContainer::UserContainer(const Admin &admin):currSize(0),maxSize(10),users(nullptr)
{
	users = new User*[maxSize];
	users[currSize++] = admin.clone();
}

UserContainer::~UserContainer()
{
	clean(currSize);
}

void UserContainer::newUser(const char *nickname, const unsigned &age, const char &type,Stats& stats)
{
	if (age < 16)
		throw std::invalid_argument("User must be 16 or older");
	else if (age > 100)
		throw std::invalid_argument("That age can't be right");

	if (currSize == maxSize)
		resize();

	switch (type)
	{
	case 'r':
		users[currSize++] = new Regular(nickname, age);
		break;
	case 'm':
		users[currSize++] = new Moderator(nickname, age);
		break;
	}
	stats.newUser(users[currSize - 1]); //Checks if wheather the new User is the youngest or the oldest
}

void UserContainer::removeUser(const unsigned& pos)
{
	sort(pos); //Puts the user at that position at the end of the array
}

void UserContainer::blockUser(const unsigned &pos,Stats& stats)
{
	users[pos]->setBlock(); 
	stats.newBlocked(users[pos]); //Adds the user to a list of blocked user
}

void UserContainer::unblockUser(const unsigned &pos)
{
	users[pos]->setUnblock();
}

void UserContainer::newPostMade(const unsigned& creatorPos,const unsigned &postID)
{
	users[creatorPos]->addPublication(postID); //Adds the postID in a array of postIDs made by this user
}

void UserContainer::removePostMade(const unsigned &creatorPos, const unsigned &postID)
{
	users[creatorPos]->removePost(postID); //Removes the postID from the arrau of postIDs made by this user
}

bool UserContainer::hasCreatedPosts(const unsigned &creatorPos) const
{
	return users[creatorPos]->hasCreatedPosts(); 
}

bool UserContainer::validatePost(const unsigned &creatorPos,const unsigned& postID) const
{
	return users[creatorPos]->validatePost(postID); //Checks if postID is made by this user
}

bool UserContainer::isAdmin(const char *nickname) const
{
	if (users[0]->checkNickname(nickname)) //The user at 0 position is always the admin
		return true;
	return false;
}

bool UserContainer::hasRights(const unsigned &pos) const
{
	if (users[pos]->isMod()) //The admin has the same rights as a moderator and more
		return true;
	return false;
}

bool UserContainer::isBlocked(const unsigned &pos) const
{
	return users[pos]->isBlocked(); //The blocked flag is used for quick checking wheather the selected user is blocked
}

int UserContainer::userExists(const char *nickname) const
{
	bool found = false;
	for (unsigned count = 0; count < currSize; ++count)
	{
		if (users[count]->checkNickname(nickname)) //Checks every name in the array
		{
			found = true; //until one is found
			return count; //since most of the time the position of that user is needed
		}
	}

	if (!found) //If there isn't any user with such name throw exception and catch it outside the System class
		throw std::invalid_argument("No such user exist");

	return -1; //If there isn't such User it shouldn't come here because it will throw exception
}

bool UserContainer::nameTaken(const char *nickname) const
{
	for (unsigned count = 0; count < currSize; ++count)
		if (users[count]->checkNickname(nickname)) 
			return true;

	return false;
}

void UserContainer::changeNickname(const unsigned &actorPos, const char *newName)
{
	users[actorPos]->changeNickname(newName);
}

void UserContainer::print() const
{
	if (currSize == 0)
		std::cout << "There are no users" << std::endl;
	else
		std::cout << "There are " << currSize << " users." << std::endl;

	for (unsigned count = 0; count < currSize; ++count)
		users[count]->print();
}

void UserContainer::resize() //Increasing users array so that there could be more pointers to User 
{
	User** temp = new User*[maxSize * 2];
	for (unsigned count = 0; count < currSize; count++)
		temp[count] = users[count];

	delete[] users;
	users = temp;
}

void UserContainer::sort(const unsigned &toRemove) //Puts a given pointer to User in last position
{
	for (unsigned count = toRemove; count < maxSize - 1; count++)
	{
		User* temp = users[count];
		users[count] = users[count + 1];
		users[count + 1] = temp;
	}
	delete users[maxSize - 1];
	currSize -= 1;
}

void UserContainer::clean(const unsigned &num) //Frees memory of all users
{
	for (unsigned count = 0; count < num; count++)
		delete users[count];
	delete[] users;

	users = nullptr;
	currSize = 0;
	maxSize = 0;
}
