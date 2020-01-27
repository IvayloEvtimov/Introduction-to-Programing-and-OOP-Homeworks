#ifndef POSTCONTAINER_H_INCLUDED
#define POSTCONTAINER_H_INCLUDED

#include "Text.h"
#include "Link.h"
#include "Image.h"

#include "Helper.h"

class PostContainer
{
public:
	PostContainer();
	PostContainer(const PostContainer&) = delete;
	PostContainer* operator+(const PostContainer&) = delete;
	~PostContainer();

	void newPost(const char*, const char*, const char& ); //Adds new Publication to the posts array
	void removePost(const int&); //Removes a post
	void saveToHTML(const int&,std::ostream&) const; //Saves the content on a post in html file

	bool postExists(const int&) const; //Checks if a post with such ID exists
	int getLastMade() const; //Returns the last made post ID
	int getCurrentSize() const; //Returns the current size
private:
	void resize();
	void sort(const int&);
	void clean(const int&);
private:
	unsigned int currSize;
	unsigned int maxSize;
	Publication ** posts;
};


#endif // !POSTCONTAINER_H_INCLUDED
