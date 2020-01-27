#include <iostream>
#include"System.h"

int main()
{
	System S1;

	S1.load("file.txt");
	S1.printHash();
	std::cout << "Message closest to fmiLife is: " << std::endl;
	std::cout<<S1["fmiLife"]<<std::endl;

	system("pause");
	return 0;
}