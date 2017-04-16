#include "menu.h"
#include "user.h"

Dish::Dish(std::string name_, float cost_)
: name(name_), cost(cost_) {}

Dish Dish::operator=(const Dish& d)
{
	name = d.name;
	cost = d.cost;
	return Dish(name, cost);
}

Menu::Menu()
{}

Menu::Menu(std::string name, float cost)
{
	aDishList.push_back(Dish(name, cost));
}

Menu::Menu(const Dish& dish_)
{
	aDishList.push_back(dish_);
}

Menu::Menu(const Menu& menu)
{
	aDishList = menu.aDishList;
}

void Menu::addDish(const Dish& dish_)
{
	aDishList.push_back(dish_);
}

bool Menu::deleteDish(unsigned int pos)
{
	if (pos < aDishList.size())
		aDishList.erase(aDishList.begin() + pos);
	else
		return false;
	return true;
}

float Menu::calcDishCost() const
{
	float cost = 0;
	for (unsigned int i = 0; i < aDishList.size(); ++i)
		cost += aDishList[i].getCost();
	return cost;
}

const Dish* Menu::chooseDish() const
{
	char choise = 0;
	try
	{
		std::cout << *this;
		std::cout << "1 - Choose a Dish\n2 - go back\n" << std::endl;

		while (true)
		{

			if (!(std::cin >> choise))
				throw InputError();
			switch (choise)
			{
			case '1': break;
			case '2': return nullptr;
			default: throw InputError();
			}
			break;
		}
		std::cout << "\nEnter the number of Dish: ";
		std::cin >> choise;
	}
	catch (InputError error)
	{
		fflush(stdout);
		std::cin.clear();
		std::cout << error.message;
		return nullptr;
	}
	return choise >= 0 && choise < aDishList.size() ? &aDishList[choise - 49] : nullptr;
}

std::ostream& operator<<(std::ostream& os, const Menu& menu)
{
	std::cout << "\n------------------MENU------------------\n";
	for (unsigned int i = 0; i < menu.aDishList.size(); ++i)
		os << i + 1 << " - " << menu.aDishList[i].getName() << " "
		<< menu.aDishList[i].getCost() << "$" << std::endl;
	std::cout << "----------------------------------------\n\n";
	return os;
}
