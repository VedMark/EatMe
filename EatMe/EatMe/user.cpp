#include "user.h"

void User::seeMenu()
{
	char choise;
	std::cout << "1 - LogIn\n2 - See dishes\n 3 - Exit";
	std::cin >> choise;

	switch (choise)
	{
	case 1: logIn(); break;
	case 2: seeDishes(); break;
	case 3: exit(0); break;
	}
}

void User::seeDishes()
{
	unsigned int choise;
	
	//for (int i = 0; i < pDishList; ++i)
	//	std::cout << i + 1 << pDishList[i];

	std::cin >> choise;

	//addInBasket(pDishList[i]);
}

void User::addInBasket(unsigned int choise)
{

}




unsigned int LogedInUser::ID = 0;

LogedInUser::LogedInUser(std::string FIO, std::string password) : aId(ID++), aName(FIO), aPassword(password) 
	{}

LogedInUser::LogedInUser(const LogedInUser& user)
{
	aId = ID++;
	aName = user.aName;
	aPassword = user.aPassword;
}

Admin::Admin(std::string FIO, std::string password) : 
	LogedInUser(FIO, password) {}

Admin::Admin(const Admin& user)
{
	LogedInUser(user);
}

void Admin::seeMenu()
{
	char choise;
	std::cout << "1 - Add new dish\n2 - Delete dish\n 3 - See orders\n4 - Exit";
	std::cin >> choise;

	switch (choise)
	{
	case 1: addDishInMenu(); break;
	case 2: deleteDish(); break;
	case 3: seeOrders(); break;
	case 4: exit(0); break;
	}

}

void Admin::addDishInMenu()
{

}

void Admin::deleteDish()
{

}

void Admin::seeOrders()
{

}





Customer::Customer(std::string FIO, std::string password) :
	LogedInUser(FIO, password) {}

Customer::Customer(const Customer& user)
{
	LogedInUser(user);
}

void Customer::seeMenu()
{
	char choise;
	std::cout << "1 - See dishes\n2 - Exit";
	std::cin >> choise;

	switch (choise)
	{
	case 1: seeDishes(); break;
	case 2: exit(0); break;
	}

}
