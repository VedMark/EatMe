#include "EatMe.h"

EatMe::EatMe()
{
	pMenu = new Menu();
	pMenu->addDish(Dish("a", 1));
	pMenu->addDish(Dish("b", 2));

	pCurrentUser = nullptr;

	pOrderLine = new Orders();
	pOrderArchive = new Orders();
}

EatMe::~EatMe()
{
	delete pMenu;
	delete pCurrentUser;
	delete pOrderLine;
	delete pOrderArchive;
}

int EatMe::run()
{
	while (true)
	{
		try
		{
			char choise = 0;
			std::cout << "1 - Sign in\n2 - Sign up\n3 - Exit" << std::endl;
			std::cin >> choise;

			switch (choise)
			{
			case '1': signIn(); break;
			case '2': signUp(); break;
			case '3': exit(0);
			default: throw InputError();
			}
		}
		catch (InputError error)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << error.message;
			run();
		}
	}
}

//	ADMIN: 
//		login - admin 
//		password - qwerty

void EatMe::signIn()
{
	if (pCurrentUser){
		delete pCurrentUser;
		pCurrentUser = NULL;
	}
	std::string name = "";
	std::string password = "";

	std::cout << "\n\tWe are glad to see you in our shop!\n\n";

	std::cout << "Login: ";
	std::cin >> name;
	std::cout << "Password: ";
	password = hide_input();

	std::deque<std::string> user_info = find_user(PASSWORD_FILE_NAME, name, password);

	if (user_info.size())
	{
		UserType _user_type = (UserType)std::stoi(user_info[0]);
		switch (_user_type)
		{
		case CUSTOMER: pCurrentUser = new Customer(user_info[1], user_info[2], user_info[3], std::stoi(user_info[4])); break;
		case ADMIN: pCurrentUser = new Admin(user_info[1], user_info[2]); break;
		}
		show_menu(_user_type);
	}
	else
		std::cout << "\n\tWrong login or password\n\n";
	run();
}

void EatMe::signUp()
{
	if (pCurrentUser){
		delete pCurrentUser;
		pCurrentUser = NULL;
	}
	std::string name = "";
	std::string password = "";
	std::string address = "";
	unsigned int money = 0;

	std::cout << "\n\tWe are glad to see new customer in our shop!\n\n";

	std::cout << "Login: ";
	fflush(stdin);
	std::getline(std::cin, name);
	std::cout << "Password: ";
	password = hide_input();
	std::cout << "Address: ";
	fflush(stdin);
	std::getline(std::cin, address);
	std::cout << "Money count: ";
	std::cin >> money;

	if (user_exist(PASSWORD_FILE_NAME, name)){
		std::cout << "\n\tUser with this login already exists!\n\n";
		run();
		return;
	}
	else
		pCurrentUser = new Customer(name, password, address, money);

	std::ofstream os;
	os.open(PASSWORD_FILE_NAME, std::ios::app);
	std::string ct = encrypt(std::to_string(CUSTOMER) + "*" +
		name + "*" + password + "*" + address + "*" + std::to_string(money)
		, 11);
	os << ct << '\n';
	os.close();

	show_menu(CUSTOMER);
}

