//Author: Ivaylo Evtimov
//FN: 45252
//Group: 5

#include "Order.h"

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void Start()
{
	StartUpCheck();

	char name[256];
	double money = 0;

	Order::Type tp = Order::Type::BUY;
	int id = 0;
	int type = 0;


	bool exit = false;

	while (exit == false)
	{

		char key = 0;

		cout << "Select choice:\n";
		cout << "[W] Add New Wallet\n";
		cout << "[O] Make Order\n";
		cout << "[S] Search by Wallet ID\n";
		cout << "[A] Attract Investors\n";
		cout << "[X] Exit\n";

		cin >> key;

		switch (key)
		{
		case 'W':
			cout << "Enter name: ";
			cin.ignore();
			cin.getline(name, 256);
			cout << "Enter amount: ";
			cin >> money;
			add_wallet(name, money);
			cout << "WALLET DONE.\n";
			break;
		case 'O':
			cout << "Enter ID num: ";

			cin >> id;
			cout << "Select type of Order [1] BUY or [2] SELL\n";

			cin >> type;
			cout << "Enter amount of money: ";
			cin >> money;

			if (type == 1)
				tp = Order::Type::BUY;
			else if (type == 2)
				tp = Order::Type::SELL;
			else
				cout << "Invalid type.\n";

			make_order(tp, money, id);
			break;
		case 'S':
			cout << "Enter valid ID: ";
			cin >> id;

			if (!findId(id))
				cout << "Invalid ID.\n";
			else
				walletInfo(id);

			break;
		case 'A':
			attractInvestors();
			break;
		case 'X':
			exit = true;
			cout << "EXITING.\n";
			break;

		}
	}
}




int main()
{
	Start();
	system("pause");
	return 0;
}