#include "Message.h"
#include "Constant.h"

#include <iostream>

Message::Message(const char *wholeMessage):wholeMessage(nullptr),words()
{
	if (wholeMessage == nullptr)
		throw std::invalid_argument("The message can't be empty");

	this->wholeMessage = new char[strlen(wholeMessage) + 1];
	strcpy_s(this->wholeMessage, strlen(wholeMessage)+1, wholeMessage);

	addWords();
}

Message::Message(const Message &other):wholeMessage(nullptr),words(other.words)
{
	this->wholeMessage = new char[strlen(other.wholeMessage) + 1];
	strcpy_s(this->wholeMessage, strlen(other.wholeMessage)+1, other.wholeMessage);
}

Message & Message::operator=(const Message &other)
{
	if (this != &other)
	{
		delete[] wholeMessage;

		this->wholeMessage = new char[strlen(other.wholeMessage) + 1];
		strcpy_s(this->wholeMessage, strlen(other.wholeMessage)+1, other.wholeMessage);
		
		words = other.words;
	}
	return *this;
	// TODO: insert return statement here
}

Message::~Message()
{
	delete[] wholeMessage;
}

void Message::printHash() const
{
	words.printHash();
}

double Message::compare(const char *toCompare) const
{
	char type = findType(toCompare);
	if (type == 'h')
	{
		Hashtag temp(toCompare);
		return words.compare(temp);
	}

	if (type == 'd')
	{
		Date temp(toCompare);
		return words.compare(temp);
	}

	if (type == 's')
	{
		Simple temp(toCompare);
		return words.compare(temp);
	}
	return 0;
}

Message * Message::clone() const
{
	return new Message(*this);
}

void Message::addWords()
{
	int countMessage = 0;

	while (true)
	{
		if (wholeMessage[countMessage - 1] == 0 || wholeMessage[countMessage - 1] == '\n')
			break;

		char buffer[MAX_SIZE];

		getCharUntil(countMessage, buffer);
		char type = findType(buffer);

		if (type == 's')
		{
			Simple temp(buffer);
			words.newWord(temp);
		}else if (type == 'h')
		{
			Hashtag temp(buffer);
			words.newWord(temp);
		}else if (type == 'd')
		{
			Date temp(buffer);
			words.newWord(temp);
		}

	}
}

void Message::getCharUntil(int &countMessage, char *buffer) const
{
	char ch = 0;
	while (true)
	{
		ch = wholeMessage[countMessage++];
		if (validChar(ch))
			break;
	}

	char temp[MAX_SIZE];
	int countTemp = 0;

	temp[countTemp++] = ch;

	while (true)
	{
		temp[countTemp++] = wholeMessage[countMessage++];
		if (!validChar(temp[countTemp - 1]))
			break;
	}
	temp[countTemp-1] = 0;
	strcpy_s(buffer, MAX_SIZE, temp);
}

bool Message::validChar(const char &toValidate) const
{
	if (toValidate >= 'a' && toValidate <= 'z')
		return true;
	if (toValidate >= 'A' && toValidate <= 'Z')
		return true;
	if (toValidate >= '0' && toValidate <= '9')
		return true;
	if (toValidate == '#' || toValidate == '-')
		return true;
	return false;
}

char Message::findType(const char *buffer) const
{
	if (buffer[0] == '#')
		return 'h';

	int linesMet = 0;
	int numsMet = 0;

	int countBuffer = 1;

	while (true)
	{
		if (buffer[countBuffer] == '-')
		{
			if (numsMet != 2)
				return 's';

			numsMet = 0;
			linesMet += 1;
		}

		if (buffer[countBuffer] >= '0' && buffer[countBuffer] <= '9')
			numsMet += 1;
		else
			return 's';

		if (buffer[countBuffer] == 0)
		{
			if (linesMet != 2 && numsMet != 4)
				return 's';
			else
				return 'd';
		}
		countBuffer += 1;
	}
}

std::ostream& operator<<(std::ostream &output, const Message &msg)
{
	output << msg.wholeMessage << std::endl;
	return output;
}
