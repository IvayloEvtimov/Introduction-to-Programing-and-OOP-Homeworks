#include "PostArr.h"

PostArr::PostArr():size(0),maxSize(2),post(nullptr)
{
	post = new PostContainer*[maxSize];
}

PostArr::~PostArr()
{
	for (int count = 0; count < size; ++count)
		delete post[count];
	delete[] post;
}


