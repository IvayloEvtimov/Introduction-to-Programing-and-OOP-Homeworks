#include <iostream>

#include "User.h"

#include "Image.h"
#include "Link.h"
#include "Text.h"

User::User(const char *nickname, const int &age) :nickname(nullptr), age(age), blocked(false),currSize(0),maxSize(5),postMadeID(nullptr)
{
	if (nickname == nullptr)
		throw std::invalid_argument("Name can't be nothing");

	try
	{
		this->nickname = new char[strlen(nickname) + 1];
		strcpy(this->nickname, nickname);	
		postMadeID = new unsigned int[maxSize];
	}
	catch (const std::bad_alloc& ba)
	{
		delete[] nickname;
		throw;
	}
}

User::User(const User &other):nickname(nullptr),age(other.age),blocked(false),currSize(other.currSize),maxSize(other.maxSize),postMadeID(nullptr)
{
	try
	{
		this->nickname = new char[strlen(other.nickname) + 1];
		strcpy(this->nickname, other.nickname);

		postMadeID = new unsigned[maxSize];
		for (int count = 0; count < currSize; ++count)
			postMadeID[count] = other.postMadeID[count];
	}
	catch (const std::bad_alloc& ba)
	{
		delete[] nickname;
		delete[] postMadeID;
		throw;
	}
}

User & User::operator=(const User &other)
{
	if (this != &other)
	{
		delete[] nickname;
		delete[] postMadeID;
		try
		{
			this->nickname = new char[strlen(nickname) + 1];
			strcpy(this->nickname, nickname);
			age = other.age;

			postMadeID = new unsigned[maxSize];
			for (int count = 0; count < currSize; ++count)
				postMadeID[count] = other.postMadeID[count];

			blocked = false;
		}
		catch (const std::bad_alloc& ba)
		{
			delete[] nickname;
			delete[] postMadeID;
			throw;
		}

	}
	return *this;
}

User::~User()
{
	delete[] nickname;
	delete[] postMadeID;
}

bool User::checkNickname(const char *nickname) const
{
	if (strcmp(nickname, this->nickname) == 0)
		return true;
	return false;
}

void User::addPublication(const int& postID)
{	
	if (currSize == maxSize)
		resizePostsMade();

	postMadeID[currSize++] = postID;
}

void User::changeNickname(const char *toChange)
{
	delete[] nickname;

	nickname = new char[strlen(toChange) + 1];
	strcpy(nickname, toChange);
}

bool User::hasCreatedPosts() const
{
	if(currSize==0)
		return false;
	return true;
}

bool User::validatePost(const int &toFind) const
{
	for (int count = 0; count < currSize; ++count)
		if (postMadeID[count] == toFind)
			return true;

	return false;
}

bool User::isBlocked() const
{
	return blocked;
}

void User::removePost(const int &toRemove)
{
	for (int count = toRemove; count < maxSize - 1; ++count)
	{
		unsigned int temp = postMadeID[count];
		postMadeID[count] = postMadeID[count + 1];
		postMadeID[count + 1] = temp;
	}
}

 void User::setBlock()
{
	if (blocked == true)
		throw(std::logic_error("User already blocked"));
	blocked = true;
}

 void User::setUnblock()
{
	if (blocked == false)
		throw(std::logic_error("User already unblocked"));
	blocked = false;
}

 const char * User::getName() const
{
	return nickname;
}

 int User::getAge() const
{
	return age;
}


 void User::resizePostsMade()
 {
	 unsigned* temp = new unsigned[maxSize];
	 for (int count = 0; count < currSize; ++count)
		 temp[count] = postMadeID[count];

	 delete[] postMadeID;
	 maxSize *= 2;
	 postMadeID = new unsigned[maxSize];
	 for (int count = 0; count < currSize; ++count)
		 postMadeID[count] = temp[count];
	 delete[] temp;
 }
