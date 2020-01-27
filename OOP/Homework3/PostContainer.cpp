#include "PostContainer.h"

#include <iostream>

PostContainer::PostContainer():currSize(0),maxSize(10),posts(nullptr)
{
	posts = new Publication*[maxSize];
}

PostContainer::~PostContainer()
{
	clean(currSize);
}

void PostContainer::newPost(const char *content, const char *linkDescription, const char &type) //If a isn't link beeing created 
{													//its value is set to nullptr
	if (currSize == maxSize)
		resize();

	switch (type)
	{
	case 'i':
		posts[currSize++] = new Image(content);
		break;
	case 'l':
		posts[currSize++] = new Link(content, linkDescription);
		break;
	case 't':
		posts[currSize++] = new Text(content);
		break;
	}
	std::cout << "Post " << posts[currSize - 1]->getId() << " created" << std::endl;
}

void PostContainer::removePost(const int &toRemove)
{
	sort(toRemove);
	std::cout << "Post " << toRemove << " removed"<<std::endl;
}

void PostContainer::saveToHTML(const int &postID,std::ostream& output) const
{
	posts[postID]->saveToHTML(output); 
}

bool PostContainer::postExists(const int &toFind) const
{
	for (int count = 0; count < currSize; ++count)
		if (posts[count]->getId() == toFind)
			return true;

	return false;
}

int PostContainer::getLastMade() const
{
	return posts[currSize-1]->getId();
}

int PostContainer::getCurrentSize() const
{
	return currSize;
}

void PostContainer::resize() //Increasing post array so that there could be more pointers to Post 
{
	Publication** temp = new Publication*[maxSize * 2];
	for (int count = 0; count < currSize; count++)
		temp[count] = posts[count];

	delete[] posts;
	posts = temp;
}

void PostContainer::sort(const int &toRemove) //Puts a given pointer to Post in last position
{
	for (int count = toRemove; count < maxSize - 1; count++)
	{
		Publication* temp = posts[count];
		posts[count] = posts[count + 1];
		posts[count + 1] = temp;
	}
	delete posts[maxSize - 1];
	currSize -= 1;

}

void PostContainer::clean(const int &num) //Frees memory of all posts
{
	for (int count = 0; count < num; count++)
	{
		delete posts[count];
	}
	delete[] posts;

	posts = nullptr;
	currSize = 0;
	maxSize = 0;
}