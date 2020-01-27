#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <fstream>

#include "Publication.h"

class User
{
public:
	User(const char*, const int&);
	User(const User&);
	User& operator=(const User&);
	virtual ~User();

	bool checkNickname(const char*) const;

	void addPublication(const int&);
	void changeNickname(const char*);

	bool hasCreatedPosts() const;
	bool validatePost(const int&) const;
	void removePost(const int&);

	bool isBlocked() const;

	virtual bool isMod() const = 0;
	virtual bool isAdmin() const = 0;

	virtual void print() const = 0;

	void setBlock();
	void setUnblock();

	const char* getName() const;
	int getAge() const;

	virtual User* clone()const = 0;

private:
	void resizePostsMade();
protected:
	char* nickname;
	int age;
	//unsigned int postMade;
	unsigned int currSize;
	unsigned int maxSize;
	unsigned int* postMadeID;
	bool blocked;
};

#endif // !USER_H_INCLUDED
