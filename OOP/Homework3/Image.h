#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Publication.h"

class Image : public Publication
{
public:
	Image (const char*);

	virtual void saveToHTML(std::ostream&) const;

	virtual Publication* clone() const;

private:

};

#endif // !IMAGE_H_INCLUDED
