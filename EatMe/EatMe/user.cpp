#include "menu.h"
#include "order.h"
#include "user.h"
#include "utils.h"

unsigned int User::ID = 0;

User::User(std::string name, std::string password) : pBuyings(NULL), aID(ID++), aName(name), aPassword(password) {}

User::User(const User& user)
{
	pBuyings = new Basket(*user.pBuyings);
	aID = user.ID;
	aName = user.aName;
	aPassword = user.aPassword;
}

void User::addInBasket(const dish& dish_)
{
	pBuyings->push_back(dish_);
}

void User::addDishInMenu(Menu* menu)
{}

void User::deleteDish(Menu* menu)
{}

void User::parseOrders(Orders *currentOrders, Orders *archive)
{}

void User::replenishWallet()
{}

Admin::Admin(std::string FIO, std::string password) : 
	User(FIO, password) {}

Admin::Admin(const Admin& user) :
	User(user) {}

void Admin::A()
{}

void Admin::addDishInMenu(Menu* menu)
{
	std::string name = "";
	unsigned int cost = 0;

	std::cout << "Enter dish name : ";
	std::cin >> name;
	std::cout << "Enter your password : ";
	std::cin >> cost;

	dish *dish_ = new dish(name, cost);

}

void Admin::deleteDish(Menu* menu)
{
	int choise = 0;
	std::cout << this;
	std::cout << "Choose dish number to delete ";
	utilits::choise_input(choise);

	if (menu->deleteDish(choise - 1))

	std::cout << "1 - repeat\n 2 - go back\n";
	utilits::choise_input(choise);
	while (true)
	{
		try
		{
			switch (choise)
			{
			case 1:
				deleteDish(menu);
				return;
			case 2:
				return;
			default:
				throw("\n\t\tWRONG VALUE!!!\n\nReapet input\n");
			}
		}
		catch (std::string warning)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << warning;
			std::cout << "\n================================> ";
		}
	}
}

void Admin::parseOrders(Orders *currentOrders, Orders *archive)
{
	char choise = 0;
	std::cout << *currentOrders;
	std::cout << "Choose delivered order: ";
	utilits::choise_input(choise);

	currentOrders->deleteOrder(choise - 1);

	std::cout << "1 - repeat\n 2 - go back\n";
	utilits::choise_input(choise);
	while (true)
	{
		try
		{
			switch (choise)
			{
			case 1:
				parseOrders(currentOrders, archive);
				return;
			case 2:
				return;
			default:
				throw("\n\t\tWRONG VALUE!!!\n\nReapet input\n");
			}
		}
		catch (std::string warning)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << warning;
			std::cout << "\n================================> ";
		}
	}
}


Customer::Customer(std::string FIO, std::string password, std::string address, unsigned int money) :
	User(FIO, password), aAddress(address), aMoney(money)
{}

Customer::Customer(const Customer& user) :
	User(user)
{
	aAddress = user.aAddress;
	aMoney = user.aMoney;
}

void Customer::addInBasket(const dish& dish_)
{
	pBuyings->push_back(dish_);
}

void Customer::replenishWallet()
{
	unsigned int money;
	std::cout << "Input money count you want to add: ";
	utilits::choise_input(money);
	aMoney += money;
}
