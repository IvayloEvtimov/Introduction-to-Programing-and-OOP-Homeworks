#include "Simple.h"

#include <iostream>

Simple::Simple(const char *word):Word(word)
{
}

char Simple::getType() const
{
	return 's';
}

double Simple::compare(const Word &toCompare) const
{
	double wordsMatch = 0;

	int length = 0;
	if (strlen(word) > strlen(toCompare.getWord()))
		length = strlen(toCompare.getWord());
	else
		length = strlen(word);

	for (int count = 0; count < length; ++count)
	{
		if (word[count] == toCompare.getWord()[count])
			wordsMatch += 1;
		else
		{
			if (word[count] >= 'a' && word[count] <= 'z')
			{
				if (toHigher(word[count]) == toCompare.getWord()[count])
					wordsMatch += 1;
			}
			else if (word[count] >= 'A' && word[count] <= 'Z')
			{
				if (toLower(word[count]) == toCompare.getWord()[count])
					wordsMatch += 1;
			}
		}
	}

	double res = (double)(wordsMatch / length);
	return res*100;
}

Word * Simple::clone() const
{
	return new Simple(*this);
}
