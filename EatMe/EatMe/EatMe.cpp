#include "EatMe.h"

EatMe::EatMe()
{
	ifstream keyFile(KEY_FILE_NAME);
	string key;
	getline(keyFile, key);
	vector<unsigned char> v_key;
	for (int i = 0; i < key.size(); ++i)
		v_key.push_back(key[i]);

	pRC5 = new RC5Simple();
	pRC5->RC5_SetKey(v_key);

	pMenu = new Menu();
	pMenu->addDish("a", 1);
	pMenu->addDish("b", 2);

	customerBasker = new Basket();

	pCurrentUser = new User();
}

EatMe::~EatMe()
{
	delete pRC5;
	delete pMenu;
	delete customerBasker;
	delete pCurrentUser;
}

void EatMe::run()
{
	char choise = 0;
	std::cout << "1 - Log In\n2 - See Menu\n3 - Exit" << endl;
	std::cin >> choise;

	switch (choise)
	{
	case 1: pCurrentUser->logIn(); break;
	case 2: std::cout << pMenu; break;
	case 3: exit(0);
	}
}