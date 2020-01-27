#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Publication.h"

class Text :public Publication
{
public:
	Text(const char*);

	virtual void saveToHTML(std::ostream&) const;

	virtual Publication* clone() const;

private:
};

#endif // !TEXT_H_INCLUDED
