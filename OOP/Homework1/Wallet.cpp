#include "Wallet.h"

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

static unsigned int unique = 1; //Used for making new wallets ID, instead of generating randon numbers

void changeContent(const Wallet &W)
{
	int numOfWallets = countWallet()/sizeof(Wallet); //Sees how many wallets there are in wallet.dat
	Wallet* temp = new(nothrow) Wallet[numOfWallets]; //Creates an array of Wallet

	if (!temp)
	{
		cout << "Memory error\n";
		return;
	}

	ifstream input("wallet.dat", ios::in | ios::binary);

	if (!input.is_open())
	{
		cout << "File not opened\n";
		return;
	}

	for (int read = 0; read < numOfWallets; read++)
		input.read((char *)&temp[read], sizeof(Wallet)); //Fills the array with the data in wallet.dat

	input.close();

	ofstream output("wallet.dat", ios::out | ios::binary);

	if (!output.is_open())
	{
		cout << "File not opened\n";
		return;
	}

	for (int write = 0; write < numOfWallets ; write++)
	{
		if (write + 1 == W.id) //If the ID of the array and the entered ID checks out
			output.write((const char *)&W, sizeof(Wallet)); //Overwrite the wallet struct in the files 
		else
			output.write((const char *)&temp[write], sizeof(Wallet)); //Else copy the rest of the array in the files
	}

	output.close();
	delete[] temp;
}

int countWallet()
{
	ifstream file("wallet.dat", ios::in | ios::binary|ios::ate);

	if (!file.is_open())
		return -1;

	int end = file.tellg();
	file.close();
	return end; //Return only the size of the file
}

bool findId(const unsigned& look)
{
	//if (look >= 1 && look < unique)
	//	return true;

	//return false;

	ifstream input("wallet.dat", ios::binary);
	if (!input.is_open())
	{
		cout << "File not open\n";
		return false;
	}

	Wallet temp;

	while (true)
	{
		input.read((char*)&temp, sizeof(Wallet)); //Read a wallet struct in the temp  variable
		if (input.eof())
		{
			cout<<"File not open.\n";
			break;
		}

		if (look == temp.id) //Checks if the temp.id is the that is looked for
			return true;
	}
	input.close();
	return false;
}

Wallet & getWallet(const unsigned &num)
{
	Wallet W;
	ifstream file("wallet.dat", ios::in | ios::binary);
	if (!file.is_open())
		cout << "Error reading file\n";

	while (!file.eof())
	{
		file.read((char*)&W, sizeof(Wallet)); //Readsfrom the file until  
		if (W.id == num) //The W.id is the one that is looked for
		{
			file.close();
			return W;
		}
	}
	file.close();
	return W = { 0,0,0 }; //If there isn't valid W.id return struct with 0.  IDs start from 1, 0 is for invalid IDs.
}

void Print()
{
	ifstream file("wallet.dat", ios::in | ios::binary);
	if(!file.is_open())
	{
		cout<<"File not open.\n";
		return;
	}
	Wallet wallet1;

	for (int count = 1; count < unique; count++)
	{
		file.read((char*)&wallet1, sizeof(Wallet));
		cout << "Money: " << wallet1.fiatMoney << endl;
		cout << "ID: " << wallet1.id << endl;
		cout << "Owner: " << wallet1.owner << endl;
		cout << endl;
	}
}

void walletInfo(const unsigned &num)
{
	ifstream input("wallet.dat", ios::binary);
	if (!input.is_open())
	{
		cout << "File not open\n";
		return;
	}

	Wallet temp;

	while (true)
	{
		input.read((char*)&temp, sizeof(Wallet)); //Read from the file until a valid struct is found
		if (temp.id == num)
			break;

		if (input.eof()) //If the file end without a valid struct is found  
		{
			cout << "NO such wallet\n"; 
			break;
		}
	}

	cout << "Name: " << temp.owner << endl;
	cout << "ID: " << temp.id << endl;
	cout << "Real Money: " << temp.fiatMoney << endl;
	cout << "FMI coins: " << calcCoins(temp.id) << endl;
}

int countNum(unsigned num)
{
	int count = 0;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return count;
}

void attractInvestors()
{
	ifstream input("wallet.dat", ios::binary|ios::ate);
	if (!input.is_open())
	{
		cout << "File not open.\n";
		return;
	}

	int size = input.tellg() / sizeof(Wallet); //If there are less than 10 wallets in wallet in wallet.dat
	input.seekg(0);

	if (size > 10) //If there are mre than 10 wallets in the wallet.dat file 
		size = 10; //Max num for allocating is set to 10
	else
		cout << "Wallets are less than 10.\n";

	Wallet temp;
	Wallet* arrWall = new(nothrow) Wallet[size];
	if (!arrWall)
	{
		cout << "Memory allocation error.\n";
		return;
	}


	//input.read((char*)&arrWall[0], sizeof(Wallet));

	for (int count = 0; count < size; count++)
	{
		for(int count1=1;count1<=size;count1++)
		{
			input.read((char*)&temp, sizeof(Wallet)); //Read a struct from the file

			if (calcCoins(temp.id) > calcCoins(arrWall[count].id) && existingID(temp.id,arrWall,count+1)==1) //If the temp coins are more than arrWall[count] coins
			{                                                        //And if the ID are diffrent
				arrWall[count] = temp;                               
			}

		}
		input.seekg(0);
	}
	input.close();


	for (int count = 0; count < size; count++) //Prints the top wealthiest wallets
	{
		cout << "ID: " << arrWall[count].id << endl;
		cout << "Name: " << arrWall[count].owner << endl;
		cout << "Coins: " << calcCoins(arrWall[count].id) << endl;
		cout << endl;
		firstAndLastTrans(arrWall[count].id);
	}

	delete[] arrWall;
}

bool existingID(const unsigned &num,const Wallet *arr,const int& size)
{
	for (int count = 0; count < size; count++)
	{
		if (arr[count].id == num)
			return false;
	}

	return true;
}

void add_wallet(const char *name, const double& money)
{
	Wallet temp ;
	strcpy(temp.owner, name);
	temp.fiatMoney = money;
	temp.id = unique++;

	Wallet System = { "System", 4294967295, 0 };

	ofstream file("wallet.dat", ios::binary|ios::app); //Opens the file for writing from the end
	if (file.is_open())
	{
		file.write((const char*)&temp, sizeof(Wallet)); //Saves the new struct in the file if the file is open
		file.close();
	}
	else
	{
		cout << "File could not be opened\n";
		return;
	}
	time_t hours = time(NULL); //Generates a time variable
	makeTransactionsV2(hours, System.id, temp.id, money / 375); //Initiates a default transaction for new user
}

void StartUpCheck()
{
	int walletSize = countWallet() / sizeof(Wallet); //Finds out how many wallets there are in wallets.dat
	
	if (walletSize < 0) 
		cout << "No other wallets\n";
	else
		unique += walletSize; //Increases the unique variable depending on the number of wallets
}

