#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>


struct dish
{
	std::string name;
	unsigned int cost;

	dish(std::string name_ = "", unsigned int cost_ = 0)
		: name(name_), cost(cost_) {}

	dish operator=(const dish& d)
	{
		name = d.name;
		cost = d.cost;
		return dish(name, cost);
	}
};


class Menu;
typedef std::vector< dish > DishList;
typedef std::vector< Menu > Basket;


class Menu
{
	friend class Orders;

public:
	Menu(std::string name = "", unsigned int cost = 0);
	Menu(const dish&);
	Menu(DishList);
	Menu(const Menu&);

	const dish* chooseDish();

	inline void addDish(const dish&);
	inline bool deleteDish(int pos);

	friend std::ostream& operator<<(std::ostream& os, Menu& menu);

private:
	DishList aDishList;
};

#endif