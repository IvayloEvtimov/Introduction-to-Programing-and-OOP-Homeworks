#include <iostream>
#include "Publication.h"

unsigned int Publication::unique = 0;

Publication::Publication(const char* content):content(nullptr),id(unique++)
{
	try
	{
		if(content==nullptr)
		{
			this->content=new char[1];
			this->content='\0';
		}else
		{
			this->content = new char[strlen(content) + 1];
			strcpy(this->content, content);
		}
	}
	catch (const std::bad_alloc &ba)
	{
		delete[] content;
		throw;
	}
}

Publication::Publication(const Publication &other):content(nullptr),id(other.id)
{
	try
	{
		this->content = new char[strlen(other.content) + 1];
		strcpy(this->content, other.content);
	}
	catch (const std::bad_alloc& ba)
	{
		delete[] content;
		throw;
	}
}

Publication & Publication::operator=(const Publication &other)
{
	if (this != &other)
	{
		delete[] content;
		try
		{
			this->content = new char[strlen(other.content) + 1];
			strcpy(this->content, other.content);
		}
		catch (const std::bad_alloc& ba)
		{
			delete[] content;
			throw;
		}
		id = other.id;
	}
	return *this;
}

Publication::~Publication()
{
	delete[] content;
}

unsigned int Publication::getId() const
{
	return id;
}
