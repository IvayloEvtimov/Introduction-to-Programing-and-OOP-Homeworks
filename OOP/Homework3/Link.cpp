#include <iostream>
#include "Link.h"

Link::Link(const char *content,const char* description):Publication(content),description(nullptr)
{
	try
	{
		if(description==nullptr)
		{
			this->description=new char[1];
			this->description='\0';
		}else
		{
			this->description = new char[strlen(description) + 1];
			strcpy(this->description, description);
		}
	}
	catch (const std::bad_alloc &ba)
	{
		delete[] content;
		delete[] description;
		throw;
	}
}

Link::Link(const Link &other):Publication(other),description(nullptr)
{
	try
	{
	this->description = new char[strlen(other.description) + 1];
	strcpy(this->description, other.description);
	}
	catch (const std::bad_alloc &ba)
	{
		delete[] content;
		delete[] description;
		throw;
	}
}

Link & Link::operator=(const Link &other)
{
	if (this != &other)
	{
		Publication::operator=(other);
		delete[] description;
		try
		{
			this->description = new char[strlen(other.description) + 1];
			strcpy(this->description, other.description);
		}
		catch (const std::bad_alloc &ba)
		{
			delete[] content;
			delete[] description;
			throw;
		}

	}
	return *this;
}

Link::~Link()
{
	delete[] description;
}

void Link::saveToHTML(std::ostream &output) const
{
	output << "<a href = " << '\"' << content << '\"';
	output << '>' << description << "</a>"<<std::endl;
}

Publication * Link::clone ()const
{
	return new Link(*this);
}
