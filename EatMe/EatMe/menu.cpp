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

const dish* Menu::chooseDish()
{
	char choise = 0;
	std::cout << *this;
	std::cout << "\n--------------------------------\n";
	std::cout << "1 - Choose a dish\n2 - go back\n" << std::endl;

	while (true)
	{
		try
		{
			std::cin >> choise;

			switch (choise)
			{
			case 1: break;
			case 2: return nullptr;
			default: throw("\n\t\tWRONG VALUE!!!\n\nReapet input\n");
			}
			break;
		}
		catch (std::string warning)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << warning;
			std::cout << "\n================================> ";
		}
	}

	std::cout << "Enter the number of dish: ";
	std::cin >> choise;
	return &aDishList[choise - 1];
}

void Menu::addDish(const dish& dish_)
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


std::ostream& operator<<(std::ostream& os, Menu& menu)
{
	for (unsigned int i = 0; i < menu.aDishList.size(); ++i)
		os << i + 1 << " - " << menu.aDishList[i].getName() << " "
		<< menu.aDishList[i].getCost();
	return os;
}
