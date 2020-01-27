#ifndef SIMPLE_H
#define SIMPLE_H

#include "Word.h"

class Simple : public Word
{
public:
	Simple(const char*);

	char getType() const;
	double compare(const Word&) const;
	Word* clone() const;
};

#endif // !SIMPLE_H
