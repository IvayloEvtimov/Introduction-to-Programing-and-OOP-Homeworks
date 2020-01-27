#include "WordContainer.h"

#include <iostream>

WordContainer::WordContainer():size(0),maxSize(10),words(nullptr)
{
	words = new Word*[maxSize];
}

WordContainer::WordContainer(const WordContainer &other):size(other.size),maxSize(other.maxSize),words(nullptr)
{
	words = new Word*[maxSize];
	//copy(other.words);
	int count;
	try
	{
		for (int count = 0; count < size; ++count)
			words[count] = other.words[count]->clone();
	}
	catch (std::bad_alloc)
	{
		clean(count);
		throw;
	}
}

WordContainer & WordContainer::operator=(const WordContainer &other)
{
	if (this != &other)
	{
		clean(size);
		size = other.size;
		maxSize = other.maxSize;
		words = new Word*[maxSize];
		//copy(other.words);
		int count;
		try
		{
			for (int count = 0; count < size; ++count)
				words[count] = other.words[count]->clone();
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

WordContainer::~WordContainer()
{
	clean(size);
}

void WordContainer::newWord(const Word &toAdd)
{
	if (size == maxSize)
		resize();

	words[size++] = toAdd.clone();
}

double WordContainer::compare(const Word &toCompare) const
{
	double sum = 0;
	for (int count = 0; count < size; ++count)
	{
		sum += words[count]->compare(toCompare);
	}
	return sum/size;
}

void WordContainer::printHash() const
{
	for (int count = 0; count < size; ++count)
	{
		if (words[count]->getType() == 'h')
			std::cout << words[count]->getWord() << std::endl;
	}
}

void WordContainer::copy(const Word** other)
{
	int count;
	try
	{
		for (int count = 0; count < size; ++count)
			words[count] = other[count]->clone();
	}
	catch (std::bad_alloc)
	{
		clean(count);
		throw;
	}
}

void WordContainer::clean(const int &toClean)
{
	for (int count = 0; count < toClean; ++count)
		delete words[count];
	delete[] words;
	size = 0;
	maxSize = 0;
	words = nullptr;
}

void WordContainer::resize()
{
	Word** temp = new Word*[maxSize * 2];
	for (int count = 0; count < size; ++count)
		temp[count] = words[count];
	delete[] words;
	words = temp;
}
