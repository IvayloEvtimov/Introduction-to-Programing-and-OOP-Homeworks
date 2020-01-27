#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED

#include "Publication.h"

class Link : public Publication
{
public:
	Link(const char*,const char*);
	Link(const Link&);
	Link& operator=(const Link&);
	~Link();

	virtual void saveToHTML(std::ostream&) const;

	virtual Publication* clone() const;
private:
	char* description;
};

#endif // !LINK_H_INCLUDED