void EatMe::show_menu(UserType person)
{
	while (true)
	{
		try
		{
			char choise = 0;
			switch (person)
			{
			case CUSTOMER:{
								std::cout << "\n1 - Show the Menu\n2 - Replenish the wallet\n3 - See current money\n"
									<< "4 - Send Order\n5 - Log out\n6 - Exit\n" << std::endl;
								std::cin >> choise;

								switch (choise)
								{
								case '1':{
											 const Dish* _chosen_dish = pMenu->chooseDish();
											 if (_chosen_dish)
												 pCurrentUser->addInBasket(*_chosen_dish);
											 else
												 throw InputError();
											 break;
								}
								case '2': pCurrentUser->replenishWallet(); break;
								case '3': std::cout << "\n\tYou have now " << pCurrentUser->getMoney() << "$\n"; break;
								case '4': newOrder(); break;
								case '5': system("cls"); run(); return;
								case '6': exit(0);
								default: throw InputError();
								}
								break;
			}
			case ADMIN:{
						   std::cout << "\n1 - Add new Dish\n2 - Delete Dish\n3 - See orders\n"
							   << "4 - See history\n5 - Parse Orders\n6 - Log out\n7 - Exit\n" << std::endl;
						   std::cin >> choise;

						   switch (choise)
						   {
						   case '1': pCurrentUser->addDishInMenu(pMenu); break;
						   case '2': pCurrentUser->deleteDishes(pMenu); break;
						   case '3': std::cout << *pOrderLine; break;
						   case '4': std::cout << *pOrderArchive; break;
						   case '5': pCurrentUser->parseOrders(pOrderLine, pOrderArchive); break;
						   case '6': system("cls"); run(); return;
						   case '7': exit(0); break;
						   }
						   break;
			}
			default: return;
			}
		}
		catch (InputError error)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << error.message;
		}
	}
	return;
}

void EatMe::newOrder()
{
	Order order = Order(pCurrentUser->getName());
	Basket* basket = pCurrentUser->getBasket();
	if (!basket->getDishCount())
	{
		std::cout << "\n\tYou ordered nothing!\n";
		return;
	}
	order.setBasket(basket);

	float cost = basket->calcDishCost();
	if (cost < pCurrentUser->getMoney()){
		pOrderLine->pushOrder(order);
		pCurrentUser->setMoney(pCurrentUser->getMoney() - cost);
		std::cout << "\n\tYour order is waiting for to be delivered!" << std::endl;
	}
	else
		std::cout << "You have no enough money" << std::endl;
}

std::string EatMe::hide_input()
{
	std::string var = "";
	char ch;
	fflush(stdin);
	for (int i = 0; i < MAX_PASSWORD_LENGTH - 1; ++i)
	{
		ch = _getch();
		
		if ('\r' != ch){
			if (PASSWORD_ALPHABET.find(ch) != -1){
				var += ch;
				_putch('*');
			}
			else{
				std::cout << "\n\n\tWRONG LETTER! REPEAR input" << std::endl;
				hide_input();
				break;
			}
		}
		else
		{
			var += '\0';
			break;
		}
	}
	std::cout << std::endl;
	fflush(stdin);
	return var;
}

std::deque<std::string> EatMe::find_user(std::string file_name, std::string name, std::string password)
{
	std::deque<std::string> _user_array;
	std::ifstream file(file_name);
	std::string user_info = "";
	while (file)
	{
		std::getline(file, user_info);
		user_info = decrypt(user_info, 11);
		_user_array = Split(user_info);
		if (_user_array.size() >= 3)
		if (_user_array[1] == name && _user_array[2] == password)
			return _user_array;
	}
	return std::deque<std::string>();
}

bool EatMe::user_exist(std::string file_name, std::string name)
{
	std::deque<std::string> _user_array;
	std::ifstream file(file_name);
	std::string user_info = "";
	while (file)
	{
		std::getline(file, user_info);
		user_info = decrypt(user_info, 11);
		_user_array = Split(user_info);
		if (_user_array.size() >= 3)
			if (_user_array[1] == name)
				return true;
	}
	return false;
}

std::string EatMe::encrypt(std::string text, int shift)
{
	std::string ct = "";
	char pos = 0;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		ct += text[i] + shift;
	}
	return ct;
}

std::string EatMe::decrypt(std::string text, int shift)
{
	std::string pt = "";
	int pos = 0;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		pt += text[i] - shift;
	}
	return pt;
}

std::deque<std::string> EatMe::Split(std::string str)
{
	std::deque<std::string> arr;
	std::string _item = "";
	
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (str[i] == '*')
		{
			arr.push_back(_item);
			_item = "";
		}
		else
			_item += str[i];
	}
	arr.push_back(_item);
	return arr;
}
