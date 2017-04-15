#ifndef EATME_H
#define EATME_H

#include <string>
#include <fstream>

#include "user.h"
#include "menu.h"

class EatMe
{
public:
	explicit EatMe();
	~EatMe();

	void signIn();
	void signUp();

	int run();
	void show_menu(UserType);

protected:
	template <class T>
	T& hide_input(T& var);

private:
	const int MAX_PASSWORD_LENGTH = 20;
	const std::string PASSWORD_FILE_NAME = "storage/passwords.txt";

	std::string encrypt(std::string text, unsigned int shift);
	std::string decrypt(std::string text, unsigned int shift);
	std::deque<std::string> Split(std::string str);
	std::deque<std::string> find_user(std::string file_name, std::string name, std::string password);

	Menu *pMenu;
	User *pCurrentUser;
};

#endif