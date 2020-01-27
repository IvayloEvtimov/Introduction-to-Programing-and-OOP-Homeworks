#include "CharArray.h"
#include "Constants.h"

#include <iostream>
#include <fstream>

CharArray::CharArray(const char *str)
{
	this->path = new char[strlen(str) + 1];
	strcpy(this->path, str);

	loadFromFile(); 
	fillStr();
}

CharArray::CharArray(const CharArray &other)
{
	path = new char[strlen(other.path) + 1];
	strcpy(path, other.path);
	this->textArr = new char*[line];

	line = other.line;

	for (int count = 0; count < line; count++)
	{
		this->textArr[count] = new char[strlen(other.textArr[count]) + 1];
		strcpy(this->textArr[count], other.textArr[count]);
	}
}

CharArray & CharArray::operator=(const CharArray &other)
{
	if (this != &other)
	{
		delete[] path;
		path = new char[strlen(other.path) + 1];
		strcpy(path, other.path);
		line = other.line;
		clean();
		this->textArr = new char*[line];
		for (int count = 0; count < line; count++)
		{
			this->textArr[count] = new char[strlen(other.textArr[count]) + 1];
			strcpy(this->textArr[count], other.textArr[count]);
		}
	}
	return *this;
}

CharArray::~CharArray()
{
	delete[] path;
	clean();
}


void CharArray::loadFromFile()
{
	std::ifstream input(this->path);

	char buffer[MAX];

	while (!input.eof())
	{
		input.getline(buffer, MAX,'\n');
		this->line++;
	}

	input.close();
}

int CharArray::getLine() const
{
	return line;
}

const char* CharArray::getPath() const
{
	return path;
}

const char * CharArray::getText(const int& lineToFind) 
{
	return textArr[lineToFind];
}

void CharArray::addLine(const char* content)
{
	char** temp = new char*[this->line];
	for (int count = 0; count < this->line; count++)
	{
		temp[count] = new char[strlen(this->textArr[count]) + 1];
		strcpy(temp[count], this->textArr[count]);
	}

	clean();
	this->line += 1;
	this->textArr = new char*[this->line];
	for (int countCopy = 0; countCopy < this->line - 1; countCopy++)
	{
		this->textArr[countCopy] = new char[strlen(temp[countCopy]) + 1];
		strcpy(this->textArr[countCopy], temp[countCopy]);
	}

	this->textArr[this->line - 1] = new char[strlen(content) + 1];
	strcpy(this->textArr[this->line - 1], content);
	delete[] temp;
}

void CharArray::removeLine(const int &lineToRemove)
{
	char** temp = new char*[this->line - 1];
	for (int count = 0; count < this->line; count++)
	{
		if (count != lineToRemove )
		{
			temp[count] = new char[strlen(this->textArr[count]) + 1];
			strcpy(temp[count], this->textArr[count]);
		}
	}

	clean();
	this->textArr = temp;

	this->line -= 1;
}

void CharArray::modifyLine(const int &lineToRemove,const char* content)
{
	delete[] textArr[lineToRemove];
	textArr[lineToRemove] = new char[strlen(content) + 1];
	strcpy(textArr[lineToRemove], content);
}


bool CharArray::checkLine(const int &lineToFind) const
{
	if (lineToFind <= this->line)
		return true;
	return false;
}


void CharArray::fillStr()
{
	char buffer[MAX];
	std::ifstream input(path);
	this->textArr = new char*[this->line];
	
	int countPos = 0;

	for (int count = 0; count < line; count++)
	{
		countPos = 0;
		while(true)
		{
			input.get(buffer[countPos]);
			if (buffer[countPos] == '\n' || buffer[countPos]==0)
			{
				buffer[countPos] = 0;
				break;
			}
			countPos++;
		}
		this->textArr[count] = new char[countPos + 1];
		strcpy(this->textArr[count], buffer);
	}
	input.close();
}

void CharArray::clean()
{
	for (int count = line - 1; count > 0; count--)
		delete[] this->textArr[count];

	delete[] this->textArr;
}