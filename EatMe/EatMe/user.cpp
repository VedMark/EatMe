#include "user.h"

unsigned int User::ID = 0;

User::User(std::string name, std::string password) : aID(ID++), aName(name), aPassword(password) {
	pBuyings = new Basket();
}

User::User(const User& user)
{
	pBuyings = new Basket(*user.pBuyings);
	aID = user.ID;
	aName = user.aName;
	aPassword = user.aPassword;
}

void User::addDishInMenu(Menu* menu) {}

void User::deleteDishes(Menu* menu) {}

void User::parseOrders(Orders *currentOrders, Orders *archive) {}

void User::addInBasket(const Dish& dish_)
{
	pBuyings->addDish(dish_);
}

void User::replenishWallet() {}

int User::getMoney() const { return 0; }

void User::setMoney(float money_) {}



Admin::Admin(std::string FIO, std::string password) : 
	User(FIO, password) {}

Admin::Admin(const Admin& user) :
	User(user) {}

void Admin::addDishInMenu(Menu* menu)
{
	try{
		std::string name = "";
		float cost = 0;

		std::cout << "\nEnter Dish name: ";
		fflush(stdin);
		std::getline(std::cin, name);
		std::cout << "Enter the cost: ";
		if (!(std::cin >> cost))
			throw InputError();

		Dish *dish_ = new Dish(name, cost);
		menu->addDish(*dish_);
	}
	catch (InputError error)
	{
		fflush(stdout);
		std::cin.clear();
		std::cout << error.message;
		return;
	}
}

void Admin::deleteDishes(Menu* menu)
{
	try{
		int choise = 0;
		std::cout << *menu;
		std::cout << "\nChoose Dish to delete: ";
		if (!(std::cin >> choise))
			throw InputError();

		if (choise >= 0 && choise < menu->getDishCount())
			menu->deleteDish(choise - 1);
		else
			std::cout << "\n\n\tWrong input!\n";
	}
	catch (InputError error)
	{
		fflush(stdout);
		std::cin.clear();
		std::cout << error.message;
		return;
	}
}

void Admin::parseOrders(CurrentOrders currentOrders, History archive)
{
	try
	{
		int choise = 0;
		std::cout << *currentOrders;

		std::cout << "1 - choose delivered\n2 - go back\n\n";
		if (!(std::cin >> choise))
			throw InputError();
		while (true)
		{
			switch (choise)
			{
			case 1:{
					   std::cout << "\nChoose delivered order: ";
					   std::cin >> choise;

					   if (choise > 0 && choise <= currentOrders->size()){
						   Order deliveredOrder = currentOrders->deleteOrder(choise - 1);
						   archive->pushOrder(deliveredOrder);
					   }
					   else
						   throw InputError();
					   break;
			}
			case 2:
				return;
			default:
				throw InputError();
			}

			std::cout << "\n\n1 - repeat\n2 - go back\n";
			if (!(std::cin >> choise))
				throw InputError();
			switch (choise)
			{
			case 1:
				parseOrders(currentOrders, archive);
				return;
			case 2:
				return;
			default:
				throw InputError();
			}
		}
	}
	catch (InputError error)
	{
		fflush(stdout);
		std::cin.clear();
		std::cout << error.message;
		return;
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

void Customer::replenishWallet()
{
	try{
		unsigned int money;
		std::cout << "\ninput money count you want to add: ";
		if (!(std::cin >> money))
			throw InputError();
		if (money >= 0 && money < INT_MAX)
			aMoney += money;
		else
			throw InputError();
		std::cout << "\n\tYou have " << aMoney << "$" << std::endl;
	}
	catch (InputError error)
	{
		fflush(stdout);
		std::cin.clear();
		std::cout << error.message;
		return;
	}
}
