#ifndef ORDER_HDR
#define ORDER_HDR

#include <time.h>

#include "Wallet.h"


struct Order {
	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};

void saveOrder(const Order::Type choice, const double&, const unsigned&); //Saves an Order in orders.dat file
void buy(Wallet&, Wallet&, const double&, const time_t&); //Initiates an Order and saves the transaction in transaction.dat
Order& findOrdersV2(const double, const Order::Type); //Returns an Order of the oposide Order::Type
void make_order(const Order::Type, double&, const unsigned&); //makes order
void modifyOrder(const double, Order&); //Modifies an Orders and saves it in the end of orders.dat file
void orderPrint();
bool operator==(const Order&, const Order&);
bool compareDbl(const double&, const double&); //Compares 2 double numbers with EPS const
double calcOrder(const double&, const double&); //Reduces 2 double numbers and checks if the result is <0
void saveOrderInText(const Wallet&, const Wallet&, const double&, bool, const int&, const char*); //Saves all orders initiated by the ID in text file
char* generateTextName(const Order::Type, const Wallet&, const Wallet&, const time_t&); //Generates a fileName for the text file

#endif // !ORDER_HDR


