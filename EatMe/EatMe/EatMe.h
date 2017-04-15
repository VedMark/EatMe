#ifndef EATME_H
#define EATME_H

#include <string>

#include "user.h"
#include "menu.h"
#include "order.h"
#include "utils.h"

class EatMe
{
public:
	explicit EatMe();
	~EatMe();

	void signIn();
	void signUp();

	int run();
	void show_menu(UserType);

private:
	const std::string PASSWORD_FILE_NAME = "storage/passwords.txt";

	Menu *pMenu;
	User *pCurrentUser;

	OrderLine aOrderLine;
	History aOrderArchive;
};

#endif