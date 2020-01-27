#include "Hashtag.h"

#include <iostream>

Hashtag::Hashtag(const char *word):Word(word)
{
}

char Hashtag::getType() const
{
	return 'h';
}

double Hashtag::compare(const Word &toCompare) const
{
	if (strlen(word) != strlen(toCompare.getWord()))
		return 0;

	for (int count = 0; count < strlen(word); ++count)
	{
		if (word[count] != toCompare.getWord()[count])
		{
			if (word[count] >= 'a' && word[count] <= 'z')
			{
				if (toHigher(word[count]) != toCompare.getWord()[count])
					return 0;
			}
			else if (word[count] >= 'A' && word[count] <= 'Z')
			{
				if (toLower(word[count]) != toCompare.getWord()[count])
					return 0;
			}
			else
				return 0;		
		}
	}
	return 100;
}

Word * Hashtag::clone() const
{
	return new Hashtag(*this);
}
