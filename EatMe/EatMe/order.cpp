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

Order Orders::pushOrder(const Order order_)
{
	aOrders.push_back(order_);
	return order_;
}

const Order& Orders::getOrder(int pos)
{
	return aOrders[pos];
}

Order Orders::deleteOrder(int pos)
{
	Order order = aOrders[pos];
	aOrders.erase(aOrders.begin() + pos);
	return order;
}

std::ostream& operator<<(std::ostream& os, const Orders& orders)
{
	std::cout << "\n----------------------------------------\n";
	std::cout.setf(std::ios::left);
	for (unsigned int i = 0; i < orders.aOrders.size(); ++i)
	{
		std::string name = orders.aOrders[i].getCustomerName();
		std::cout << i + 1 << ": " << std::setw(16) << name
			<< " " << orders.aOrders[i].getBasket()->calcDishCost() << "$";
	}
	std::cout.unsetf(std::ios::left);
	if (!orders.aOrders.size())
		std::cout << "No orders!";
	std::cout << "\n----------------------------------------\n";
	return os;
}
