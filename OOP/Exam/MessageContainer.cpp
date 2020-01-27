#include "MessageContainer.h"

#include <iostream>

MessageContainer::MessageContainer():size(0),maxSize(10),messages(nullptr)
{
	messages = new Message*[maxSize];
}

MessageContainer::MessageContainer(const MessageContainer &other):size(other.size), maxSize(other.maxSize), messages(nullptr)
{
	messages = new Message*[maxSize];
	//copy(other.messages);
	int count;
	try
	{
		for (int count = 0; count < size; ++count)
			messages[count] = other.messages[count]->clone();
	}
	catch (std::bad_alloc)
	{
		clean(count);
		throw;
	}
}

MessageContainer & MessageContainer::operator=(const MessageContainer &other)
{
	if (this != &other)
	{
		clean(size);
		size = other.size;
		maxSize = other.maxSize;
		messages = new Message*[maxSize];
		//copy(other.messages);
		int count;
		try
		{
			for (int count = 0; count < size; ++count)
				messages[count] = other.messages[count]->clone();
		}
		catch (std::bad_alloc)
		{
			clean(count);
			throw;
		}
	}
	return *this;
	// TODO: insert return statement here
}

MessageContainer::~MessageContainer()
{
	clean(size);
}

void MessageContainer::newMessage(const char *text)
{
	if (text == nullptr)
		throw std::invalid_argument("Message can't be empty");

	messages[size++] = new Message(text);
}

void MessageContainer::printHash() const
{
	for (int count = 0; count < size; ++count)
		messages[count]->printHash();
}

Message MessageContainer::compare(const char *toCompare) const
{
	double tempScore = 0,
		bestScore = 0;

	int	bestPos = 0;

	for (int count = 0; count < size; ++count)
	{
		tempScore = messages[count]->compare(toCompare);
		if (tempScore > bestScore)
		{
			bestScore = tempScore;
			bestPos = count;
		}
	}

	return Message(*messages[bestPos]);
}

void MessageContainer::copy(const Message **other)
{
	int count;
	try
	{
		for (int count = 0; count < size; ++count)
			messages[count] = other[count]->clone();
	}
	catch (std::bad_alloc)
	{
		clean(count);
		throw;
	}
}

void MessageContainer::clean(const int& toClean)
{
	for (int count = 0; count < toClean; ++count)
		delete messages[count];
	delete[] messages;
	size = 0;
	maxSize = 0;
	messages = nullptr;
}

void MessageContainer::resize()
{
	Message** temp = new Message*[maxSize * 2];
	for (int count = 0; count < size; ++count)
		temp[count] = messages[count];
	delete[] messages;
	messages = temp;
}
