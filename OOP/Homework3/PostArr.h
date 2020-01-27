#ifndef POSTARR_H_INCLUDED
#define POSTARR_H_INCLUDED

#include "PostContainer.h"

class PostArr
{
public:
	PostArr();
	PostArr(const PostArr&)=delete;
	PostArr& operator=(const PostArr&) = delete;
	~PostArr();

	void newElem(const char*, const char*, const char*);

private:
	int size;
	int maxSize;
	PostContainer** post;
};


#endif // !POSTARR_H_INCLUDED
