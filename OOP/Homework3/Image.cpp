#include<iostream>

#include "Image.h"

Image::Image(const char *content) :Publication(content)
{

}

void Image::saveToHTML(std::ostream &output) const
{
	output << "<img src=" << '\"' << content << '\"'<<'>' << std::endl;
}

Publication* Image::clone()const
{
	return new Image(*this);
}
