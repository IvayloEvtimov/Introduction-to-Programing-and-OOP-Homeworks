#include "Order.h"

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

const double EPS = 0.00001;

void saveOrder(const Order::Type choice,const double& cash,const unsigned& num)
{
	Order O = { choice,num,cash };
	ofstream save("orders.dat", ios::binary|ios::app); //Saves the struct in the end in orders.dat 
	if(!save.is_open())
	{
		cout<<"File not opne.\n";
		return;
	}
	save.write((const char*)&O, sizeof(O));
	save.close();
}

void buy( Wallet& sender, Wallet& receiver, const double& cash,const time_t& hours)    //Initiates an Order
{                                                                                     //Sender loses money, gains coins 
	sender.fiatMoney -= cash*375;
	changeContent(sender);
	
	receiver.fiatMoney += cash * 375;
	changeContent(receiver);

	makeTransactionsV2(hours,  receiver.id, sender.id, cash);
	cout << "Transaction completed\n";
}

Order & findOrdersV2(const double cash, const Order::Type choice)  //Find an Order based  on the opopsite choice
{
	Order temp;
	ifstream file("orders.dat", ios::in | ios::binary);
	if (!file.is_open())
		cout << "File not open\n";

	int size = 0;
	file.seekg(0,ios::end);
	size = file.tellg()/sizeof(Order); //Number of Orders saved in orders.dat

	if (size == 0) //If there are no orders return an Order with id=0
	{
		file.close();
		temp = { choice,0,cash }; //Walletid with 0 is for errors
		return temp;
	}

	file.seekg(ios::beg);

	while (true)
	{	
		file.read((char*)&temp, sizeof(Order)); //Reads Order struct from orders.dat

		if(file.eof()) 
			break;

		if (temp.type != choice) //If the recently read order has the oposide Order::Type        
			if (temp.fmiCoins > 0 && compareDbl(temp.fmiCoins, 0) == 0)   //And the coins ordered are more than 0 and different than 0
			{
				file.close();
				return temp;
			}
	}

	file.close();
	temp = { choice,0,cash }; //If no valid Orders are found return Order with id=0
	return temp;
}

