#include "Word.h"
#include "Constant.h"

#include <iostream>

Word::Word(const char *word)
{
	copy(word);
}

Word::Word(const Word &other)
{
	copy(other.word);
}

Word & Word::operator=(const Word &other)
{
	if (this != &other)
	{
		delete[] word;
		copy(other.word);
	}
	return *this;
	// TODO: insert return statement here
}

Word::~Word()
{
	delete[] word;
}

const char * Word::getWord() const
{
	return word;
}

char Word::toLower(const char &letter) const
{
	return letter+charDifference;
}

char Word::toHigher(const char &letter) const
{
	return letter-charDifference;
}

void Word::copy(const char* word)
{
	if (word == nullptr)
	{
		this->word = new char[1];
		this->word[0] = 0;
	}
	else
	{
		this->word = new char[strlen(word) + 1];
		strcpy_s(this->word, strlen(word)+1, word);
	}
}
