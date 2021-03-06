#pragma once

#include <conio.h>
#include <algorithm>
#include <fstream>

#include "menu.h"
#include "user.h"

class EatMe
{
public:
	explicit EatMe();
	~EatMe();

	int run();

	void signIn();
	void signUp();

	void show_menu(UserType);
	void newOrder();

protected:
	std::string hide_input();

private:
	const std::string PASSWORD_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890_";
	const int MAX_PASSWORD_LENGTH = 20;
	const std::string PASSWORD_FILE_NAME = "storage/passwords.txt";

	std::deque<std::string> find_user(std::string file_name, std::string name, std::string password);
	bool EatMe::user_exist(std::string file_name, std::string name);
	std::deque<std::string> Split(std::string str);

	Menu *pMenu;
	User *pCurrentUser;

	CurrentOrders pOrderLine;
	History pOrderArchive;
};
