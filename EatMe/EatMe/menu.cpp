#include "menu.h"

Menu::Menu(std::string name, unsigned int cost)
{
	aDishList.push_back(dish(name, cost));
}

Menu::Menu(const dish& dish_)
{
	aDishList.push_back(dish_);
}

Menu::Menu(DishList dishList) : aDishList(dishList) {}


Menu::Menu(const Menu& menu)
{
	aDishList = menu.aDishList;
}

void addDish()
{

}

void deleteDish()
{

}