#include "EatMe.h"

EatMe::EatMe()
{
	pMenu = new Menu();
	pMenu->addDish(dish("a", 1));
	pMenu->addDish(dish("b", 2));

	pCurrentUser = nullptr;
}

EatMe::~EatMe()
{
	delete pMenu;
	delete pCurrentUser;
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
			case 1: signIn(); break;
			case 2: signUp(); break;
			case 3: exit(0);
			default: throw("\n\t\tWRONG VALUE!!!\n\nReapet input\n");
			}
		}
		catch (std::string warning)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << warning;
		}
	}
}

void EatMe::signIn()
{
	delete pCurrentUser;
	std::string name = "";
	std::string password = "";

	std::cout << "We are glad to see you in our shop!\n";

	std::cout << "Enter your name : ";
	std::cin >> name;
	std::cout << "Enter your password : ";
	hide_input(password);

	std::deque<std::string> user_info = find_user(PASSWORD_FILE_NAME, name, password);

	switch (std::stoi(user_info[0]))
	{
	case CUSTOMER: pCurrentUser = new Customer(user_info[1], user_info[2], user_info[3], std::stoi(user_info[4])); break;
	case ADMIN: pCurrentUser = new Admin(user_info[1], user_info[2]); break;
	}
	if (!pCurrentUser)
	{
		std::cout << "Wrong login or password!";
	}
	run();
}

void EatMe::signUp()
{
	delete pCurrentUser;
	std::string name = "";
	std::string password = "";
	std::string address = "";
	unsigned int money = 0;

	std::cout << "We are glad to see new customer in our shop!\n";

	std::cout << "Enter your name : ";
	std::cin >> name;
	std::cout << "Enter your password : ";
	hide_input(password);
	std::cout << "Enter your address : ";
	std::cin >> address;
	std::cout << "Enter your money count : ";
	std::cin >> money;

	Customer *customer = new Customer(name, password, address, money);

	std::ofstream os(PASSWORD_FILE_NAME);
	UserType user_type = typeid(*pCurrentUser) == typeid(Customer) ? CUSTOMER : ADMIN;
	std::string ct = encrypt(std::to_string(user_type) + " " +
		name + " " + password + " " + address + " " + std::to_string(money)
		, 10);
	os << ct;
	os.close();

	switch (user_type)
	{
	case CUSTOMER: 
		pCurrentUser = new Customer(name, password, address, money);
		break;
	case ADMIN:
		pCurrentUser = new Admin(name, password);
		break;
	}

	show_menu(user_type);
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
								std::cout << "1 - Show the Menu\n2 - Replenish the wallet\n3 - Exit" << std::endl;
								std::cin >> choise;

								switch (choise)
								{
								case 1: pCurrentUser->addInBasket(*pMenu->chooseDish()); break;
								case 2: pCurrentUser->replenishWallet();
								case 4: exit(0);
								default: throw("\n\t\tWRONG VALUE!!!\n\nReapet input\n");
								}
								break;
			}
			case ADMIN:{
						   std::cout << "1 - Add new dish\n2 - Delete dish\n 3 - See orders\n4 - Exit";
						   std::cin >> choise;

						   switch (choise)
						   {
						   case 1: pCurrentUser->addDishInMenu(pMenu); break;
						   case 2: pCurrentUser->deleteDishes(pMenu); break;
						   case 4: exit(0); break;
						   }
						   break;
			}
			default: return;
			}
		}
		catch (std::string warning)
		{
			fflush(stdout);
			std::cin.clear();
			std::cout << warning;
		}
	}
	return;
}

template <class T>
T& EatMe::hide_input(T& var)
{
	char ch;
	for (int i = 0; i < MAX_PASSWORD_LENGTH - 1; ++i)
	{
		std::cin.get(ch);
		if ('\n' != ch)
			var[i] = ch;
		else
		{
			var[i] = '\0';
			return var;
		}
		std::cout.put('*');
	}
	var[MAX_PASSWORD_LENGTH - 1] = '\0';
	return var;
}

std::string EatMe::encrypt(std::string text, unsigned int shift)
{
	char value = 0;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		value = text[i] + shift;
		if (value > 122)
			text[i] = value - 57;
	}
	return text;
}

std::string EatMe::decrypt(std::string text, unsigned int shift)
{
	std::string pt = "";
	char value = 0;
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		pt += text[i] - shift;
		if (pt[i] < 65 && pt[i] != 32)
			text[i] = pt[i] + 57;
	}
	return pt;
}

std::deque<std::string> EatMe::Split(std::string str)
{
	std::deque<std::string> arr(4);
	std::string _item = "";
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (str[i] == ' ')
		{
			arr.push_back(_item);
			_item = "";
		}
		else
			_item += str[i];
	}
	return arr;
}

std::deque<std::string> EatMe::find_user(std::string file_name, std::string name, std::string password)
{
	std::deque<std::string> _user_array;
	std::ifstream file(file_name);
	std::string user_info = "";
	while (file)
	{
		file >> user_info;
		user_info = decrypt(user_info, 10);
		if (user_info.find(name) && user_info.find(password))
		{
			_user_array = Split(user_info);
			break;
		}
	}
	return _user_array;
}