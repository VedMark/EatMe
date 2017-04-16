#pragma once

#include <iostream>
#include <deque>
#include <string>
#include <iomanip>

#include "menu.h"

typedef Orders* CurrentOrders;
typedef Orders* History;

class Order
{	
public:
	Order();
	Order(std::string name);
	Order::Order(const Order& order);

	inline std::string getCustomerName() const { return aCustomerName; }

	inline Basket* getBasket() const { return pBasket; }
	inline void setBasket(Basket* basket) { pBasket = new Basket(*basket); }

	float getCost() const;

private:
	std::string aCustomerName;
	Basket* pBasket;
};

class Orders
{
public:
	Orders();
	Orders(const Orders&);

	inline int size() const { return aOrders.size(); }

	Order pushOrder(const Order);
	const Order& getOrder(int pos);

	Order deleteOrder(int pos);
	
	friend std::ostream& operator<<(std::ostream& os, const Orders& orders);

private:
	std::deque< Order > aOrders;
};
