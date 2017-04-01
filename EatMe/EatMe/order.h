#ifndef ORDER_H
#define ORDER_H

#include <vector>

typedef User;
typedef Basket;
typedef std::pair<User*, Basket*> order;

class Orders
{
public:
	Orders();
	Orders(std::vector<order> orders);
	Orders(const Orders&);

	void pushOrder(const order&);
	const order& getOrder();

private:
	std::vector<order> aOrders;
};

#endif //ORDER_H
