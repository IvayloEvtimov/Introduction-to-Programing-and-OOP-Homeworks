/////////////////////////////
//Author: Ivalylo Evtimov  
//FN: 45252				   
//Group: 5				   
//Homework 3			   
/////////////////////////////


#include <iostream>

#include "TemplatePol.h"

int main()
{
	Polynom<int > pol1;
	Polynom<int> pol2;


	try
	{

		std::cin >> pol1;
		std::cin >> pol2;
		std::cout << "Pol1: " << pol1;
		std::cout << "Pol2: " << pol2;

		std::cout << std::endl;

		Polynom<int> pol3 = pol1 % pol2;
		std::cout << "Pol3: " << pol3 << std::endl;

		Polynom<int> pol4 = pol1 / pol2;
		std::cout << "Pol4: " << pol4 << std::endl;

		Polynom<int> pol5 = pol1 + pol2;
		std::cout << "Pol5: " << pol5 << std::endl;

		Polynom<int> pol6 = pol1 - pol2;
		std::cout << "Pol6: " << pol6 << std::endl;

		Polynom<int> pol7 = pol1 * pol2;
		std::cout << "Pol7: " << pol7 << std::endl;

		std::cout << "pol1 < pol2: " << (pol1 < pol2) << std::endl;
		std::cout << "pol1 <= pol2: " << (pol1 <= pol2) << std::endl;
		std::cout << "pol3 > pol4: " << (pol3 > pol4) << std::endl;
		std::cout << "pol1 >= pol2: " << (pol1 >= pol2) << std::endl;
		std::cout << "pol1 == pol2: " << (pol1 == pol2) << std::endl;
		std::cout << "pol1 != pol2: " << (pol1 != pol2) << std::endl;

		std::cout << std::endl << std::endl;

		std::cout << "(pol1(1)): " << (pol1(1)) << std::endl;
		std::cout << "(pol1(1, 2)): " << (pol1(1, 2)) << std::endl;

		std::cout << std::endl;

		std::cout << "pol2++: " << pol2++ << std::endl;
		std::cout << "pol2: " << pol2 << std::endl;

		std::cout << std::endl;

		std::cout << "pol1--: " << pol1-- << std::endl;
		std::cout << "pol1: " << pol1 << std::endl;

		std::cout << "pol4.asInt(): " << pol4.asInt() << std::endl;

		std::cout << "pol4: " << pol4;
		std::cout << "Iterator pol4 print begining to end: ";
		for (Polynom<int>::Iterator it = pol4.begin(); it < pol4.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "Iterator pol4 print end to begining: ";
		for (Polynom<int>::Iterator it = (pol4.end()); it >= pol4.begin(); --it)
			std::cout << *it << " ";
		std::cout << std::endl;

	}
	catch (std::bad_alloc &ba)
	{
		std::cerr << "Memory allocation failure" << std::endl;
	}
	catch (std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}

	system("pause");
	return 0;
}