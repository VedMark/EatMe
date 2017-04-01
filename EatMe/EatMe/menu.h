#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

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


typedef std::vector<dish> DishList;

class Menu;
typedef Menu Basket;

class Menu
{
	friend class Orders;

public:
	Menu(std::string name = "", unsigned int cost = 0);
	Menu(const dish&);
	Menu(DishList);
	Menu(const Menu&);

	inline void addDish(std::string name, unsigned int cost);
	inline void addDish(const dish&);
	inline void deleteDish();

	friend ostream& operator<<(ostream& os,  Menu& menu)
	{
		for (int i = 0; i < menu.aDishList.size(); ++i)
			os << i + 1 << " - " << menu.aDishList[i].name << " "
			<< menu.aDishList[i].cost;
		return os;
	}

private:
	DishList aDishList;
};

#endif //MENU_H