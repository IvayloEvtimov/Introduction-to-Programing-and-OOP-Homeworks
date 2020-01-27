#include "Text.h"

Text::Text(const char *content):Publication(content)
{

}

void Text::saveToHTML(std::ostream &output) const
{
	output <<"<p>" <<content<<"</p>"<<std::endl;
}

Publication * Text::clone()const
{
	return new Text(*this);
}
