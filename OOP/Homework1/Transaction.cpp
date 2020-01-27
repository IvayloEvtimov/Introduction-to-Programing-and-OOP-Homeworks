#include "Transaction.h"

#include <iostream>
#include <fstream>


using namespace std;

int countTransaction()
{
	ifstream file("transactions.dat", ios::in | ios::binary);
	if (!file)
	{
		return -1;
	}
	size_t end;
	file.seekg(0, ios::end);
	end = file.tellg();
	file.close();
	return end; //Return only the size of transactions.dat file 
}

void makeTransactionsV2(const long long& hours,const unsigned& sender, const unsigned& receiver, const double& cash)
{
	Transaction T = { hours,sender,receiver,cash };
	ofstream file("transactions.dat",ios::binary | ios::app); //Saves the new struct at the end of the file
	if (!file.is_open())
	{
		cout << "File not open";
		return;
	}
	file.write((const char*)&T, sizeof(Transaction));
	file.close();
}

double calcCoins(const unsigned &id)
{
	ifstream input("transactions.dat", ios::binary);
	if (!input.is_open())
	{
		cout << "File not open.\n";
		return -1;
	}

	double sum = 0;

	Transaction temp;

	while(true)
	{
		input.read((char*)&temp, sizeof(Transaction));  //Read from transactions.dat file until the end if met

		if (input.eof())
			break;
               //If the desired ID is
		if (temp.senderId == id) //sender
			sum -= temp.fmiCoins; //reduce the overall sum
		else if (temp.receiverId == id)
			sum += temp.fmiCoins; //else increase overall sum
	}

	return sum;
}

void printTrans()
{
	ifstream input("transactions.dat", ios::in | ios::binary);

	Transaction temp;

	while (!input.eof())
	{
		input.read((char*)&temp, sizeof(Transaction));
		cout << "Sender ID: " << temp.senderId<< endl;
		cout << "Receiver ID: " << temp.receiverId << endl;
		cout << "Coins: " << temp.fmiCoins << endl;
		cout << endl;
	}

	input.close();
}

void firstAndLastTrans(const unsigned &num)
{
	bool checkFist = false;
	bool checkLast = false;

	Transaction First,Last, temp;

	ifstream input("transactions.dat", ios::binary);
	if (!input.is_open())
	{
		cout << "File not open.\n";
		return;
	}

	while (true)
	{
		input.read((char*)&temp, sizeof(Transaction)); //Read from file until the end is met

		if (input.eof())
			break;

		if (temp.senderId == num || temp.receiverId == num) //If the id is either sender or receiver
		{
			if (!checkFist)
				First = temp; //Saves the first valid struct found 
			else
			{
				Last = temp; //After the first is found everything else if it;s valid is saved in Last variable
				checkLast = true;
			}

			checkFist = true;
		}
	}

    //If the ID of the array and the entered ID checks out
	cout << "Fist Transaction Made: \n";
	cout << "Time made: " << First.time << endl;
	cout << "Sender's ID: " << First.senderId << endl;
	cout << "Receiver's ID: " << First.receiverId << endl;
	cout << "Amount of Money Transfered: " << First.fmiCoins << endl;

	if (!checkLast) //If there is only one transaction made by that wallet ID
		Last = First;

	cout << endl;

    //If the ID of the array and the entered ID checks out
	cout << "Last Transaction Made: \n";
	cout << "Time made: " << Last.time << endl;
	cout << "Sender's ID: " << Last.senderId << endl;
	cout << "Receiver's ID: " << Last.receiverId << endl;
	cout << "Amount of Money Transfered: " << Last.fmiCoins << endl;

	cout << endl;
}
