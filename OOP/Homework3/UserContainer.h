#ifndef USERCONTAINER_H_INCLUDED
#define USERCONTAINER_H_INCLUDED

#include "Admin.h"
#include "Moderator.h"
#include "Regular.h"

#include "Stats.h"

class UserContainer
{
public:
	UserContainer(const Admin&);
	UserContainer(const UserContainer&) = delete;
	UserContainer& operator=(const UserContainer&) = delete;
	~UserContainer();

	void newUser(const char*, const unsigned&, const char&,Stats&); //Adds new user to the array
	void removeUser(const unsigned&); //Removes a user from the array
	void blockUser(const unsigned&,Stats&); //Sets the block flag to the user and puts him in a list of blocked users
	void unblockUser(const unsigned&); //Sets the block flag to false

	void newPostMade(const unsigned&,const unsigned&); //Adds the post ID to an array of post IDs made by this user
	void removePostMade(const unsigned&, const unsigned&); //Removes the post ID from an array of post IDs made by this user
	bool hasCreatedPosts(const unsigned&) const; //Return wheather the user has created any post so far
	bool validatePost(const unsigned&,const unsigned&) const; //Checks if the postID is made by thsi user


	bool isAdmin(const char*) const; //Returns if wheather the user is an admin
	bool hasRights(const unsigned&) const; //Returns if wheather the users is moderator or higher
	bool isBlocked(const unsigned&) const; //Returns if wheather the user is blocked or not
	int userExists(const char*) const; //Checks if by name if such user exists

	bool nameTaken(const char*) const; //Checks if the name is taken
	void changeNickname(const unsigned&, const char*); //Changes a users name

	void print() const; //Prints information about the users
private:
	void resize(); //Increases the size of the array
	void sort(const unsigned&); //Sorts the array by putting the selected user at the end of the array
	void clean(const unsigned&);

private:
	unsigned int currSize;
	unsigned int maxSize;
	User** users;
};

#endif // !USERCONTAINER_H_INCLUDED
