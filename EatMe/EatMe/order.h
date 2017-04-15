#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <deque>
#include <string>

#include "menu.h"



class Order
{	
public:
	Order();
	Order(std::string name);
	Order::Order(const Order& order);

	inline std::string getCustomerName() const { return aCustomerName; }
	inline Menu* getBasket() const { return pBasket; }

private:
	std::string aCustomerName;
	Menu* pBasket;
};

class Orders
{
public:
	Orders();
	Orders(const Orders&);

	inline void pushOrder(const Order);
	inline const Order& getOrder(int pos);
	inline void deleteOrder(int pos);

	friend std::ostream& operator<<(std::ostream& os, const Orders& orders);

private:
	std::deque< Order > aOrders;
};

#endif