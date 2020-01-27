#ifndef DATE_H
#define DATE_H

#include "Word.h"

class Date :public Word
{
public:
	Date(const char*);

	char getType() const ;
	double compare(const Word&) const;
	Word* clone() const;
};
#endif // !DATE_H
