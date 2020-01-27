#include "Date.h"

#include <iostream>

Date::Date(const char *word):Word(word)
{
}

char Date::getType() const
{
	return 'd';
}

double Date::compare(const Word &toCompare) const
{
	if (toCompare.getType() != 'd')
		return 0;

	if (strcmp(word, toCompare.getWord()) == 0)
		return 100;

	int thisDate[3];
	int toCompareDate[3];

	thisDate[0] = (word[0] - '0')*10 + (word[1]-'0');
	thisDate[1] = (word[3] - '0') * 10 + (word[4] - '0');
	thisDate[2] = (word[6] - '0') * 1000 + (word[7] - '0') * 100 + (word[8] - '0') * 10 + (word[9] - '0');

	toCompareDate[0] = (toCompare.getWord()[0] - '0') * 10 + (toCompare.getWord()[1] - '0');
	toCompareDate[1] = (toCompare.getWord()[3] - '0') * 10 + (toCompare.getWord()[4] - '0');
	toCompareDate[2] = (toCompare.getWord()[6] - '0') * 1000 + (toCompare.getWord()[7] - '0') * 100 + (toCompare.getWord()[8] - '0') * 10 + (toCompare.getWord()[9] - '0');

	int dayDiff = thisDate[0] - toCompareDate[0],
		monthDiff = thisDate[1] - toCompareDate[1],
		yearDiff = thisDate[2] - toCompareDate[2];

	return 100;
}

Word* Date::clone() const
{
	return new Date(*this);
}
