#include "menu.h"
#include "order.h"

Order::Order() : aCustomerName(""), pBasket(nullptr) {}
Order::Order(std::string name) : aCustomerName(name) {}
Order::Order(const Order& order)
{
	pBasket = order.pBasket;
	aCustomerName = order.aCustomerName;
}

Orders::Orders() 
	: aOrders() {}
Orders::Orders(const Orders& orders)
{
	aOrders = orders.aOrders;
}

void Orders::pushOrder(const Order order_)
{
	aOrders.push_back(order_);
}

const Order& Orders::getOrder(int pos)
{
	return aOrders[pos];
}
void Orders::deleteOrder(int pos)
{
	aOrders.erase(aOrders.begin() + pos);
}

std::ostream& operator<<(std::ostream& os, const Orders& orders)
{
	for (unsigned int i = 0; i < orders.aOrders.size(); ++i)
	{
		std::string name = orders.aOrders[1].getCustomerName();
		std::cout << i + 1 << name;
	}
	return os;
}