void make_order(const Order::Type choice, double& cash, const unsigned& num) //main function for processing Orders
{
	if (findId(num) == false) 
	{
		cout << "No such ID.\n";
		return;
	}

	bool end = false; //bool for checking if the coins in order are completed
	bool hasGeneratedText = false; //bool for checking if a file name has been generated for the text file

	char* fileName = NULL;

	Wallet W1 = getWallet(num);

	time_t hours = time(NULL);
	unsigned countTrans = 0; //For counting the number of transaction made during the process

	while (true)
	{
		if (choice == Order::Type::BUY)
		{
			if (W1.fiatMoney < cash * 375)   //If the one making the Order doesn't have enough money 
			{
				cout << "NOT ENOUGH CASH\n" << "SAVING ORDER\n";
				saveOrder(choice, cash, num); //Saves the Order in orders.dat file
				cout << "ORDER SAVED\n";
				break;
			}

		}
		else if (choice == Order::Type::SELL)
		{
			if (calcCoins(W1.id) < cash) //If the one making the Order doesn't have enough coins
			{
				cout << "NOT ENOUGH CASH\n"<<"SAVING ORDER\n";
				saveOrder(choice, cash, W1.id); //Saves the Order in orders.dat
				cout << "ORDER SAVED\n";
				break;
			}

		}

		Order O = findOrdersV2(cash, choice); //When the one making the Orders is found to be valid, find compatible Order 

		if (O.walletId == 0) //If O.walletId is 0, then there are no compatible Orders
		{
			cout << "NO SUCH ORDER AVALIABLE\n"<<"SAVING ORDER\n";
			saveOrder(choice, cash, num); 
			cout << "ORDER SAVED\n";
			break;
		}
		else
		{

			Wallet W2 = getWallet(O.walletId); //After a valid Orders has been found, W2 get the wallet by the ID
			if (calcCoins(W2.id) < O.fmiCoins && compareDbl(calcCoins(W2.id),O.fmiCoins)==0) //If W2 has less coins that the one put in the Order
			{                                                               //and if W2 coins and the Orders coins aren't equal
				cout << "THE OTHER PARTY DOESN'T HAVE REQUIERED AMOUNT Of COINS\n"<<"SAVING ORDER\n";
				saveOrder(choice, cash, num);
				cout << "ORDER SAVED\n";
			}
			double cashDiff = calcOrder(O.fmiCoins, cash);


			if (!hasGeneratedText) //After validating Order and Finding the Wallet, generate fileName for the text file
			{
				if(choice==Order::Type::BUY)
					fileName = generateTextName(choice, W1, W2, hours);
				else
					fileName = generateTextName(choice, W2, W1, hours);

				hasGeneratedText = true;
			}

			if (compareDbl(cash - O.fmiCoins, 0) == 0) //Check if the diffenrence between cash,O.FmiCoins is not 0
			{
				cash = cash - O.fmiCoins;
				if (choice == Order::Type::BUY)
				{
					if (cash < 0)
					{
						buy(W1, W2, fabs(cash ), hours);
						saveOrderInText(W1, W2, fabs(cash ), false, countTrans,fileName);
					}
					else
					{
						buy(W1, W2, O.fmiCoins, hours);
						saveOrderInText( W1, W2, O.fmiCoins, false, countTrans,fileName);
					}
					countTrans++;
				}
				else if (choice == Order::Type::SELL)
				{
					if (cash < 0)
					{
						buy(W2, W1, fabs(cash), hours);
						saveOrderInText( W2, W1, fabs(cash),  false, countTrans,fileName);
					}
					else
					{
						buy(W2, W1, O.fmiCoins, hours);
						saveOrderInText(W2, W1, O.fmiCoins,  false, countTrans,fileName);
					}
					countTrans++;
				}
			}
			else //If it's 0, then the orders will be completed
			{
				end = true;
				if (choice == Order::Type::BUY)
				{
					if (cash < 0)
					{
						buy(W1, W2, fabs(cash - O.fmiCoins), hours);
						saveOrderInText( W1, W2, fabs(cash - O.fmiCoins), false,countTrans,fileName);
					}
					else
					{
						buy(W1, W2, O.fmiCoins, hours);
						saveOrderInText( W1, W2,O.fmiCoins, false, countTrans,fileName);
					}
					countTrans++;
				}
				else if (choice == Order::Type::SELL)
				{
					if (cash < 0)
					{
						buy(W2, W1, fabs(cash ), hours);
						saveOrderInText( W2, W1, fabs(cash - O.fmiCoins), false, countTrans,fileName);
					}
					else
					{
						buy(W2, W1, O.fmiCoins, hours);
						saveOrderInText( W2, W1, O.fmiCoins, false, countTrans,fileName);
					}
					
					countTrans++;
				}
			}


			modifyOrder(cashDiff, O); //Modifies the compatible Order so that the changes are saved in the file
			//orderPrint();

			if (cash < 0) 
				end = true;

			if (end == true)
				break;
		}
	}

	if (end == true) //If cash variable has been reduces to 0, then the Order has been fully completed
		cout << "ORDER FULLY COMPLETED\n";
	else 
		cout << "ORDER PARTIALY COMPLETED\n";

	if(countTrans>1) //If an Transactions have been made, then the number of them are saved in the end of the text file
		saveOrderInText(W1, W1, 0,true,countTrans,fileName);

}

