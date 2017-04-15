#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class dish;
class Menu;
typedef std::vector< dish > DishList;

class dish
{
	std::string name;
	unsigned int cost;

public:
	dish(std::string name_ = "", unsigned int cost_ = 0)
		: name(name_), cost(cost_) {}

	dish operator=(const dish& d)
	{
		name = d.name;
		cost = d.cost;
		return dish(name, cost);
	}

	std::string getName() const { return name; }
	void setName(std::string name_) { name = name_; }

	unsigned int getCost() const { return cost; }
	void setCost(unsigned int cost_) { cost = cost_; }
};

class Menu
{
	friend class Orders;

public:
	Menu(std::string name = "", unsigned int cost = 0);
	Menu(const dish&);
	Menu(DishList);
	Menu(const Menu&);

	const dish* chooseDish();

	void addDish(const dish&);
	bool deleteDish(unsigned int pos);

	friend std::ostream& operator<<(std::ostream& os, Menu& menu);

private:
	DishList aDishList;
};

#endif