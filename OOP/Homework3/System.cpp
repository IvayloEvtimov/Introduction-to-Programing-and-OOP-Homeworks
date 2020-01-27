#include "System.h"

#include<iostream>

System::System(const Admin &admin):users(admin),posts(),stats(admin)
{

}

void System::newUser(const char *actor, const char *nickname, const int &age, const char &type)
{
	if (!users.isAdmin(actor))
		throw std::invalid_argument("Only admin can add new Users");

	if (users.nameTaken(nickname))
		throw std::invalid_argument("Name is already taken");

	users.newUser(nickname, age, type,stats);

	std::cout << nickname << " is created" << std::endl;
}

void System::removeUser(const char *actor, const char *toRemove)
{
	if (!users.isAdmin(actor))
		throw std::invalid_argument("Only admin can remove Users");

	if (strcmp(actor,toRemove) == 0) //After checking if actor is the admin, check if toRemove isn't the same as actor
		throw std::invalid_argument("The admin can't remove himself");

	int toRemovePos = users.userExists(toRemove);

	for (unsigned count = 0; count < posts.getCurrentSize(); ++count)
		if (users.validatePost(toRemovePos, count))
			posts.removePost(count);

	users.removeUser(toRemovePos);
	stats.newUnblocked(toRemove); //Removes it from the list of blocked user because the user is deleted from the System
	std::cout << toRemove << " is removed" << std::endl;
}

void System::blockUser(const char *actor, const char *toBlock)
{
	int actorPos = users.userExists(actor);
	if (!users.hasRights(actorPos))
		throw std::invalid_argument("Only mods or higher can block Users");

	int toBlockPos = users.userExists(toBlock);

	users.blockUser(toBlockPos,stats);
	std::cout << toBlock << " is blocked" << std::endl;
}

void System::unblockUser(const char *actor, const char *toUnblock)
{
	int actorPos = users.userExists(actor);
	if (!users.hasRights(actorPos))
		throw std::invalid_argument("Only mods or higher can block Users");

	int toUnblockPos = users.userExists(toUnblock);

	users.unblockUser(toUnblockPos);
	stats.newUnblocked(toUnblock);
	std::cout << toUnblock << " is unblocked" << std::endl;
}

void System::newPost(const char *actor, const char *content, const char *linkDescription, const char &type)
{
	int actorPos = users.userExists(actor);
	if (users.isBlocked(actorPos)) //Quick check is the user if blocked or not
		throw std::invalid_argument("Action can't be completed. User is blocked");

	posts.newPost(content, linkDescription, type);
	users.newPostMade(actorPos, posts.getLastMade());
}

void System::removePost(const char *actor, const int &postID)
{
	int actorPos = users.userExists(actor);
	if (users.isBlocked(actorPos))
		throw std::invalid_argument("Action can't be completed. User is blocked");

	if (!posts.postExists(postID))
		throw std::invalid_argument("There is no post with such ID");

	posts.removePost(postID);
	users.removePostMade(actorPos, postID);
}

void System::viewPost(const char *nickname, const int &postID) const
{
	int actorPos = users.userExists(nickname);

	if (!posts.postExists(postID))
		throw std::invalid_argument("There is no post with such ID");

	char* filename = new char[strlen("Post ") + strlen(".html") + numOfInts(postID) + 1];
	strcpy(filename, "Post ");

	if (postID < 10) //If postID is less then 10 there is no need for conversion
	{
		filename[5] = postID + '0';
		filename[6] = 0;
	}
	else
		intToStr(filename, postID);

	strcat(filename, ".html");

	std::ofstream output(filename);
	if (!output.is_open())
		throw std::logic_error("File could not be opened");

	output << "<!DOCTYPE html>" << std::endl;
	output << "<html>" << std::endl;
	output << "<head></head>" << std::endl;
	output << "<body>" << std::endl;

	posts.saveToHTML(postID,output); //Generates a HTML page for this post only

	std::cout << "HTML view for post " << postID << " is created" << std::endl;

	output << "</body>" << std::endl;
	output << "</html>" << std::endl;

	if (!output.good())
		throw std::logic_error("Error when saving file");

	output.close();
	delete[] filename;
}

void System::viewAll(const char *actor, const char *postCreator) const
{
	int actorPos = users.userExists(actor);

	int postCreatorPos = users.userExists(postCreator);
	if (!users.hasCreatedPosts(postCreatorPos))
		throw std::invalid_argument("User hasn't created any posts");

	char* filename = new char[strlen(postCreator) + strlen("'s posts.html") + 1];
	strcpy(filename, postCreator);
	strcat(filename, "'s posts.html");
	
	//Generates HTML page for all the posts made by the user

	std::ofstream output(filename);
	if (!output.is_open())
		throw std::logic_error("File could not be opened");

	output << "<!DOCTYPE html>" << std::endl;
	output << "<html>" << std::endl;
	output << "<head></head>" << std::endl;
	output << "<body>" << std::endl;

	for (int count = 0; count < posts.getCurrentSize(); ++count)
		if (users.validatePost(postCreatorPos, count))
			posts.saveToHTML(count, output);

	output << "</body>" << std::endl;
	output << "</html>" << std::endl;

	if (!output.good())
		throw std::logic_error("Error when saving file");

	output.close();

	std::cout << "HTML view for all of " << postCreator << "'s post are created.\n";
	delete[] filename;
}

void System::changeNickname(const char *actor, const char *newName)
{
	int actorPos = users.userExists(actor);
	if (users.nameTaken(newName))
		throw std::invalid_argument("Name is already taken");

	users.changeNickname(actorPos, newName);
	if(users.isBlocked(actorPos))
		stats.changeName(actor, newName); //Updates the name in the blocked list
	std::cout << actor << " is now known as " << newName << std::endl;
}

void System::statistic() const
{
	users.print();
	std::cout << std::endl;
	stats.print();
}
