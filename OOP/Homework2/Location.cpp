#include "Location.h"
#include "Constants.h"

#include <iostream>
#include <fstream>


Location::Location()
{
	this->path = new char[8];
	strcpy(this->path, "Invalid");
	this->line = 0;
}

Location::Location(const char* path)
{
	this->path = new char[strlen(path) + 1];
	strcpy(this->path, path);
	loadFromFile();
}

Location::Location(const Location &other)
{
	path = new char[strlen(other.path) + 1];
	strcpy(path, other.path);
	line = other.line;
}

Location & Location::operator=(const Location &other)
{
	if (this != &other)
	{
		delete[] path;
		path = new char[strlen(other.path) + 1];
		strcpy(path, other.path);
		line = other.line;
	}
	return *this;
}

Location::~Location()
{
	delete[] path;
}

const char * Location::getPath()
{
	return path;
}

int Location::getLine() const
{
	return line;
}

void Location::loadFromFile()
{
	std::ifstream input(this->path);

	char buffer[MAX];

	while (!input.eof())
	{
		input.getline(buffer, MAX);
		this->line++;
	}

	input.close();
}