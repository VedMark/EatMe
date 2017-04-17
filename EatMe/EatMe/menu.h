#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class Dish;
class Menu;
typedef Menu Basket;
typedef std::vector< Dish > DishList;

class Dish
{
	std::string name;
	float cost;

public:
	Dish(std::string name_ = "", float cost_ = 0);

	Dish operator=(const Dish& d);

	std::string getName() const { return name; }
	void setName(std::string name_) { name = name_; }

	float getCost() const { return cost; }
	void setCost(float cost_) { cost = cost_; }
};

class Menu
{
	friend class Orders;

public:
	Menu();
	Menu(std::string name, float cost);
	Menu(const Dish&);
	Menu(const Menu&);

	void addDish(const Dish&);
	bool deleteDish(unsigned int pos);
	float calcDishCost() const;
	inline int getDishCount() const { return aDishList.size(); }
	inline DishList getDishList() const { return aDishList; }

	const Dish* chooseDish() const;

	friend std::ostream& operator<<(std::ostream& os, const Menu& menu);

private:
	DishList aDishList;
};
