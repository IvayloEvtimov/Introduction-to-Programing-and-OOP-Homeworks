#ifndef TRANSFORMATION_H_INCLUDED
#define TRANSFORMATION_H_INCLUDED

#include "CharArray.h"

class Transformation
{
public:
	Transformation(const char*); 

	void makeHeading(const int&); //Add Heading
	void makeItalic(const int&, const int&, const int&); //Makes the selected words italic
	void makeBold(const int&, const int&, const int&); //Makes the selected words bold
	void makeCombine(const int&, const int&, const int&); //Makes the selected words italic and bold
	void addLine(const char*); 
	void removeLine(const int&);
	void exit();
private:
	void findStr(const int&, const int&, const char*, int*); //Finds the first pos of the first words and the last pos of the second word
	void charHeadingV3(const int&); 
	void transformV4(const int&, const int&, const int&, char&); //Used for making the selected part of the text italic,bold or both
	bool checkAsterix(const char*, const int*, char&);
private:
	CharArray file;
};

#endif // !TRANSFORMATION_H_INCLUDED