void modifyOrder(const double cashDiff, Order &O) //Saves a modified Order at the end of orders.dat unless if O.fmiCoins = 0
{
	ifstream input("orders.dat", ios::binary|ios::ate); 

	if (!input)
	{
		cout << "File not opened\n";
		return;
	}

	size_t size = input.tellg()/sizeof(Order);
	input.seekg(0);
	Order* temp = new(nothrow) Order[size]; //Allocates array based on number of Orders in orders.dat file

	if (!temp)
	{
		cout << "Memory error\n";
		return;
	}

	int equal = 0; 

	for (int readCount = 0; readCount<size; readCount++)
	{
		input.read((char *)&temp[readCount], sizeof(Order));
		if (temp[readCount] == O) //If the last saved Order matches with the Order& O
			equal = readCount; //The position in the array is saved
	}
	input.close();

	ofstream output("orders.dat",ios::binary);

	if (!output.is_open())
	{
		cout << "File not opened\n";
		return;
	}

	bool isZero = false;
	O.fmiCoins = cashDiff;
	if (compareDbl(O.fmiCoins, 0) == 1)
		isZero = true;

	for (int writeCount = 0; writeCount < size; writeCount++)
	{		
		 if(equal!=writeCount)
			output.write((const char *)&temp[writeCount], sizeof(Order)); //Copies the orders from the array in the orders.dat exept the one that is identical to Order& O
	}
	if (isZero == false) //If Order& O has coins > 0
		output.write((const char*)&O, sizeof(Order)); //It is saved at the end if the file, if not it is not

	output.close();
	delete[] temp;
}

void orderPrint()
{
	Order temp;
	ifstream input("orders.dat",ios::binary);

	if (!input.is_open())
	{
		cout << "File not opened\n";
		return;
	}

	input.seekg(0, ios::end);
	size_t size = input.tellg() / sizeof(Order);
	input.seekg(0);

	for(int count=0;count<size;count++)
	{
		input.read((char *)&temp, sizeof(Order));
		cout << "Type: " << temp.type << endl;
		cout << "Wallet ID: " << temp.walletId << endl;
		cout << "FMI Coins: " << temp.fmiCoins << endl;
		cout << endl;
	}
	input.close();
}

bool operator==(const Order &temp1, const Order &temp2)
{
	if (temp1.type == temp2.type)
		if (temp1.walletId == temp2.walletId)
			if (compareDbl(temp1.fmiCoins, temp2.fmiCoins)==1)
				return true;
	return false;
}

bool compareDbl(const double& num1, const double& num2)
{
	if (fabs(num1 - num2) < EPS)

		return true;
	return false;
}

double calcOrder(const double &coins, const double &cash)
{
	double temp = coins - cash;
	if (temp < 0)
		return 0;

	return temp;
}

void saveOrderInText(const Wallet &sender, const Wallet &receiver, const double &money,bool atEnd, const int& countTrans,const char* fileName)
{
	ofstream output(fileName,ios::app); //Open a text file for output based on predetermined fileName

	if (!output.is_open())
	{
		cout << "File not open.\n";
		return;
	}

	if (!atEnd) //If all Orders have been completed by the one making them, it saves the number of Transaction made
		output << sender.id << " " << receiver.id << " " << money << endl;
	else
		output << countTrans;

	output.close();
}

char* generateTextName(const Order::Type choice,const Wallet& sender,const Wallet& receiver,const time_t& hours)
{
	int sizePart1 = 0,
		sizePart2 = 0;

	if (choice == Order::Type::BUY)
		sizePart1 = countNum(sender.id);
	else
		sizePart1 = countNum(receiver.id);

	sizePart2 = countNum(hours);

	char* fileName = new(nothrow) char[sizePart1 + sizePart2 + 2 + 4];
	if (!fileName)
	{
		cout << "ERROR/n";
		return NULL;
	}

	int  part1 = 0;

	if (choice == Order::Type::BUY)
		part1 = sender.id;
	else
		part1 = receiver.id;

	long long part2 = hours;

	bool space = false;

	for (int count = sizePart1 + sizePart2; count >= 0; count--) //Saves the 2 number variables in the fileName char
	{
		if (part2 == 0 && space == false)
		{
			fileName[count] = ' ';
			count--;
			space = true;
		}

		if (part2 > 0)
		{
			fileName[count] = part2 % 10 + '0';
			part2 /= 10;
		}
		else
		{
			fileName[count] = part1 % 10 + '0';
			part1 /= 10;
		}

	}

	//Add the extension of the file
	fileName[sizePart1 + sizePart2 + 1] = '.';
	fileName[sizePart1 + sizePart2 + 2] = 't';
	fileName[sizePart1 + sizePart2 + 3] = 'x';
	fileName[sizePart1 + sizePart2 + 4] = 't';
	fileName[sizePart1 + sizePart2 + 2 + 3] = 0;

	return fileName;
}
